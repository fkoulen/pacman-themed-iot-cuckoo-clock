<?php
$databaseHost = $_SERVER['MYSQL_HOST'];
$databaseUsername = $_SERVER['MYSQL_ROOT_USERNAME'];
$databasePassword = $_SERVER['MYSQL_ROOT_PASSWORD'];
$databaseName = $_SERVER['MYSQL_DATABASE_NAME'];

// Create connection
$db = mysqli_connect($databaseHost, $databaseUsername, $databasePassword, $databaseName);

// Check connection
if (!$db) {
    die("Connection failed: " . mysqli_connect_error());
}
