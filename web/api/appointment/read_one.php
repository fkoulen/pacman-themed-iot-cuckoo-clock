<?php
/*
 * Get the id from the URL and retrieve the appointment with that id from the database. Return a JSON response with the
 * appointment data or a message if the appointment does not exist.
 *
 * @author F.S. Koulen
 * @date 2023-09-18
 */

// Required headers
header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Methods: GET");
header("Content-Type: application/json; charset=UTF-8");

// Include database and object files
include_once '../config/database.php';
include_once '../objects/appointment.php';

// Instantiate database and appointment object
$database = new Database();
$db = $database->getConnection();
$appointment = new Appointment($db);

// Set ID of appointment to be read
$appointment->id = $_GET['id'] ?? die();

// Read the details of appointment to be read
$appointment->readOne();

if ($appointment->name != null) {
    // Create array to be converted to a JSON object
    $appointment_arr = array(
        "id" => $appointment->id,
        "name" => $appointment->name,
        "start" => $appointment->start,
    );

    // Set response code - 200 OK
    http_response_code(200);

    // Make it JSON format
    echo json_encode($appointment_arr);
} else {
    // Set response code - 404 Not found
    http_response_code(404);

    // Tell the user appointment does not exist
    echo json_encode(array("message" => "Appointment does not exist."));
}