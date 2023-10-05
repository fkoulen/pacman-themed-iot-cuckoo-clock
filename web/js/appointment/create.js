/*
    Listen for the create appointment form to be submitted and send the data to the API.
    If the appointment was created successfully, redirect to the index page.
    If an error occurred, display the error message.

    @author F.S. Koulen
    @date 2023-09-17
 */

setFormLimitations();

const API_APPOINTMENT_CREATE = `${BASE_URL}/api/appointment/create.php`;

// Add event listener to form
document.getElementById("create-appointment-form").addEventListener("submit", (event) => {
    event.preventDefault();

    // Get form data
    const formData = new FormData(event.target);
    const appointment = {};
    formData.forEach((value, key) => {
        appointment[key] = value;
    });

    // Set start time to UTC
    appointment.start = moment(localToUtc(appointment.start)).format("YYYY-MM-DD HH:mm:ss");

    // Disable close and submit button, change text of submit button to "Creating..." and hide error message
    document.getElementById("close-button").disabled = true;
    document.getElementById("submit-button").disabled = true;
    document.getElementById("submit-button").innerHTML = "Creating...";
    document.getElementById("create-appointment-error").classList.add("d-none");

    // Send data to API
    fetch(API_APPOINTMENT_CREATE, {
        method: "POST",
        body: JSON.stringify(appointment)
    }).then(response => {
        if (response.status === 201) { // Appointment created successfully
            window.location.href = "index.html";
        } else {
            response.json().then(data => {
                document.getElementById("create-appointment-error").innerHTML = data.message;
                document.getElementById("create-appointment-error").classList.remove("d-none");
            });
        }
    }).catch((reason) => {
        console.error(reason);
        document.getElementById("create-appointment-error").innerHTML = "An error occurred while creating the appointment.";
        document.getElementById("create-appointment-error").classList.remove("d-none");
    }).finally(() => {
        // Enable close and submit button and change text of submit button back to "Create"
        document.getElementById("close-button").disabled = false;
        document.getElementById("submit-button").disabled = false;
        document.getElementById("submit-button").innerHTML = "Create";
    });
});