<?php
$databaseHost = $_SERVER['MYSQL_HOST'];
$databaseUsername = $_SERVER['MYSQL_ROOT_USERNAME'];
$databasePassword = $_SERVER['MYSQL_ROOT_PASSWORD'];
$databaseName = $_SERVER['MYSQL_DATABASE_NAME'];

// Create connection
$db = new mysqli($databaseHost, $databaseUsername, $databasePassword, $databaseName);

// Set the maximum length of the appointment name
$MAX_LENGTH_APPOINTMENT_NAME = 50;