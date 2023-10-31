/**
 * Retrieve the latest measurement from the API and display it on the site.
 * If no measurement is found, display an error message.
 *
 * If the refresh button is clicked, the latest measurement is retrieved again.
 *
 * @author F.S. Koulen
 * @date 2023-09-16
 */

const API_MEASUREMENT_READ_LATEST = 'http://localhost/api/measurement/read_latest.php';

/**
 * Handle whether to display the measurement or the error message.
 *
 * @param errorMessage the error message to display
 */
function handleDisplayState(errorMessage) {
    document.getElementById('measurement-spinner').classList.add('d-none');
    if (errorMessage) {
        document.getElementById('measurement-container').classList.add('d-none');
        document.getElementById('measurement-error').classList.remove('d-none');
        document.getElementById('measurement-error-description').innerHTML = errorMessage;
    } else {
        document.getElementById('measurement-container').classList.remove('d-none');
        document.getElementById('measurement-error').classList.add('d-none');
    }
}

/**
 * Request a new measurement from the embedded device. Show an alert if the request failed.
 * Finally, retrieve the latest measurement from the API.
 */
function requestMeasurement() {
    document.getElementById('measurement-spinner').classList.remove('d-none');
    document.getElementById('measurement-container').classList.add('d-none');

    fetch(REQUEST_MEASUREMENT_URL, {method: 'GET'})
        .then(response => {
            response.json()
                .then(data => {
                    if (data.response !== HttpCodes.CREATED) {
                        alert("Failed to request new measurement. Error: " + data.response);
                    }
                })
                .catch((reason) => alert("Failed to request new measurement. Error: " + reason))
        })
        .catch((reason) => alert("Failed to request new measurement. Error: " + reason))
        .finally(() => getLatestMeasurement());
}

/**
 * Retrieve the latest measurement from the API and display it on the site if successful.
 */
function getLatestMeasurement() {
    let errorMessage = "";

    fetch(API_MEASUREMENT_READ_LATEST)
        .then(response => {
            response.json()
                .then(data => {
                    if (response.status !== HttpCodes.OK) { // Error occurred
                        if (response.status === HttpCodes.NOT_FOUND) { // No measurement found
                            errorMessage = "No measurement found.";
                        } else { // Other error
                            errorMessage = `An error (${response.status}) occurred while fetching the data.`;
                        }
                    } else {
                        const utc = moment.utc(data.measurement_time);
                        // measurement_time is a string in the format of "YYYY-MM-DD HH:MM:SS"
                        document.getElementById('measurement-time').innerHTML = moment(utc).local().fromNow();
                        document.getElementById('measurement-temperature').innerHTML = data.temperature;
                        document.getElementById('measurement-humidity').innerHTML = data.humidity;
                        document.getElementById('measurement-container').classList.remove('d-none');
                    }
                })
                .catch(() => errorMessage = "An error occurred while displaying the data.")
                .finally(() => handleDisplayState(errorMessage));
        })
        .catch(() => errorMessage = "An error occurred while fetching the data.")
        .finally(() => {
            if (errorMessage) handleDisplayState(errorMessage);
        });
}

requestMeasurement();


document.getElementById('refresh-button').addEventListener('click', function () {
    requestMeasurement();
});