<?php

class Database
{

    private $host;
    private $db_name;
    private $username;
    private $password;
    public $conn;


    public function __construct()
    {
        $this->host = $_SERVER['MYSQL_HOST'];
        $this->db_name = $_SERVER['MYSQL_DATABASE_NAME'];
        $this->username = $_SERVER['MYSQL_ROOT_USERNAME'];
        $this->password = $_SERVER['MYSQL_ROOT_PASSWORD'];
    }

    /*
     * Get the database connection.
     *
     * @return PDO
     */
    public function getConnection()
    {
        $this->conn = null;

        try {
            $this->conn = new PDO("mysql:host=" . $this->host . ";dbname=" . $this->db_name,
                $this->username, $this->password);
            $this->conn->exec("set names utf8");
        } catch (PDOException $exception) {
            echo "Connection error: " . $exception->getMessage();
        }

        return $this->conn;
    }
}
