<?php namespace mydb;
use PDO, PDOException;

const DB_USER = "root";
const DB_PASS = "toor";
const DB_HOST = "mysql";
const DB_PORT = "3306";
const DB_NAME = "shop";
const DB_CHARSET = "utf8mb4";
const DB_OPTS = [
    PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
    PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
    PDO::ATTR_EMULATE_PREPARES => false
];

function getConnection(){
    try{
        $DB_ATTR = "mysql:host=".DB_HOST
            .";port=".DB_PORT
            .";dbname=".DB_NAME
            .";charset=".DB_CHARSET;
        $pdo = new PDO(
            $DB_ATTR,
            DB_USER,
            DB_PASS,
            DB_OPTS
        );
        return $pdo;
    }catch (PDOException $e){
        throw new PDOException($e->getMessage(), (int)$e->getCode());
    }
}