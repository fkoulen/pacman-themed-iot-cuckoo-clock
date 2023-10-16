/**
 * Update the appointment once the form is submitted.
 * If the appointment was updated successfully, redirect to the index page.
 * If an error occurred, display the error message.
 *
 * @author F.S. Koulen
 * @date 2023-09-18
 */

const API_APPOINTMENT_UPDATE = `${BASE_URL}/api/appointment/update.php`;

document.getElementById("update-appointment-form").addEventListener("submit", function (event) {
    event.preventDefault();

    const appointment = getAppointmentObject(event);

    // Disable cancel and submit button, change text of submit button to "Updating..." and hide error message
    document.getElementById("cancel-button").disabled = true;
    document.getElementById("submit-button").disabled = true;
    document.getElementById("submit-button").innerHTML = "Updating...";
    document.getElementById("update-appointment-error").classList.add("d-none");

    // Send data to API
    fetch(API_APPOINTMENT_UPDATE, {
        method: "PATCH", body: JSON.stringify(appointment)
    })
        .then(response => {
            if (response.status === HttpCodes.OK) { // Appointment updated successfully, redirect to index page
                window.location.href = "index.html";
            } else {
                response.json()
                    .then(data => handleError(data.message))
                    .catch(() => handleError())
            }
        })
        .catch(() => handleError())
        .finally(() => {
            // Enable cancel and submit button and change text of submit button back to "Update"
            document.getElementById("cancel-button").disabled = false;
            document.getElementById("submit-button").disabled = false;
            document.getElementById("submit-button").innerHTML = "Update";
        });
});

/**
 * Handle the error by displaying the error message.
 * If no message is provided, display a default message.
 *
 * @param message The error message to display.
 */
function handleError(message = "An error occurred while updating the appointment.") {
    document.getElementById("update-appointment-error").innerHTML = message;
    document.getElementById("update-appointment-error").classList.remove("d-none");
}