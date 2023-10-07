<?php
/*
 * Retrieve the latest measurement from the database and return it in JSON format. If no measurement is found, return a
 * JSON response with a message that indicates that no measurements were found.
 *
 * @author F.S. Koulen
 * @date 2023-10-05
 */

// Include utils and object files
require_once "../config/utils.php";
require_once "../objects/measurement.php";

setHeadersGetRequest();

// Initialize object
$measurement = new Measurement(getDatabaseConnection());

// Read latest measurement
if ($measurement->readLatest()) {
    // Create array to be converted to a JSON object
    $measurement_arr = array(
        "id" => $measurement->id,
        "measurement_time" => $measurement->measurement_time,
        "temperature" => $measurement->temperature,
        "humidity" => $measurement->humidity
    );

    returnData($measurement_arr, 200);
} else { // If no measurements are found
    returnMessage("No measurements found.", 404);
}
