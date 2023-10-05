/*
    Retrieve the latest measurement from the API and display it on the site.

    @author F.S. Koulen
    @date 2023-09-16
 */

const API_MEASUREMENT_READ_LATEST = 'http://localhost/api/measurement/read_latest.php';

fetch(API_MEASUREMENT_READ_LATEST).then(response => {
    response.json().then(data => {
        if (response.status !== 200) { // Error occurred
            if (response.status === 404) { // No measurement found
                console.log("No measurement found.");
            } else { // Other error
                console.log(`An error (${response.status}) occurred while fetching the data.`);
            }
        } else {
            console.log(data);
        }
    }).catch((reason) => {
        console.error(reason);
        document.getElementById('appointments').innerHTML = '<tr><td colspan="4">An error occurred while displaying the data.</td></tr>';
    });
}).catch((reason) => {
    console.error(reason);
    document.getElementById('appointments').innerHTML = '<tr><td colspan="4">An error occurred while fetching the data.</td></tr>';
});