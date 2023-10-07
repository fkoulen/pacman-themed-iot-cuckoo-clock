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