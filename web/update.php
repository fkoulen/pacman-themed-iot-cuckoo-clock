<?php include_once("config.php");
// Check if the form was submitted
if (isset($_POST['update'])) {
    // Get the id, name and start date and time from the POST request
    $id = $_POST['id'];
    $name = $_POST['name'];
    $start = $_POST['start'];

    // Update the appointment record
    $sql = "UPDATE APPOINTMENT SET name = '$name', start = '$start' WHERE id = '$id'";
    $result = mysqli_query($db, $sql);

    // Check if the update was successful. If successful, redirect to index.php
    if ($result) {
        header("Location: index.php");
    } else { // If unsuccessful, display an error message
        echo "Error: " . $sql . " " . mysqli_error($db);
    }
}