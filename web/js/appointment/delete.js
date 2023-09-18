/*
    This file contains the function used to delete an appointment. It is called from the delete button in the table.
    The function uses the fetch API to send a DELETE request to the API. If the request is successful, the user is
    redirected to the index page. If an error occurs, the user is alerted with the error message.

    @author F.S. Koulen
    @date 2023-09-18
 */

const API_APPOINTMENT_DELETE = 'http://localhost/api/appointment/delete.php';

/**
 * Delete an appointment.
 *
 * @param id The ID of the appointment to delete.
 */
function deleteAppointment(id) {
    console.log('Deleting appointment with ID ' + id);
    fetch(API_APPOINTMENT_DELETE, {
        method: 'DELETE', body: JSON.stringify({id: id})
    }).then(response => {
        if (response.status === 200) {
            window.location.href = 'index.html';
        } else {
            response.json().then(data => {
                alert(data.message);
            }).catch((reason) => {
                console.error(reason);
                alert('An error occurred while deleting the appointment.');
            });
        }
    }).catch((reason) => {
        console.error(reason);
        alert('An error occurred while deleting the appointment.');
    });
}
