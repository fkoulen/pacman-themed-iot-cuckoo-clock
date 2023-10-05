<?php
/*
 * Class that represents a measurement. It has a constructor that takes a database connection as a parameter and
 * functions that can be used to create measurements in the database and read measurements from the database. The data
 * is returned in JSON format.
 *
 * @author F.S. Koulen
 * @date 2023-09-28
 */

class Measurement
{
    private PDO $conn;
    private string $table_name = "measurement";

    public ?string $id;
    public ?string $measurement_time;
    public ?float $temperature;
    public ?float $humidity;

    public function __construct($db)
    {
        $this->conn = $db;
    }

    // Create measurement
    function create(): bool
    {
        // Query to create record
        $query = "INSERT INTO " . $this->table_name . " SET temperature=:temperature, humidity=:humidity";

        // Prepare query
        $stmt = $this->conn->prepare($query);

        // Sanitize
        $this->temperature = htmlspecialchars(strip_tags($this->temperature));
        $this->humidity = htmlspecialchars(strip_tags($this->humidity));

        // Bind values
        $stmt->bindParam(":temperature", $this->temperature);
        $stmt->bindParam(":humidity", $this->humidity);

        // Execute query
        if ($stmt->execute()) {
            return true;
        }
    }

    // Read latest measurement
    function readLatest(): bool
    {
        // Query to read record
        $query = "SELECT * FROM " . $this->table_name . " ORDER BY measurement_time DESC LIMIT 1";

        // Prepare query
        $stmt = $this->conn->prepare($query);

        // Execute query
        $stmt->execute();

        // Get retrieved row
        $row = $stmt->fetch(PDO::FETCH_ASSOC);

        // Set values to object properties
        $this->id = $row['id'];
        $this->measurement_time = $row['measurement_time'];
        $this->temperature = $row['temperature'];
        $this->humidity = $row['humidity'];

        return true;
    }
}