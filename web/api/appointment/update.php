<?php
/*
 * Decode the JSON body that is sent to this endpoint and update an appointment. Return a JSON response with a message
 * that indicates whether the appointment was updated or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-18
 */

// Include utils and object files
require_once '../config/utils.php';
require_once '../objects/appointment.php';

setHeadersPatchRequest();

// Instantiate appointment object
$appointment = new Appointment(getDatabaseConnection());

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
    echo json_encode(array("message" => "Unable to update appointment. Please check if the appointment exists."));
}