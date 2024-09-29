<?php
require_once "./dbcreds.php";
require_once "./func.php";

use function func\renderOrder, func\findTool;
use function mydb\getConnection;
// TODO check user cookie for id, create if not presented
// TODO echo list of orders related to this id
$uid = null;

if(!isset($_COOKIE["uid"])){
    $uid = bin2hex(random_bytes(5));
    setcookie("uid", $uid, time() + 3600);
}else{
    $uid = $_COOKIE["uid"];
}
$db = getConnection();

if(isset($_GET["request"])){
    $search = $db->prepare("SELECT * FROM `tools` WHERE `id` = :id");
    $search->execute([":id" => $_GET["request"]]);
    $tool = $search->fetch(PDO::FETCH_ASSOC);
    if($tool){
        if($tool["amount"] > 0){
            $order = $db->prepare("INSERT INTO `orders` (`user_id`, `tool_id`, `date`) VALUES (:uid, :tool, :date)");
            $done = $order->execute([
                ":uid" => $uid,
                ":tool" => $tool["id"],
                ":date" => date("Y-m-d H:i:s")
            ]);
            $decrease = $db->prepare("UPDATE `tools` SET `amount` = `amount` - 1 WHERE `id` = :id");
            $updated = $decrease->execute([":id" => $tool["id"]]);
            if($done && $updated){
                echo $tool["title"]." successfully bought! See your order below!<hr>";
            }else{
                echo "Sorry, something went wrong. Please try again later :(<hr>";
            }
        }else{
            echo $tool["title"]." is out of stock :(<hr>";
        }
    }
}
echo "<a href='./index.php'>Back to list of tools</a><hr>";
// take all tools
$allTools = $db->query("SELECT * FROM `tools`");
$allTools->execute();
$tools = $allTools->fetchAll();
// take ordered
$bought = $db->prepare("SELECT * FROM `orders` WHERE `user_id` = :uid");
$bought->execute([":uid" => $uid]);
$orders = $bought->fetchAll();
foreach ($orders as $order){
    $boughtTool = findTool($order["tool_id"], $tools);
    echo renderOrder($order["id"], $boughtTool["title"], $order["date"]);
}
// END OF SCRIPT
$db = null;