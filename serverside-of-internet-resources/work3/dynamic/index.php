<?php
require_once "./dbcreds.php";
require_once "./func.php";

use function func\renderTool;
use function mydb\getConnection;

// TODO echo list of tools from database with their amount and order button (if amount > 0)
$db = getConnection();
$stmt = $db->prepare("SELECT * FROM `tools`");
$stmt->execute();
$rows = $stmt->fetchAll();

foreach($rows as $row){
    echo renderTool($row["id"], $row["title"], $row["amount"], $row["price"]);
}

# END OF SCRIPT
$db = null;