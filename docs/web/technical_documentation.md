# Technical Documentation

> Your technical documentation should contain information about the design decisions you made, the problems you
> encountered and how you solved them. It should also contain information about the technologies you used and why you
> used them. It should also contain information about the structure of your website, and how the different parts of your
> website interact with each other.

> In your technical documentation you should also describe how you tested your application, and how you deployed your
> application.

## Technologies Used

### Front-end

<figure class="inline start" markdown>
  ![HTML5](../assets/web/technical_documentation/html5.png){ width="150" }
  <figcaption>HTML</figcaption>
</figure>
<figure class="inline" markdown>
  ![CSS3](../assets/web/technical_documentation/css3.png){ width="150" }
  <figcaption>CSS</figcaption>
</figure>
<figure markdown>
  ![Bootstrap](../assets/web/technical_documentation/bootstrap.png){ width="150" }
  <figcaption>Bootstrap</figcaption>
</figure>
<figure class="inline end" markdown>
  ![Moment.js](../assets/web/technical_documentation/momentjs.png){ width="150" }
  <figcaption>Moment.js</figcaption>
</figure>
<figure markdown>
  ![JavaScript](../assets/web/technical_documentation/javascript.png){ width="150" }
  <figcaption>JavaScript</figcaption>
</figure>

### Back-end

<figure class="inline start" markdown>
  ![PHP](../assets/web/technical_documentation/php.png){ width="150" }
  <figcaption>PHP & PDO (PHP extension)</figcaption>
</figure>
<figure class="inline" markdown>
  ![MariaDB](../assets/web/technical_documentation/mariadb.png){ width="150" }
  <figcaption>MariaDB</figcaption>
</figure>
<figure markdown>
  ![JSON](../assets/web/technical_documentation/json.png){ width="150" }
  <figcaption>JSON</figcaption>
</figure>


## Structure of the Website

All the code for the website is located in the `web` folder. The `web` folder contains the following:

- `api` folder: contains the API endpoints and all PHP files that are used to connect to the database. More information
  about the API endpoints and the file structure can be found in the [API Reference](../api_reference/).
- `js` folder:
    - `appointment` folder: contains the JavaScript files that are used to execute the CRUD operations for the
      appointments. In these files the API endpoints are called to execute the CRUD operations and the result is
      displayed on the website.
      -`measurement` folder: contains the Javascript file that is used to execute the read operation for the latest
      measurement. In this file the API endpoint is called to execute the read operation and the result is displayed
      on the website.
    - `lib` folder: contains the Javascript libraries that are used in the website. It currently contains the Moment.js
      library.
- `index.html`: the home page of the website. This page displays all the upcoming appointments and latest measurement.
  The needed Javascript files are included in this page to dynamically display the appointments and latest measurement.
  Moment.js is also included in this page to format the date and time.
- `update.html`: the update page of the website. This page displays the form to edit an appointment. The needed
  Javascript files are included in this page to dynamically display the appointment to edit. Moment.js is also included
  in this page to format the date and time.

## Design Decisions

**Front-end**

- I chose HTML to display the home page and the update page. HTML lets me define the foundation of the website by using
  different elements, defining where they should be placed and how they should be displayed.
- I choose to use Bootstrap to style the website. I have worked with Bootstrap on multiple occasions in the past and
  have a good knowledge of it. It allowed me to quickly style the website without having to spend too much time on
  writing all the CSS code myself. It also came pre-installed with this project.
- I chose to use Moment.js to format the date and time. I have worked with libraries similar to Moment.js in the past
  and have a good knowledge of it. It allowed me to easily display the time relatively and to be able to change the
  time from UTC to local and the other way around.
- I chose Javascript to dynamically display the content from the database and to be able to send content to the
  database. HTML is by itself not interactive. By loading the Javascript files into the HTML, I can easily make the
  website interactive without having to write all the code in the HTML file itself.

**Back-end**

- I chose PHP to connect to the database and to execute the CRUD operations. It allowed me to easily connect to the
  database and execute the CRUD operations. It also allowed me to easily secure the database queries by using prepared
  statements.
- I chose PDO to provide an abstraction layer. It allowed me to easily separate the database layer from the API
  endpoints. This makes it easier to maintain the code and to make changes to the database layer without having to
  change the API endpoints and vice versa.
- MariaDB is used to store the data from this project. It came pre-installed with this project. It is quite similar to
  MySQL and I have worked with MySQL in the past. It is used to store the appointments and measurements in tables that
  are defined in the [Database](../database/) section.
- I chose JSON to return the data from the database. JSON is largely used in web development since it is easy to read
  and write from different platforms. It also allowed me to easily return the data from the database to the website
  and my embedded device.

## Problems & solutions

While working on this project, I encountered some problems. In this table I will describe the problems I encountered
and how I solved them.

| Problem                                                                                                                                                                                                                                                                                                         | Solution                                                                                                                                                                                                               |
|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| One of the problems I encountered was finding a library that would help me format the date and time but was easy to load into my project. I first wanted to use date-fns since I have worked with it in the past, but I could not find a way to load it into my project (it was only available as npm package). | The solution was Moment.js. On their website they have a download link to download the library as a JavaScript file. This allowed me to easily load it into my project.                                                |
| Another problem I encountered was separating the database from the application. When I first started working on the website, I had loaded the appointments through PHP in my HTML file. This was not a good solution since it was not separated and would make it harder to maintain.                           | The solution was to create an API. This allowed me to separate the database from the application. PDO helped me tremendously with creating an abstraction layer to separate the database logic from the API endpoints. |

## Testing

All the code is manually tested on a local machine.

The API endpoints are tested with Postman. Every endpoint is tested with different inputs to make sure that the
endpoints work as expected and returned the correct status and message. For example, the endpoint to create an
appointment is tested with a valid input and with an invalid input. I then checked if the appointment was created
successfully in the database with the valid input and if an error returned with the invalid input. The same has been
done for the other endpoints.

For the website, I tested it in a similar way. I looked at the different scenarios that could happen and tested them
all. For example, I tested if the appointments were displayed correctly when there were no appointments, when there was
only one appointment and when there were multiple appointments. I tested if the latest measurement was displayed
correctly when there was no measurement and when there was a measurement. I tested if the inputs of the form were
validated correctly and whether the form could be submitted with valid and invalid inputs. I also tested and handled
what would happen if the update page was accessed with an invalid appointment ID.

I could go on and on with the different scenarios that I tested, but I think you get the point. I tried to test as many
scenarios as possible to make sure that the website works as expected and that the user gets the correct feedback.

## Deployment

If you want to get the website up and running on your local machine, you can follow the steps below.

### Prerequisites

- Docker & Docker Compose
- Git
- A web browser
- A terminal

### Steps

1. Clone the repository by running the following command in your
   terminal: `git clone https://gitlab.fdmci.hva.nl/IoT/2023-2024-semester-1/individual-project/iot-koulenf.git`
2. Navigate to the newly created folder `iot-koulenf` in your terminal.
3. Run the following command in your terminal: `docker-compose up -d`
4. Open your browser and navigate to `http://localhost`
5. You should now see the home page of the website.