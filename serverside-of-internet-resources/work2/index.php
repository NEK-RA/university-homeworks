<?php
$links = [
    "Drawer" => "drawer/index.php",
    "Sorter" => "sort/index.php",
    "Shell" => "shell/index.html",
];
echo "<ul>";
foreach ($links as $key => $value) {
    echo "<li><a href='$value'>$key</a></li>";
}
echo "</ul>";