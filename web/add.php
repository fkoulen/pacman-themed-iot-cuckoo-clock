<?php include_once("config.php");

// Check if the form is submitted
if (isset($_POST['create'])) {
    // Get the name and start date and time from the POST request
    $name = $_POST['name'];
    $start = $_POST['start'];
    // Insert the record in the database
    $sql = "INSERT INTO APPOINTMENT (name, start) VALUES ('$name', '$start')";
    $result = mysqli_query($db, $sql);

    // Check if the insertion was successful. If successful, redirect to index.php
    if ($result) {
        header("Location: index.php");
    } else { // If unsuccessful, display an error message
        echo "Error: " . $sql . " " . mysqli_error($db);
    }
}

