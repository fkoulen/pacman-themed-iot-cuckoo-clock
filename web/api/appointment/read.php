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

// Return appointments
handleReturnAppointments($appointment->read());