<?php
/**
 * This file contains utility functions that are used by multiple files.
 *
 * @author F.S. Koulen
 * @date 2023-10-07
 */

require_once "../config/database.php";

/**
 * Set the headers for a GET request.
 *
 * @return void
 */
function setHeadersGetRequest(): void
{
    // Required headers
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
}

/**
 * Set the headers for a POST request.
 *
 * @return void
 */
function setHeadersPostRequest(): void
{
    // Required headers
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
    header("Access-Control-Allow-Methods: POST");
    header("Access-Control-Max-Age: 3600");
}

/**
 * Set the headers for a PATCH request.
 *
 * @return void
 */
function setHeadersPatchRequest(): void
{
    // Required headers
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
    header("Access-Control-Allow-Methods: PATCH");
}

/**
 * Set the headers for a DELETE request.
 *
 * @return void
 */
function setHeadersDeleteRequest(): void
{
    // Required headers
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
    header("Access-Control-Allow-Methods: DELETE");
}

/**
 * Return a JSON response with a message and a response code.
 *
 * @param string $message the message to return
 * @param int $responseCode the response code to return
 * @return void
 */
function returnMessage(string $message, int $responseCode): void
{
    returnData(array("message" => $message), $responseCode);
}

/**
 * Return a JSON response with data and a response code.
 *
 * @param array $data the data to return
 * @param int $responseCode the response code to return
 * @return void
 */
function returnData(array $data, int $responseCode): void
{
    // Set response code
    http_response_code($responseCode);

    // Tell the user
    echo json_encode($data);
}

/**
 * Create a database connection and return it.
 *
 * @return PDO the database connection
 */
function getDatabaseConnection(): PDO
{
    $database = new Database();
    return $database->getConnection();
}

/**
 * Handle the return of appointments. Return a JSON response with the appointments or a message if no appointments are
 * found.
 *
 * @param bool|PDOStatement $statement the statement to handle.
 * @return void
 */
function handleReturnAppointments(bool|PDOStatement $statement): void
{
    $num = $statement->rowCount();

// Check if more than 0 record found
    if ($num > 0) {
        // Appointments array
        $appointments_arr = array();
        $appointments_arr["records"] = array();

        // Retrieve table contents
        while ($row = $statement->fetch(PDO::FETCH_ASSOC)) {
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
}