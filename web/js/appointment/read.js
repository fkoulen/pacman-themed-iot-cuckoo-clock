/**
 * Retrieve all upcoming appointments from the API and display them in a table.
 *
 * @author F.S. Koulen
 * @date 2023-09-16
 */

const API_APPOINTMENT_READ = `${BASE_URL}/api/appointment/read.php`;

fetch(API_APPOINTMENT_READ).then(response => {
    response.json()
        .then(data => {
            const appointments = data.records;

            if (response.status !== HttpCodes.OK) { // Error occurred
                if (response.status === HttpCodes.NOT_FOUND) { // No appointments found
                    handleReadAppointmentsError("No appointments found.")
                } else { // Other error
                    handleReadAppointmentsError(`An error (${response.status}) occurred while fetching the data.`)
                }
            } else { // If no error occurred, display the appointments in a table
                let appointmentsHTML = '';
                appointments.forEach(appointment => {
                    appointmentsHTML += `
                <tr>
                    <td class="col-4">${appointment.name}</td>
                    <td class="col-6">${moment(utcToLocal(appointment.start)).format("HH:mm - DD MMMM YYYY")}</td>
                    <td class="text-end"><a href="update.html?id=${appointment.id}" class="btn btn-primary">Edit</a></td>
                    <td class="text-end"><button class="btn btn-danger" onclick="deleteAppointment('${appointment.id}');" >Delete</button></td>
                </tr>
            `;
                });
                document.getElementById('appointments').innerHTML = appointmentsHTML;
            }
        })
        .catch(() => handleReadAppointmentsError("An error occurred while displaying the data."));
}).catch(() => handleReadAppointmentsError("An error occurred while fetching the data."));

/**
 * Handle the error by displaying an error message.
 *
 * @param message The error message to display.
 */
function handleReadAppointmentsError(message) {
    document.getElementById('appointments').innerHTML = `<tr><td colspan="4">${message}</td></tr>`;
}