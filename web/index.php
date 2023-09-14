<!DOCTYPE html>
<?php
// Include the database connection file
include_once("config.php");

// Get the appointment records from the database
$select_appointments = "SELECT * FROM APPOINTMENT";
$appointments = mysqli_query($db, $select_appointments);
?>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/css/bootstrap.min.css" rel="stylesheet"
          integrity="sha384-4bw+/aepP/YC94hEpVNVgiZdgIC5+VKNBQNGCHeKRQN+PtmoHDEXuppvnDJzQIu9" crossorigin="anonymous">
    <title></title>
</head>
<body>
<div class="container">
    <div class="row">
        <div class="text-center my-5"><h1>Appointments</h1></div>
        <div class="col-md-10 col-md-offset-1">
            <button type="button" class="btn btn-success" data-bs-toggle="modal"
                    data-bs-target="#exampleModal">
                New Appointment
            </button>
            <table class="table">
                <thead>
                <tr>
                    <th scope="col">Appointment</th>
                    <th scope="col">Date & time</th>
                    <th></th>
                    <th></th>
                </tr>
                </thead>
                <tbody>
                <?php
                // Check if there are any records to display
                if (mysqli_num_rows($appointments) > 0) {
                    // Loop through each record found and display the contents
                    while ($res = mysqli_fetch_array($appointments)) {
                        ?>
                        <tr>
                            <td><?php echo $res['name']; ?></td>
                            <td><?php echo $res['start']; ?></td>
                            <td><a href="update.php?id=<?php echo $res['id']; ?>" class="btn btn-primary">Edit</a></td>
                            <td><a href="delete.php?id=<?php echo $res['id']; ?>" class="btn btn-danger">Delete</a></td>
                        </tr>
                        <?php
                    }
                } else { // if there are no records in the database, display an info message
                    ?>
                    <tr>
                        <td colspan="8">No upcoming appointments.</td>
                    </tr>
                    <?php
                }
                ?>
                </tbody>
            </table>
        </div>
    </div>
    <!-- Modal -->
    <div class="modal fade" id="addModal" tabindex="-1" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog">
            <div class="modal-content">
                <form method="post" action="add.php">
                    <div class="modal-header">
                        <h1 class="modal-title fs-5" id="exampleModalLabel">Add Appointment</h1>
                        <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                    </div>
                    <div class="modal-body">
                        <div class="form-group mb-2">
                            <label for="name">Name</label>
                            <input id="name" type="text" required name="name" class="form-control"
                                   maxlength="<?php echo $MAX_LENGHT_APPOINTMENT_NAME ?>"/>
                        </div>
                        <div class="form-group mb-2">
                            <label for="start">Date and time</label>
                            <input id="start" type="datetime-local" required name="start" class="form-control"
                                   maxlength="50"/>
                        </div>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
                        <input type="submit" name="create" value="Create" class="btn btn-primary"/>
                    </div>
                </form>
            </div>
        </div>
    </div>
</div>


<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.1/dist/js/bootstrap.bundle.min.js"
        integrity="sha384-HwwvtgBNo3bZJJLYd8oVXjrBZt8cqVSpeBNS5n7C8IVInixGAoxmnlMuBnhbgrkm"
        crossorigin="anonymous"></script>
</body>
</html>