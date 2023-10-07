<?php
/*
 * Decode the JSON data that is sent to this endpoint and create a new appointment. Return a JSON response with a
 * message that indicates whether the appointment was created or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

// Include utils and object files
require_once '../config/utils.php';
require_once '../objects/appointment.php';

setHeadersPostRequest();

// Initialize object
$appointment = new Appointment(getDatabaseConnection());

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
        returnMessage("Appointment was created.", 201);
    } else {
        returnMessage("Unable to create appointment. Service unavailable.", 503);
    }
} else {
    returnMessage("Unable to create appointment. Data is incomplete.", 400);
}