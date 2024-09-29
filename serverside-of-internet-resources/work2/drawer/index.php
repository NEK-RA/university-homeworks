<?php
require_once "./shape.php";

echo "<h1>Shape drawer</h1>";
?>
<!-- if number set -->
<?php if(isset($_GET["num"])):{
    $shape = new Shape($_GET["num"]);
    // var_dump($shape);
    echo "Drawing shape for number: ".$shape->getShapeNum()."<br>";
    $blob = base64_encode($shape->draw());
    echo "<image src='data:image/png;base64, $blob'><br>";
    echo "<hr><a href='index.php'>Go back</a>";
}?>

<?php else:?>
<!-- if number not set yet -->
<?php if (isset($_POST["type"])):{
        $type = null;
        switch ($_POST["type"]){
            case "square":
                $type = decbin(1);
                break;
            case "rect":
                $type = decbin(2);
                break;
            case "triangle":
                $type = decbin(3);
                break;
            default:
                $type = decbin(0);
                break;
        }
        echo "Type: ".$_POST["type"]." => ".$type."<br>";

        $red = decbin($_POST["red"]);
        echo "Red: ".$_POST["red"]." => ".$red."<br>";

        $green = decbin($_POST["green"]);
        echo "Green: ".$_POST["green"]." => ".$green."<br>";

        $blue = decbin($_POST["blue"]);
        echo "Blue: ".$_POST["blue"]." => ".$blue."<br>";

        $width = decbin($_POST["width"]);
        echo "Width: ".$_POST["width"]." => ".$width."<br>";

        $height = decbin($_POST["height"]);
        echo "Height: ".$_POST["height"]." => ".$height."<br>";

        $bin = $height." ".$width." ".$blue." ".$green." ".$red." ".$type;
        $num = bindec($type) +
            (bindec($red) << 2) +
            (bindec($green) << 10) +
            (bindec($blue) << 18) +
            (bindec($width) << 26) +
            (bindec($height) << 36);

        echo "Expected number: ".$bin."<br>";
        echo "Result number: ".decbin($num)."<br>";
        echo "<a href='index.php?num=$num'>Draw this shape</a><br>";
    }?>

<?php else:?>
<form method="POST">
    <label>Type:
        <select name="type">
            <option value="circle">Circle</option>
            <option value="square">Square</option>
            <option value="rect">Rectangle</option>
            <option value="triangle">Triangle</option>
        </select>
    </label><br>
    <label>Red:
        <input type="number" max="255" min="0" name="red" value="0">
    </label><br>
    <label>Green:
        <input type="number" max="255" min="0" name="green" value="0">
    </label><br>
    <label>Blue:
        <input type="number" max="255" min="0" name="blue" value="0">
    </label><br>
    <label>Max Width:
        <input type="number" max="1000" min="50" name="width" value="50">
    </label><br>
    <label>Max Height:
        <input type="number" max="1000" min="50" name="height" value="50">
    </label><br>
    <input type="submit">
</form>
<?php endif; ?>
<?php endif; ?>