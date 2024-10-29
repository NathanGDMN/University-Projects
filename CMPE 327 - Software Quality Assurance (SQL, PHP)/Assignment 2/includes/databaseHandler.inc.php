<?php 
//Database parameters
$dsn = "mysql:host=localhost;dbname=cisc327"; //Make sure database name is the same
$dbusername = "root"; //Default username
$dbpassword = "";     //Default password

try {
    $pdo = new PDO($dsn, $dbusername, $dbpassword); //Connect to database
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    echo "Connection failed: " . $e->getMessage();
}