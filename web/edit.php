<!DOCTYPE html>
<?php
// Include the database connection file
include_once("config.php");

// Fetch the appointment record
$id = $_GET['id'];
$sql = "SELECT * FROM APPOINTMENT WHERE id = '$id' LIMIT 1";
$result = mysqli_query($db, $sql);
$data = mysqli_fetch_assoc($result);
?>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet"
          integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">
    <title>Edit Appointment</title>
</head>
<body>
<div class="container">
    <div class="row">
        <div class="text-center my-5"><h1>Edit Appointment</h1></div>
        <div class="col-md-10 col-md-offset-1">
            <form method="post" action="update.php">
                <input type="hidden" name="id" value="<?php echo $data['id'] ?>"/>
                <div class="modal-body">
                    <div class="form-group mb-2">
                        <label for="name">Name</label>
                        <input id="name" type="text" required name="name" class="form-control"
                               maxlength="<?php echo $MAX_LENGHT_APPOINTMENT_NAME ?>"
                               value="<?php echo $data['name'] ?>"/>
                    </div>
                    <div class=" form-group mb-2">
                        <label for="start">Date and time</label>
                        <input id="start" type="datetime-local" required name="start" class="form-control"
                               value="<?php echo $data['start'] ?>"/>
                    </div>
                </div>
                <div class="modal-footer gap-2 mt-4">
                    <a href="index.html" class="btn btn-secondary">Cancel</a>
                    <input type="submit" name="update" value="Update" class="btn btn-primary"/>
                </div>
            </form>
        </div>
    </div>
</div>


<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-HwwvtgBNo3bZJJLYd8oVXjrBZt8cqVSpeBNS5n7C8IVInixGAoxmnlMuBnhbgrkm"
        crossorigin="anonymous"></script>
</body>
</html>