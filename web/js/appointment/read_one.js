/*
    Retrieve the id from the url and send a request to the API to get the appointment data.
    If the appointment was retrieved successfully, fill the form with the appointment data.
    If an error occurred, display the error message.

    @author F.S. Koulen
    @date 2023-09-18
 */


// Get the id from the url
const id = window.location.href.split("=")[1];

setFormLimitations();

const API_APPOINTMENT_READ_ONE = `${BASE_URL}/api/appointment/read_one.php?id=${id}`;

/**
 * Handle error by displaying error message and logging error to console.
 * @param reason The reason why the error occurred.
 */
function handleError(reason) {
    document.getElementById("loading").classList.add("d-none");
    document.getElementById("error").classList.remove("d-none");
    document.getElementById("error").innerHTML =
        `An error occurred while loading the appointment. 
        Please <a href="${window.location.href}" class="alert-link">refresh the page</a> and try again 
        or go back to the <a class="alert-link" href='index.html'>home page</a>.
        <hr>
        <pre>${reason}</pre>`;
    console.error(reason);
}

// Add event listener to the page load event and send a request to the API to get the appointment data if the page has loaded
document.addEventListener("DOMContentLoaded", () => {
    fetch(API_APPOINTMENT_READ_ONE, {
        method: "GET",
    }).then(response => {
        response.json().then(data => {
            if (response.status !== 200) {
                handleError("Error: " + data.message);
                return;
            }
            document.getElementById("id").value = data.id;
            document.getElementById("name").value = data.name;
            document.getElementById("start").value = moment(utcToLocal(data.start)).format("YYYY-MM-DDTHH:mm");
            document.getElementById("loading").classList.add("d-none");
            document.getElementById("form").classList.remove("d-none");
        }).catch((reason) => {
            handleError(reason);
        });
    }).catch((reason) => {
        handleError(reason);
    });
});