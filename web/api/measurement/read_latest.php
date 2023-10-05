<?php
/*
 * Retrieve the latest measurement from the database and return it in JSON format. If no measurement is found, return a
 * JSON response with a message that indicates that no measurements were found.
 *
 * @author F.S. Koulen
 * @date 2023-10-05
 */

// Required headers
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

// Include database and object files
require_once "../config/database.php";
require_once "../objects/measurement.php";

// Instantiate database and measurement object
$database = new Database();
$db = $database->getConnection();

// Initialize object
$measurement = new Measurement($db);

// Query measurements
$measurement->readLatest();

// Check if a measurement was found
if ($measurement->id != null) {
    // Create array to be converted to a JSON object
    $measurement_arr = array(
        "id" => $measurement->id,
        "measurement_time" => $measurement->measurement_time,
        "temperature" => $measurement->temperature,
        "humidity" => $measurement->humidity
    );

    // Set response code - 200 OK
    http_response_code(200);

    // Make it JSON format
    echo json_encode($measurement_arr);
} else {
    // Set response code - 404 Not found
    http_response_code(404);

    // Tell the user no measurements found
    echo json_encode(array("message" => "No measurements found."));
}
