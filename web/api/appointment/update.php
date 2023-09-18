<?php
/*
 * Decode the JSON body that is sent to this endpoint and update an appointment. Return a JSON response with a message
 * that indicates whether the appointment was updated or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-18
 */

// Required headers
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: PATCH");

// Include database and object files
include_once '../config/database.php';
include_once '../objects/appointment.php';


// Instantiate database and appointment object
$database = new Database();
$db = $database->getConnection();
$appointment = new Appointment($db);

// Get & set appointment id
$data = json_decode(file_get_contents("php://input"));
$appointment->id = $data->id;

// Set appointment property values
$appointment->name = $data->name;
$appointment->start = $data->start;

// Update the appointment
if ($appointment->update()) {
    // Set response code - 200 ok
    http_response_code(200);

    // Tell the user
    echo json_encode(array("message" => "Appointment was updated."));
} else {
    // Set response code - 400 bad request
    http_response_code(400);

    // Tell the user
    echo json_encode(array("message" => "Unable to update appointment."));
}