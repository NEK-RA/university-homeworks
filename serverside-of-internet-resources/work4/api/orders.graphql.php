<?php
require_once "./private/dbcreds.php";
use function mydb\getConnection;
// GraphQL
$rawgql = file_get_contents('php://input');
$q = trim(json_decode($rawgql, true)["query"]);
$isQuery = str_starts_with($q, "query");
$isMutation = str_starts_with($q, "mutation");
if(!$isQuery && !$isMutation){
    header("Location: https://http.cat/400");
}
$q = trim(substr($q, strpos($q, "{")+1, -1));
preg_match("/(?'opname'[a-zA-Z0-9_]+)(?'args'\(.*?\))?(\{(?'fields'[a-zA-Z0-9_,\s]+)\})?/", $q, $matches);

$opname = $matches["opname"];
$args = $matches["args"];
$fields = [];
if(in_array("fields", array_keys($matches))){
    $fields = array_map(function($field){
        return trim($field);
    }, explode(",", $matches["fields"]));
}

if($isQuery && $opname == "orders"){
    // Для чтения есть только операция на весь список, поэтому без аргументов
    $db = getConnection();
    $query = $db->query("SELECT * FROM `orders`");
    $data = $query->fetchAll(PDO::FETCH_ASSOC);
    $db = null;

    $result = array_map(function($item){
        global $fields;
        $value = [];
        foreach($fields as $field){
            if(in_array($field, array_keys($item))){
                $value[$field] = $item[$field];
            }
        }
        return $value;
    }, $data);

    echo json_encode($result);
}else if($isMutation){
    // создание, редактирование и удаление без аргументов не обойдется
    $args = substr($args, 1, -1);
    $fieldRegex = "(?'field'[a-zA-Z0-9_]+)";
    preg_match_all("/,?\s*".$fieldRegex."\s*:/", $args, $matches, PREG_OFFSET_CAPTURE);
    $offsets = $matches["field"];
    $indexes = [];
    foreach($offsets as $offset){
        $indexes[] = $offset[1];
    }
    $indexes[] = strlen($args);
    $params = [];
    for($i=0; $i < count($indexes) - 1; $i++){
        $kv = trim(substr($args, $indexes[$i], $indexes[$i+1]));
        preg_match("/\s*".$fieldRegex."\s*:\s*(?'value'\S*)/", $kv, $parts);
        $params[$parts["field"]] = trim($parts["value"]);
    }
    $params = array_map(function($value){
        $r = $value;
        if(str_ends_with($r, ",")){
            $r = substr($r, 0, -1);
        }
        return trim($r);
    }, $params);
    $db = getConnection();
    switch ($opname) {
        case "add":
            if(in_array("user_id",array_keys($params)) && in_array("tool_id",array_keys($params))){
                $idOfTools = $db->prepare("SELECT id FROM tools");
                $idOfTools->execute();
                $idOfTools = $idOfTools->fetchAll();
                $idOfTools = array_map(function($row){
                    return $row["id"];
                }, $idOfTools);
                if(!in_array($params["tool_id"],$idOfTools)){
                    if(in_array("success", $fields)){
                        echo json_encode(["success" => false]);
                    }else{
                        echo json_encode(["error" => "Wrong tool id"]);
                    }
                    die();
                }
                $order = $db->prepare("INSERT INTO `orders` (`user_id`, `tool_id`, `date`) VALUES (:uid, :tool, :date)");
                $done = $order->execute([
                    ":uid" => $params["user_id"],
                    ":tool" => $params["tool_id"],
                    ":date" => date("Y-m-d H:i:s")
                ]);
                // TODO стоит изменить значение в таблице `tools`
                if(in_array("success", $fields)){
                    echo json_encode(["success" => $done]);
                }else{
                    $createdId = $db->lastInsertId();
                    $created = $db->prepare("SELECT * FROM `orders` WHERE `id` = :id");
                    $created->execute([":id" => $createdId]);
                    $created = $created->fetch(PDO::FETCH_ASSOC);
                    echo json_encode($created);
                }
            }else{
                header("Location: https://http.cat/400");
            }
            break;
        case "delete":
            if(in_array("id",array_keys($params))) {
                $search = $db->prepare("SELECT COUNT(*) as exist FROM orders WHERE `id` = :id");
                $search->execute([":id" => $params["id"]]);
                $order = $search->fetch();
                if($order != null && $order["exist"] == 1){
                    $deletion = $db->prepare("DELETE FROM `orders` WHERE `id` = :id");
                    $done = $deletion->execute([":id" => $params["id"]]);
                    echo json_encode(["success" => $done]);
                }else{
                    if(in_array("success", $fields)){
                        echo json_encode(["success" => false]);
                    }else{
                        echo json_encode(["error" => "Wrong order id"]);
                    }
                }
            }else{
                header("Location: https://http.cat/400");
                die();
            }
            break;
        case "update":
            if(in_array("id",array_keys($params))) {
                if(in_array("user_id",array_keys($params)) || in_array("tool_id",array_keys($params))){
                    $search = $db->prepare("SELECT * FROM orders WHERE `id` = :id");
                    $search->execute([":id" => $params["id"]]);
                    $oldState = $search->fetch();
                    if($oldState != null){
                        if(in_array("tool_id",array_keys($params))){
                            $idOfTools = $db->prepare("SELECT id FROM tools");
                            $idOfTools->execute();
                            $idOfTools = $idOfTools->fetchAll();
                            $idOfTools = array_map(function($row){
                                return $row["id"];
                            }, $idOfTools);
                            if(!in_array($params["tool_id"],$idOfTools)){
                                if(in_array("success", $fields)){
                                    echo json_encode(["success" => false]);
                                }else{
                                    echo json_encode(["error" => "Wrong tool id"]);
                                }
                                die();
                            }
                        }
                        $uid = $params["user_id"] ?? $oldState["user_id"];
                        $tool = $params["tool_id"] ?? $oldState["tool_id"];
                        $upd = $db->prepare("UPDATE `orders` SET `user_id` = :uid, `tool_id` = :tool WHERE `id` = :id");
                        $done = $upd->execute([
                            ":uid" => $uid,
                            ":tool" => $tool,
                            ":id" => $params["id"]
                        ]);
                        if(in_array("success", $fields)){
                            echo json_encode(["success" => $done]);
                        }else{
                            $search->execute([":id" => $params["id"]]);
                            $newState = $search->fetch();
                            echo json_encode($newState);
                        }
                    }else{
                        if(in_array("success", $fields)){
                            echo json_encode(["success" => false]);
                        }else{
                            echo json_encode(["error" => "Wrong order id"]);
                        }
                    }
                }else{
                    header("Location: https://http.cat/400");
                    die();
                }
            }else{
                header("Location: https://http.cat/400");
                die();
            }
            break;
        default:
            header("Location: https://http.cat/405");
            break;
    }
}else{
    header("Location: https://http.cat/405");
}