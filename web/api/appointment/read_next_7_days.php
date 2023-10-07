<?php
/*
 * Retrieve the upcoming appointments for the next 7 days from the database and return them as JSON.
 * Return a message if no appointments are found.
 *
 * @author F.S. Koulen
 * @date 2023-10-07
 */

// Include utility and object files
require_once '../config/utils.php';
require_once '../objects/appointment.php';

setHeadersGetRequest();

// Initialize object
$appointment = new Appointment(getDatabaseConnection());

// Return appointments
handleReturnAppointments($appointment->readNext7Days());