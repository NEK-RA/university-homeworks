<h1>Merge sort</h1>
<?php if(isset($_GET["array"])):
    require_once "./merge-sort.php";
    $array = explode(",",$_GET["array"]);
    echo "Array before sort: ".implode(", ", $array);
    echo "<br>";
    $sorted = splitAndMerge($array);
    echo "Sorted array: ".implode(", ", $sorted);
    ?>
    
<?php else:?>
    <form method="get">
        <label>Enter array (separate by comma): <input type="text" name="array"></label><br>
        <input type="submit">
    </form>
<?php endif; ?>
<hr>
<a href="/">Go back</a>
