<?php
/*
 * Decode the JSON data that is sent to this endpoint and create a new measurements. Return a JSON response with a
 * message that indicates whether the measurement was created or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-28
 */

// Include utils and object files
require_once '../config/utils.php';
require_once '../objects/measurement.php';

setHeadersPostRequest();

// Initialize object
$measurement = new Measurement(getDatabaseConnection());

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
        returnMessage("Measurement was created.", 201);
    } else {
        returnMessage("Unable to create measurement. Service unavailable.", 503);
    }
} else {
    returnMessage("Unable to create measurement. Data is incomplete.", 400);
}