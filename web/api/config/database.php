<?php
/*
 * Database configuration.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

class Database
{

    private string $host;
    private string $db_name;
    private string $username;
    private string $password;
    public ?PDO $conn;


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
    public function getConnection(): ?PDO
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
