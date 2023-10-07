# Database

> Your database should be well documented. On your portfolio you describe how your database is designed and how it
> works. You include a diagram of your database made in MySQL Workbench.

- [x] The database is normalized into a correct relation database. Tool: MySQL Workbench
- [x] All the tables in the database have a logical and correct primary key.
- [x] The structure of all the columns and tables is in such way that there is no data saved in a wrong format.
- [x] The build script of your MySQL Database should be stores as .sql files in your portfolio website with detailed
  instructions on how to use.

## Creating the database

The build script is a SQL script that creates the database called `iot` and the tables called `appointment` and
`measurement`.

### Pre-requisites

- MySQL server
- MySQL Workbench
- [Build script](./seed.sql){:download="seed.sql"}

### Steps

1. Open MySQL Workbench.  
   ![MySQL Workbench](../assets/web/database/step_1.png){: style="height:150px"}
2. Connect to your MySQL server. You can do this by either clicking on `Database` and then `Connect to Database...` or
   by clicking on one of the connections in the `MySQL Connections` pane.
   ![Connect to Database](../assets/web/database/step_2.png){: style="height:300px"}
3. Open the build script in MySQL Workbench. You can do this by clicking on `File` and then `Open SQL Script...`. Then
   navigate to the build script and click on `Open`.  
   ![Open SQL Script](../assets/web/database/step_3.png){: style="height:300px"}
4. Optional: Change the name of the database in the build script. You can do this by changing the value of the
   variable `defined_schema` on line 1.  
   ![Change database name](../assets/web/database/step_4.png){: style="height:100px"}
5. Run the build script by clicking on the lightning bolt icon in the toolbar. This will create the database and the
   tables. If you have changed the name of the database, you will have to change the name of the database in the
   .env file as well.  
   ![Run build script](../assets/web/database/step_5.png){: style="width:600px"}

## Database diagram

<figure markdown>
  ![Database Diagram](../assets/web/database/database_diagram.png){: style="width:600px"}
  <figcaption>Database diagram</figcaption>
</figure>

The database has two tables.

The table called `appointment` has the following columns:

- `id` - The primary key of the table. It is an auto incrementing integer. It is not nullable. I have chosen for this
  type because it is a simple way to create a primary key. I first wanted to use a UUID, but I decided against it
  since it is not supported by MySQL Workbench.
- `name` - The name of the appointment. It is of type `varchar(13)`. It is not nullable. I have chosen for this type
  because the name of an appointment should not be longer than 13 characters since the LCD only has 16 characters per
  line and the name of the appointment is displayed on the first line with a prefix of `[digit]: `. The length of the
  prefix is 3 so the name of the appointment can be 13 characters long.
- `start` - The start date and time of the appointment. It is of type `datetime`. It is not nullable. I have chosen for
  this type because it supports storing both the date and time of the appointment in one column. It is stored in UTC.

The table called `measurement` has the following columns:

- `id` - The primary key of the table. It is an auto incrementing integer. It is not nullable. I have chosen for this
  type because it is a simple way to create a primary key. I first wanted to use a UUID, but I decided against it
  since it is not supported by MySQL Workbench.
- `measurement_time` - The time of the measurement. It is of type `datetime`. It is not nullable. I have chosen for
  this type because it supports storing both the date and time of the measurement in one column. It is stored in UTC.
- `temperature` - The temperature at the time of measurement. It is of type `decimal(3,1)`. The length is 3 and the
  precision is 1 (example: 24.5). It is not nullable. I have chosen for this type because it supports storing a
  temperature with one decimal. The temperature is of length 3 with precision 1 since the sensor can only measure
  temperatures between 0 and 50 degrees Celsius with one decimal.
- `humidity` - The humidity at the time of measurement. It is of type `int(2)`. It is not nullable. I have chosen for
  this type with length 2 because it supports storing an integer and the sensor can only measure between 20 and 90
  percent with no decimals.