<?php
// REST
// TODO: CRUD

require_once "./private/dbcreds.php";
require_once "./private/Tool.php";

use function mydb\getConnection;
use myclasses\Tool;

$db = getConnection();
switch ($_SERVER['REQUEST_METHOD']) {
    case 'GET':
        $stmt = $db->prepare("SELECT * FROM `tools`");
        $stmt->execute();
        $tools = $stmt->fetchAll();
        $objects = array_map(function ($tool) {
            return new Tool($tool);
        }, $tools);
        echo json_encode($objects);
        break;

    case 'POST':
        $toolId = $_POST["id"] ?? null;
        $toolTitle = $_POST['title'] ?? null;
        $toolAmount = $_POST['amount'] ?? null;
        $toolPrice = $_POST['price'] ?? null;

        if(!isset($toolId)){
            $db = null;
            header("Location: https://http.cat/400");
        }

        if(!isset($toolTitle) && !isset($toolPrice) && !isset($toolAmount)){
            $db = null;
            header("Location: https://http.cat/400");
        }

        $current = $db->prepare("SELECT * FROM `tools` WHERE `id` = ?");
        $current->execute([$toolId]);
        $tool = $current->fetch();

        $newTitle = $toolTitle ?? $tool["title"];
        $newPrice = $toolPrice ?? $tool["price"];
        $newAmount = $toolAmount ?? $tool["amount"];

        $upd = $db->prepare("UPDATE `tools` SET `title` = :title, `amount` = :amount, `price` = :price WHERE `id` = :id");
        $upd->bindParam(":title",  $newTitle);
        $upd->bindParam(":amount", $newAmount);
        $upd->bindParam(":price", $newPrice);
        $upd->bindParam(":id", $toolId);
        $updated = $upd->execute();

        if($updated){
            $current->execute([$toolId]);
            $tool = $current->fetch();
            echo json_encode($tool);
        }else{
            $db = null;
            header("Location: https://http.cat/500");
        }

        break;

    case 'DELETE':
        if(isset($_REQUEST["id"])){
            $deletion = $db->prepare("DELETE FROM `tools` WHERE `id` = ?");
            $done = $deletion->execute([$_REQUEST["id"]]);
            echo json_encode(["success" => $done]);
        }else{
            header("Location: https://http.cat/400");
        }
        break;

    case 'PUT':
        $toolTitle = $_REQUEST["title"] ?? null;
        $toolPrice = $_REQUEST["price"] ?? null;
        $toolAmount = $_REQUEST["amount"] ?? null;
        if(isset($toolTitle) && isset($toolPrice) && isset($toolAmount)){
            $creation = $db->prepare("INSERT INTO `tools` (title, price, amount) VALUES (:title, :price, :amount)");
            $done = $creation->execute([
                "title" => $toolTitle,
                "price" => $toolPrice,
                "amount" => $toolAmount
            ]);
            echo json_encode(["success" => $done]);
        }else{
            $db = null;
            header("Location: https://http.cat/400");
        }
        break;

    default:
        $db = null;
        header("Location: https://http.cat/405");
        break;
}
$db = null;