<?php namespace func;
function renderTool($id, $name, $amount, $price): string{
    $left = $amount > 0 ? $amount." items" : "nothing";
    $btn = $amount > 0 ? "<a href='orders.php?request=$id'>BUY</a>" : "";
    return <<< _END
<div>
<h3>$name</h3>
<p>$left left</p>
<p>$price\$</p>
$btn
</div>
_END;

}

function renderOrder($id, $name, $date): string{
    return <<< _END
<div>
<h3>Order $id</h3>
<p>$name</p>
<p>Bought at: $date</p>
</div>
_END;
}

function findTool($id, $list){
    foreach($list as $item){
        if($item['id'] == $id){
            return $item;
        }
    }
}