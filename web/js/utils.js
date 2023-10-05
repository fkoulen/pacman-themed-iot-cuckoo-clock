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


function setFormLimitations() {
    // Set max length of text input for name
    document.getElementById("name").maxLength = MAX_APPOINTMENT_NAME_LENGTH;

    // Set min date to today for input for appointment start time
    document.getElementById("start").min = moment().format("YYYY-MM-DDTHH:mm").substring(0, LENGTH_DATE_TIME);
}