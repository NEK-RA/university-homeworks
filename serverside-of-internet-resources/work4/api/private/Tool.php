<?php

namespace myclasses;

class Tool{
    public readonly int $id;
    public readonly string $title;
    public readonly int $amount;
    public readonly float $price;

    public function __construct($dbrow){
        $this->id = $dbrow['id'] ?? -1;
        $this->title = $dbrow['title'] ?? 'Missing title value';
        $this->amount = $dbrow['amount'] ?? -1;
        $this->price = $dbrow['price'] ?? -1;
    }
}