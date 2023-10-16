/**
 * Listen for the create appointment form to be submitted and send the data to the API.
 * If the appointment was created successfully, redirect to the index page.
 * If an error occurred, display the error message.
 *
 * @author F.S. Koulen
 * @date 2023-09-17
 */

setFormLimitations();

const API_APPOINTMENT_CREATE = `${BASE_URL}/api/appointment/create.php`;

// Add event listener to form
document.getElementById("create-appointment-form").addEventListener("submit", (event) => {
    event.preventDefault();

    const appointment = getAppointmentObject(event);

    // Disable close and submit button, change text of submit button to "Creating..." and hide error message
    document.getElementById("close-button").disabled = true;
    document.getElementById("submit-button").disabled = true;
    document.getElementById("submit-button").innerHTML = "Creating...";
    document.getElementById("create-appointment-error").classList.add("d-none");

    // Send data to API
    fetch(API_APPOINTMENT_CREATE, {
        method: "POST",
        body: JSON.stringify(appointment)
    })
        .then(response => {
            if (response.status === HttpCodes.CREATED) { // Appointment created successfully
                window.location.href = "index.html";
            } else { // If not created successfully, display error message
                response.json()
                    .then(data => handleError(data.message))
                    .catch(() => handleError());
            }
        })
        .catch(() => handleError())
        .finally(() => {
            // Enable close and submit button and change text of submit button back to "Create"
            document.getElementById("close-button").disabled = false;
            document.getElementById("submit-button").disabled = false;
            document.getElementById("submit-button").innerHTML = "Create";
        });
});

/**
 * Handle the error by displaying the error message.
 * If no message is provided, display a default message.
 *
 * @param message The error message to display.
 */
function handleError(message = "An error occurred while creating the appointment.") {
    document.getElementById("create-appointment-error").innerHTML = message;
    document.getElementById("create-appointment-error").classList.remove("d-none");
}