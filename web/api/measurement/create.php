<?php
/*
 * Decode the JSON data that is sent to this endpoint and create a new measurements. Return a JSON response with a
 * message that indicates whether the measurement was created or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-28
 */


// Required headers
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: POST");

// Include database and object files
include_once '../config/database.php';
include_once '../objects/measurement.php';

// Instantiate database and measurement object
$database = new Database();
$db = $database->getConnection();

// Initialize object
$measurement = new Measurement($db);

// Get posted data
$data = json_decode(file_get_contents("php://input"));

// Make sure data is not empty
if (
    !empty($data->temperature) &&
    !empty($data->humidity)
) {
    // Set measurement property values
    $measurement->temperature = $data->temperature;
    $measurement->humidity = $data->humidity;

    // Create the measurement
    if ($measurement->create()) {
        // Set response code - 201 created
        http_response_code(201);

        // Tell the user
        echo json_encode(array("message" => "Measurement was created."));
    } else {
        // Set response code - 503 service unavailable
        http_response_code(503);

        // Tell the user
        echo json_encode(array("message" => "Unable to create measurement. Service unavailable."));
    }
} else {
    // Set response code - 400 bad request
    http_response_code(400);

    // Tell the user
    echo json_encode(array("message" => "Unable to create measurement. Data is incomplete."));
}