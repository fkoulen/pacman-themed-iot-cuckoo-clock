# API Reference

> Your API Reference should contain information about the endpoints of your API, and how to use them. It should also
> contain information about the data that is returned by your API.

> The REST API documentation explains the input, output, and endpoint URL for each API to help you use them effectively.

> There is a full explanation of the used technology.

> All the design choices are explained in detail of the front-end and back-end of the web application.

## General Information

* The API is fully written in PHP.
* It uses PHP Data Objects (PDO), a PHP extension, to provide an abstraction layer.
* There is one Database class. This class contains all the necessary setup to connect to the database.
* There is a class for each object (which corresponds to a table in the database) which contains functions to operate on
  the object. These functions describe how to execute the basic Create, Read, Update, Delete (CRUD) actions in SQL.
* For each object a folder is created. In this folder the CRUD operations all have separate file. These files contain
  code on how to execute that action. It validates the received data if any, creates an
  object, executes the action and returns the result in JSON format.
* The API can be used by any application that can send HTTP requests and parse JSON. This includes web applications,
  mobile applications and embedded systems. This is why the JSON format is used.
* The API can be reached at `http://localhost/api/`.

## Endpoints

The API currently has the following endpoints:

### Appointment

??? abstract "GET /appointment/read.php - Returns all appointments"

      **Parameters**  
      None.
      
      **Responses**  
  
      * **200 OK** - The request was successful.   
        The response contains a JSON array with all appointments in `records`.  
  
        Example:  
  
        ```json
        {
            "records": [
                {
                    "id": "6b77b957-54d0-11ee-bff1-0242ac120003",
                    "name": "Dentist",
                    "start": "2023-09-20 21:53:00"
                },
                {
                    "id": "25dbfc4c-54d0-11ee-bff1-0242ac120003",
                    "name": "Doctor",
                    "start": "2023-09-28 12:25:00"
                }
            ]
        }
        ```
  
      * **404 Not Found** - There are no appointments in the database.   
        The response contains a message about there being no appointments in `message`.
  
        Example: 
  
        ```json
        {
            "message": "No appointments found."
        }
        ```

??? abstract "GET /appointment/read_one.php - Returns a single appointment"

    **Parameters**  

    * **id** - The id of the appointment.
    
    **Responses**  

    * **200 OK** - The request was successful.   
        The response contains a JSON object with the appointment.  

        Example:  

        ```json
        {
          "id": "77a702e8-5634-11ee-8f02-0242ac120002",
          "name": "Nieuwe Afspraak",
          "start": "2023-09-24 17:14:00"
        }
        ```

    * **404 Not Found** - The appointment could not be found.   
        The response contains a message about the error in `message`.

        Example: 

        ```json
        {
            "message": "Appointment does not exist."
        }
        ```

??? abstract "POST /appointment/create.php - Creates a new appointment"

     **Parameters**  
      JSON object with the following properties:  

     * **name** - The name of the appointment.  
     * **start** - The start date and time of the appointment in the format `YYYY-MM-DDTHH:MM:SS`.  
      
     **Responses**  
  
     * **201 Created** - The appointment was created successfully.   
          The response contains the following message in `message`:  `Appointment was created.`.
      
          Example:  
      
          ```json
            {
               "message": "Appointment was created."
            }
          ```
  
     * **400 Bad Request** - The appointment could not be created.   
          The appointment could not be created since there is missing data. 
          The response contains a message about the error in `message`.
      
          Example: 
      
          ```json
          {
              "message": "Unable to create appointment. Data is incomplete."
          }
          ```

     * **503 Service Unavailable** - The appointment could not be created.   
          The appointment could not be created since the database is unavailable. 
          The response contains a message about the error in `message`.
      
          Example: 
      
          ```json
          {
              "message": "Unable to create appointment. Service unavailable."
          }
          ```

??? abstract "UPDATE /appointment/update.php - Update a single appointment"

    **Parameters**

    * **id** - The id of the appointment.
    * **name** - The name of the appointment.
    * **start** - The start date and time of the appointment in the format `YYYY-MM-DDTHH:MM:SS`.

    **Responses**

    * **200 OK** - The appointment was successfully updated.   
        The response contains a message about the success in `message`.

        Example:  

        ```json
        {
            "message": "Appointment was updated."
        }
        ```

    * **400 Bad Request** - The appointment could not be updated.

        The appointment could not be updated since there is missing data or the appointment does not exist. 
        The response contains a message about the error in `message`.

        Example: 

        ```json
        {
            "message": "Unable to update appointment. Please check if the appointment exists."
        }
        ```  

??? abstract "DELETE /appointment/delete.php - Delete a single appointment"

    **Parameters**  

    * **id** - The id of the appointment.

    **Responses**

    * **200 OK** - The appointment was successfully deleted.   
        The response contains a message about the success in `message`.

        Example:  

        ```json
        {
            "message": "Appointment was deleted."
        }
        ```

    * **400 Bad Request** - The appointment could not be deleted.

        The appointment could not be deleted since the appointment does not exist or could not be retrieved. 
        The response contains a message about the error in `message`.

        Example: 

        ```json
        {
            "message": "Unable to delete appointment. The appointment does not exist or could not be retrieved."
        }
        ```

### Measurement

??? abstract "POST /measurement/create.php - Creates a new measurement"

     **Parameters**  
      JSON object with the following properties:  

     * **temperature** - The temperature in Celsius degrees in DECIMAL(4,2).  
     * **humidity** - The humidity in percentage in DECIMAL(4,2).  
      
     **Responses**  
  
     * **201 Created** - The appointment was created successfully.   
          The response contains a message about the success in `message`.  
    
          Example:  
      
          ```json
            {
               "message": "Measurement was created."
            }
          ```
  
     * **400 Bad Request** - The measurement could not be created.   
          The measurement could not be created since there is missing data. 
          The response contains a message about the error in `message`.
      
          Example: 
      
          ```json
          {
              "message": "Unable to create measurement. Data is incomplete."
          }
          ```

     * **503 Service Unavailable** - The measurement could not be created.   
          The measurement could not be created since the database is unavailable. 
          The response contains a message about the error in `message`.
      
          Example: 
      
          ```json
          {
              "message": "Unable to create measurement. Service unavailable."
          }
          ```

??? abstract "GET /appointment/read_latest.php - Returns the most recent measurement"

    **Parameters**  

    None.
    
    **Responses**  

    * **200 OK** - The request was successful.   
        The response contains a JSON object with the measurement.  

        Example:  

        ```json
        {
            "id": "69",
            "measurement_time": "2023-10-05 15:47:15",
            "temperature": 25.2,
            "humidity": 49
        }
        ```

    * **404 Not Found** - The measurement could not be found.   
        The response contains a message about the error in `message`.

        Example: 

        ```json
        {
            "message": "No measurements found."
        }
        ```
