<!-- 
Общий принцип: 
разделить массив на 2 части, 
для каждой половины заново вызвать merge sort
когда отработает - склеить обе части
/merge-sort.php?array=172%2C31%2C196%2C41%2C60%2C460%2C+28

https://onlinegdb.com/KRbQ2aqBi
-->
<?php
    function splitAndMerge($arr, $run = 0){
        if(count($arr) == 1){
            return $arr;
        }
        $mid = (int)(count($arr) / 2)  + (count($arr) % 2);
        $left = array();
        $right = array();
        for($i=0; $i < count($arr); $i++){
            if($i < $mid){
                $left[] = $arr[$i];
            }else{
                $right[] = $arr[$i];
            }
        }
        // echo "<br>Run $run<br>";
        // echo "Left part: ".implode(", ", $left)."<br>";
        // echo "Right part: ".implode(", ", $right)."<br>";
        $leftSorted = splitAndMerge($left, $run + 1.1);
        $rightSorted = splitAndMerge($right, $run + 1.2);
        $merged = actuallyMerge($leftSorted, $rightSorted, $run);
        // echo "<br>";
        return $merged;
    }
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
    function actuallyMerge($l, $r, $run){
        // echo "Merge $run<br>";
        // echo "Left part: ".implode(", ", $l)."<br>";
        // echo "Right part: ".implode(", ", $r)."<br>";
        $il = 0;
        $ir = 0;
        $res = array();
        $other = array();
        $io = 0;
        // most elements
        while($il < count($l) && $ir < count($r)){
            // echo "Current loop run:<br>
            // \$il=$il \t \$l[$il]=$l[$il]<br>
            // \$ir=$ir \t \$r[$ir]=$r[$ir]<br>";
            if($l[$il] < $r[$ir]){
                // echo $l[$il]." < ".$r[$ir]."<br>";
                $res[] = $l[$il];
                $il++;
            }else{
                // echo $r[$ir]." < ".$l[$il]."<br>";
                $res[] = $r[$ir];
                $ir++;
            }
        }
        // echo "Loop finished:<br>
        //     \$il=$il \t \$l[$il]=$l[$il]<br>
        //     \$ir=$ir \t \$r[$ir]=$r[$ir]<br>";
        // echo "Most elements merged: ".implode(", ", $res)."<br>";
        // rest elements
        if($il >= count($l)){
            // echo "Left exceeded, so appending right<br>";
            for($i = $ir; $i < count($r); $i++){
                $res[] = $r[$i];
            }
        }else{
            // echo "Right exceeded, so appending left<br>";
            for($i = $il; $i < count($l); $i++){
                $res[] = $l[$i];
            }
        }
        // echo "Rest elements merged: ".implode(", ", $res)."<br>";
        return $res;
    }