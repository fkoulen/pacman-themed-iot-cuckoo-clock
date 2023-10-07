<?php
/*
 * Decode the id that is sent through JSON and delete an appointment from the database. Returns a JSON response with a
 * message that indicates whether the appointment was deleted or not.
 *
 * @author F.S. Koulen
 * @date 2023-09-18
 */

// Include database, utils and object files
require_once '../config/utils.php';
require_once '../objects/appointment.php';

setHeadersDeleteRequest();

$appointment = new Appointment(getDatabaseConnection());

// Get & set appointment id
$data = json_decode(file_get_contents("php://input"));
$appointment->id = $data->id;

// Delete the appointment
if ($appointment->delete()) {
    returnMessage("Appointment was deleted.", 200);
} else {
    returnMessage("Unable to delete appointment. The appointment does not exist or could not be retrieved.", 400);
}