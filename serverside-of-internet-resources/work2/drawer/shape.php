<?php
class Shape{
/*
TODO: работа с битовыми сдвигами
- первые 2 бита - форма // 00 - круг, 01 - квадрат, 10 - прямоугольник, 11 - треугольник
- следующие 24 бита - rgb
- остальное - размеры
*/
    private int $num = 0;
    private string $type = "";
    private string $color = "";
    private $max_width = 0;
    private $max_height = 0;

    public function __construct($val){
        // save number to be able to provide it for any reason
        $this->num = $val;
        // echo $val." => ".decbin($val)."<br>";
        // single byte to use in other values
        $bytemask = 0b11111111;
        $tenbits = 0b1111111111;
        // calculate shape type
        $type = $val & 0b11;
        switch($type){
            case 0b01:
                $this->type = "square";
                break;
            case 0b10:
                $this->type = "rect";
                break;
            case 0b11:
                $this->type = "triangle";
                break;
            default:
                $this->type = "circle";
        }

        // calculate shape color
        $offset = 2;

        $red = ($val >> $offset) & $bytemask;
        $offset += 8;

        $green = ($val >> $offset) & $bytemask;
        $offset += 8;

        $blue = ($val >> $offset) & $bytemask;
        $offset += 8;

        $this->color = "rgb($red, $green, $blue)";

        // calculate shape max size
        $width = ($val >> $offset) & $tenbits;
        $offset += 10;
        $height = ($val >> $offset) & $tenbits;
        if($width != 0){
            $this->max_width = $width;
        }
        if($height != 0){
            $this->max_height = $height;
        }
    }

    public function getShapeNum(){
        return $this->num;
    }

    public function draw(){
        $image = new Imagick();
        $image->newImage($this->max_width, $this->max_height, 'grey');

        $content = new ImagickDraw();
        $content->setFillColor(new ImagickPixel($this->color));

        $min = $this->max_width < $this->max_height ? $this->max_width : $this->max_height;

        switch ($this->type){
            case "rect":
                $content->rectangle(0,0,$this->max_width,$this->max_height);
                break;
            case "square":
                $content->rectangle(0,0,$min,$min);
                break;
            case "circle":
                $cx = $this->max_width/2;
                $cy = $this->max_height/2;
                $content->circle($cx,$cy, $cx, $cy - $min/2);
                break;
            case "triangle":
                $content->polygon([
                    ["x" => 0, "y" => 0],
                    ["x" => $this->max_width, "y" => $this->max_height],
                    ["x" => $this->max_width * 0.25, "y" => $this->max_height * 0.75]
                ]);

        }

        $image->setImageFormat("png");
        $image->drawImage($content);
        return $image->getImageBlob();
    }
}
