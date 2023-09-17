<?php include_once("config.php");
// Get the id from the GET request
$id = $_GET['id'];

// Delete the record from the database
$sql = "DELETE FROM APPOINTMENT WHERE id = '$id'";
$result = mysqli_query($db, $sql);

// Check if the deletion was successful. If successful, redirect to index.html
if ($result) {
    header("Location: index.html");
} else { // If unsuccessful, display an error message
    echo "Error: " . $sql . " " . mysqli_error($db);
}