<?php
/*
 * Class that represents an appointment. It has a constructor that takes a database connection as a parameter and
 * multiple functions that can be used to read, create, update and delete appointments from the database. The data is
 * returned in JSON format.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

class Appointment
{
    private PDO $conn;
    private string $table_name = "appointment";

    public $id;
    public $name;
    public $start;

    public function __construct($db)
    {
        $this->conn = $db;
    }

    // Read appointments
    function read()
    {
        // Select all query
        $query = "SELECT * FROM " . $this->table_name . " ORDER BY start";

        // Prepare query statement
        $stmt = $this->conn->prepare($query);

        // Execute query
        $stmt->execute();

        return $stmt;
    }

    // Create appointment
    function create()
    {
        // Query to insert record
        $query = "INSERT INTO " . $this->table_name . " SET name=:name, start=:start";

        // Prepare query
        $stmt = $this->conn->prepare($query);

        // Sanitize
        $this->name = htmlspecialchars(strip_tags($this->name));
        $this->start = htmlspecialchars(strip_tags($this->start));

        // Bind values
        $stmt->bindParam(":name", $this->name);
        $stmt->bindParam(":start", $this->start);

        // Execute query
        if ($stmt->execute()) {
            return true;
        }

        return false;
    }
}