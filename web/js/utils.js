/**
 * This file contains utility functions that are used in multiple files.
 *
 * @author F.S. Koulen
 * @date 2023-10-16
 */

const HttpCodes = {
    OK: 200,
    CREATED: 201,
    BAD_REQUEST: 400,
    NOT_FOUND: 404,
    INTERNAL_SERVER_ERROR: 500
}

/**
 * Return a UTC date in local time
 *
 * @param date date in utc
 * @returns date in local time
 */
function utcToLocal(date) {
    return moment.utc(date).local();
}

/**
 * Return a local date in UTC
 *
 * @param date date in local time
 * @returns date in utc
 */
function localToUtc(date) {
    return moment(date).utc();
}


/**
 * Set limitations for the form.
 *
 * The name input has a maximum length of MAX_APPOINTMENT_NAME_LENGTH.
 * The start input has a minimum date of today.
 */
function setFormLimitations() {
    // Set max length of text input for name
    document.getElementById("name").maxLength = MAX_APPOINTMENT_NAME_LENGTH;

    // Set min date to today for input for appointment start time
    document.getElementById("start").min = moment().format("YYYY-MM-DDTHH:mm").substring(0, LENGTH_DATE_TIME);
}

/**
 * Get the appointment object from the form data.
 * The start time is converted to UTC and formatted to the correct format.
 *
 * @param event The event that triggered the function
 * @returns {{}} The appointment object
 */
function getAppointmentObject(event) {
    // Get form data
    const formData = new FormData(event.target);
    const appointment = {};
    formData.forEach((value, key) => {
        appointment[key] = value;
    });

    // Set start time to UTC
    appointment.start = moment(localToUtc(appointment.start)).format("YYYY-MM-DD HH:mm:ss");
    return appointment;
}