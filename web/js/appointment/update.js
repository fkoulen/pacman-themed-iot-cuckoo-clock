/*
    Update the appointment once the form is submitted.
    If the appointment was updated successfully, redirect to the index page.
    If an error occurred, display the error message.

    @author F.S. Koulen
    @date 2023-09-18
 */
const API_APPOINTMENT_UPDATE = "http://localhost/api/appointment/update.php";

document.getElementById("update-appointment-form").addEventListener("submit", function (event) {
    event.preventDefault();

    // Get form data
    const formData = new FormData(event.target);
    const appointment = {};
    formData.forEach((value, key) => {
        appointment[key] = value;
    });

    // Disable cancel and submit button, change text of submit button to "Updating..." and hide error message
    document.getElementById("cancel-button").disabled = true;
    document.getElementById("submit-button").disabled = true;
    document.getElementById("submit-button").innerHTML = "Updating...";
    document.getElementById("update-appointment-error").classList.add("d-none");

    // Send data to API
    fetch(API_APPOINTMENT_UPDATE, {
        method: "PATCH", body: JSON.stringify(appointment)
    }).then(response => {
        if (response.status === 200) { // Appointment updated successfully
            window.location.href = "index.html";
        } else {
            response.json().then(data => {
                document.getElementById("update-appointment-error").innerHTML = data.message;
                document.getElementById("update-appointment-error").classList.remove("d-none");
            });
        }
    }).catch((reason) => {
        console.error(reason);
        document.getElementById("update-appointment-error").innerHTML = "An error occurred while updating the appointment.";
        document.getElementById("update-appointment-error").classList.remove("d-none");
    }).finally(() => {
        // Enable cancel and submit button and change text of submit button back to "Update"
        document.getElementById("cancel-button").disabled = false;
        document.getElementById("submit-button").disabled = false;
        document.getElementById("submit-button").innerHTML = "Update";
    });
});