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
    private mixed $conn;
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
}