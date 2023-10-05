/*
    Retrieve all upcoming appointments from the API and display them in a table.

    @author F.S. Koulen
    @date 2023-09-16
 */

const API_APPOINTMENT_READ = 'http://localhost/api/appointment/read.php';

fetch(API_APPOINTMENT_READ).then(response => {
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
                    <td class="col-4">${appointment.name}</td>
                    <td class="col-6">${appointment.start}</td>
                    <td class="text-end"><a href="edit.html?id=${appointment.id}" class="btn btn-primary">Edit</a></td>
                    <td class="text-end"><button class="btn btn-danger" onclick="deleteAppointment('${appointment.id}');" >Delete</button></td>
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