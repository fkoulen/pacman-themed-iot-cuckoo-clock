/*
    Retrieve all appointments from the API and display them in a table.

    @author F.S. Koulen
    @date 2023-09-16
 */

const API_URL = 'http://localhost/api/appointment/read.php';

fetch(API_URL).then(response => {
    response.json().then(data => {
        const appointments = data.records;

        if (response.status !== 200) { // Error occurred
            if (response.status === 404) { // No appointments found
                document.getElementById('appointments').innerHTML = '<tr><td colspan="4">No appointments found.</td></tr>';
            } else { // Other error
                document.getElementById('appointments').innerHTML = `<tr><td colspan="4">An error (${response.status}) occurred while fetching the data.</td></tr>`;
            }
        } else {
            let appointmentsHTML = '';
            appointments.forEach(appointment => {
                appointmentsHTML += `
                <tr>
                    <td>${appointment.name}</td>
                    <td>${appointment.start}</td>
                    <td><a href="edit.php?id=${appointment.id}" class="btn btn-primary">Edit</a></td>
                    <td><a href="delete.php?id=${appointment.id}" class="btn btn-danger">Delete</a></td>
                </tr>
            `;
            });
            document.getElementById('appointments').innerHTML = appointmentsHTML;
        }
    }).catch((reason) => {
        console.error(reason);
        document.getElementById('appointments').innerHTML = '<tr><td colspan="4">An error occurred while displaying the data.</td></tr>';
    });
}).catch((reason) => {
    console.error(reason);
    document.getElementById('appointments').innerHTML = '<tr><td colspan="4">An error occurred while fetching the data.</td></tr>';
});