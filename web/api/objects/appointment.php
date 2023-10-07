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

    public ?string $id;
    public ?string $name;
    public ?string $start;

    public function __construct($db)
    {
        $this->conn = $db;
    }

    // Read upcoming appointments
    function read(): bool|PDOStatement
    {
        // Select all query
        $query = "SELECT * FROM " . $this->table_name . " WHERE start > NOW() ORDER BY start ASC";

        // Prepare query statement
        $stmt = $this->conn->prepare($query);

        // Execute query
        $stmt->execute();

        return $stmt;
    }

    // Read one appointment
    function readOne(): void
    {
        // Query to read single record
        $query = "SELECT * FROM " . $this->table_name . " WHERE id = ? LIMIT 0,1";

        // Prepare query statement
        $stmt = $this->conn->prepare($query);

        // Bind id of appointment to be read
        $stmt->bindParam(1, $this->id);

        // Execute query
        $stmt->execute();

        // Get retrieved row
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        // Set values to object properties
        $this->name = $row['name'] ?? null;
        $this->start = $row['start'] ?? null;
    }

    // Read appointments of the next 7 days
    function readNext7Days(): bool|PDOStatement
    {
        // Select all query
        $query = "SELECT * FROM " . $this->table_name . " WHERE start > NOW() AND start < DATE_ADD(NOW(), INTERVAL 7 DAY) ORDER BY start ASC";

        // Prepare query statement
        $stmt = $this->conn->prepare($query);

        // Execute query
        $stmt->execute();

        return $stmt;
    }

    // Check if appointment exists
    function exists(): bool
    {
        // Query to read single record
        $query = "SELECT * FROM " . $this->table_name . " WHERE id = ? LIMIT 0,1";

        // Prepare query statement
        $stmt = $this->conn->prepare($query);

        // Bind id of appointment to be read
        $stmt->bindParam(1, $this->id);

        // Execute query
        $stmt->execute();

        // Get retrieved row
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        // Return true if row exists
        return (bool)$row;
    }


    // Create appointment
    function create(): bool
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

    // Update the appointment if it exists
    function update(): bool
    {
        // Check if appointment exists before updating it
        if ($this->exists()) {
            // Update query
            $query = "UPDATE " . $this->table_name . " SET name=:name, start=:start WHERE id=:id";

            // Prepare query statement
            $stmt = $this->conn->prepare($query);

            // Sanitize
            $this->name = htmlspecialchars(strip_tags($this->name));
            $this->start = htmlspecialchars(strip_tags($this->start));
            $this->id = htmlspecialchars(strip_tags($this->id));

            // Bind values
            $stmt->bindParam(":name", $this->name);
            $stmt->bindParam(":start", $this->start);
            $stmt->bindParam(":id", $this->id);

            // Execute query
            if ($stmt->execute()) {
                return true;
            }
        }

        return false;
    }

    // Delete the appointment if it exists
    function delete(): bool
    {
        // Check if appointment exists before deleting it
        if ($this->exists()) {
            // Delete query
            $query = "DELETE FROM " . $this->table_name . " WHERE id = ?";

            // Prepare query
            $stmt = $this->conn->prepare($query);

            // Sanitize
            $this->id = htmlspecialchars(strip_tags($this->id));

            // Bind id of record to delete
            $stmt->bindParam(1, $this->id);

            // Execute query
            if ($stmt->execute()) {
                return true;
            }
        }

        return false;
    }
}