<!DOCTYPE html>
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
        <!--            Show loading spinner -->
        <div class="d-flex justify-content-center" id="loading">
            <div class="spinner-border" role="status">
                <span class="visually-hidden">Loading...</span>
            </div>
        </div>
        <!--            Show error message -->
        <div class="alert alert-danger d-none" id="error"></div>
        <!--            Show form -->
        <div id="form" class="d-none">
            <form method="post" action="update.php">
                <input type="hidden" name="id" id="id"/>
                <div class="modal-body">
                    <div class="form-group mb-2">
                        <label for="name">Name</label>
                        <input id="name" type="text" required name="name" class="form-control"/>
                    </div>
                    <div class=" form-group mb-2">
                        <label for="start">Date and time</label>
                        <input id="start" type="datetime-local" required name="start" class="form-control"
                        />
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
<script src="js/appointment/read_one.js"></script>
</body>
</html>