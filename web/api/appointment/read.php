<?php
/*
 * Retrieve all upcoming appointments from the database and return them as JSON.
 * Return a message if no appointments are found.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

// Include utils and object files
require_once "../config/utils.php";
require_once "../objects/appointment.php";

setHeadersGetRequest();

// Initialize object
$appointment = new Appointment(getDatabaseConnection());

// Query appointments
$stmt = $appointment->read();
$num = $stmt->rowCount();

// Check if more than 0 record found
if ($num > 0) {
    // Appointments array
    $appointments_arr = array();
    $appointments_arr["records"] = array();

    // Retrieve table contents
    while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
        // Extract row
        extract($row);

        $appointment_item = array(
            "id" => $id,
            "name" => $name,
            "start" => $start
        );

        $appointments_arr["records"][] = $appointment_item;
    }

    returnData($appointments_arr, 200);
} else {
    returnMessage("No appointments found.", 404);
}