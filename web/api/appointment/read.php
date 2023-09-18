<?php
/*
 * Retrieve all appointments from the database and return them as JSON. Return a message if no appointments are found.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

// Required headers
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

// Include database and object files
require_once "../config/database.php";
require_once "../objects/appointment.php";

// Instantiate database and appointment object
$database = new Database();
$db = $database->getConnection();

// Initialize object
$appointment = new Appointment($db);

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

    // Set response code - 200 OK
    http_response_code(200);

    // Show appointments data in json format
    echo json_encode($appointments_arr);
} else {
    // Set response code - 404 Not found
    http_response_code(404);

    // Tell the user no appointments found
    echo json_encode(array("message" => "No appointments found."));
}