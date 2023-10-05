/*
    Retrieve the latest measurement from the API and display it on the site.
    If no measurement is found, display an error message.

    If the refresh button is clicked, the latest measurement is retrieved again.

    @author F.S. Koulen
    @date 2023-09-16
 */

const API_MEASUREMENT_READ_LATEST = 'http://localhost/api/measurement/read_latest.php';

/**
 * Handle whether to display the measurement or the error message.
 *
 * @param error whether an error occurred
 */
function handleDisplayState(error) {
    document.getElementById('measurement-spinner').classList.add('d-none');
    if (error) {
        document.getElementById('measurement-container').classList.add('d-none');
        document.getElementById('measurement-error').classList.remove('d-none');
    } else {
        document.getElementById('measurement-container').classList.remove('d-none');
        document.getElementById('measurement-error').classList.add('d-none');
    }
}

/**
 * Retrieve the latest measurement from the API and display it on the site if successful.
 */
function getLatestMeasurement() {
    document.getElementById('measurement-spinner').classList.remove('d-none');
    document.getElementById('measurement-container').classList.add('d-none');
    let error = false;

    fetch(API_MEASUREMENT_READ_LATEST).then(response => {
        response.json().then(data => {
            if (response.status !== 200) { // Error occurred
                error = true;
                if (response.status === 404) { // No measurement found
                    console.log("No measurement found.");
                } else { // Other error
                    console.log(`An error (${response.status}) occurred while fetching the data.`);
                }
            } else {
                const utc = moment.utc(data.measurement_time);
                // measurement_time is a string in the format of "YYYY-MM-DD HH:MM:SS"
                document.getElementById('measurement-time').innerHTML = moment(utc).local().fromNow();
                document.getElementById('measurement-temperature').innerHTML = data.temperature;
                document.getElementById('measurement-humidity').innerHTML = data.humidity;
                document.getElementById('measurement-container').classList.remove('d-none');
            }
        }).catch((reason) => {
            error = true;
            console.error(reason);
        }).finally(() => {
            handleDisplayState(error);
        });
    }).catch((reason) => {
        error = true;
        console.error(reason);
    }).finally(() => {
        if (error) {
            handleDisplayState(error);
        }
    });
}

getLatestMeasurement();


document.getElementById('refresh-button').addEventListener('click', function () {
    getLatestMeasurement();
});