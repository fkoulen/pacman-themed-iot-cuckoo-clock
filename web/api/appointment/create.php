<?php
/*
 * Decode the JSON data that is sent to this endpoint and create a new appointment. Return a JSON response with a
 * message that indicates whether the appointment was created or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

// Required headers
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: POST");

// Include database and object files
include_once '../config/database.php';
include_once '../objects/appointment.php';

// Instantiate database and appointment object
$database = new Database();
$db = $database->getConnection();

// Initialize object
$appointment = new Appointment($db);

// Get posted data
$data = json_decode(file_get_contents("php://input"));

// Make sure data is not empty
if (
    !empty($data->name) &&
    !empty($data->start)
) {
    // Set appointment property values
    $appointment->name = $data->name;
    $appointment->start = $data->start;

    // Create the appointment
    if ($appointment->create()) {
        // Set response code - 201 created
        http_response_code(201);

        // Tell the user
        echo json_encode(array("message" => "Appointment was created."));
    } else {
        // Set response code - 503 service unavailable
        http_response_code(503);

        // Tell the user
        echo json_encode(array("message" => "Unable to create appointment. Service unavailable."));
    }
} else {
    // Set response code - 400 bad request
    http_response_code(400);

    // Tell the user
    echo json_encode(array("message" => "Unable to create appointment. Data is incomplete."));
}