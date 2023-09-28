# Database

> Your database should be well documented. On your portfolio you describe how your database is designed and how it
> works. You include a diagram of your database made in MySQL Workbench.

- [ ] The database is normalized into a correct relation database. Tool: MySQL Workbench
- [x] All the tables in the database have a logical and correct primary key.
- [x] The structure of all the columns and tables is in such way that there is no data saved in a wrong format.
- [ ] The build script of your MySQL Database should be stores as .sql files in your portfolio website with detailed
  instructions on how to use.

## Build script

[SQL Build file](./seed.sql){:download="seed.sql"}

## Database diagram

<figure markdown>
  ![Database Diagram](database_diagram.png){: style="width:600px"}
  <figcaption>Database diagram</figcaption>
</figure>

The database currently has two tables.

The table called `appointment` has the following columns:

- `id` - The primary key of the table. It is an auto incrementing integer. It is not nullable. I have chosen for this
  type because it is a simple way to create a primary key. I first wanted to use a UUID, but I decided against it
  since it is not supported by MySQL Workbench.
- `name` - The name of the appointment. It is of type `varchar(50)`. It is not nullable. I have chosen for this type
  because the name of an appointment should not be longer than 50 characters since the LCD only has 16 characters per
  line.
- `start` - The start date and time of the appointment. It is of type `datetime`. It is not nullable. I have chosen for
  this type because it supports storing both the date and time of the appointment in one column.

The table called `measurement` has the following columns:

- `id` - The primary key of the table. It is an auto incrementing integer. It is not nullable. I have chosen for this
  type because it is a simple way to create a primary key. I first wanted to use a UUID, but I decided against it
  since it is not supported by MySQL Workbench.
- `measurement_time` - The time of the measurement. It is of type `datetime`. It is not nullable. I have chosen for
  this type because it supports storing both the date and time of the measurement in one column.
- `temperature` - The temperature at the time of measurement. It is of type `decimal(4,2)`. The length is 4 and the
  precision is 2 (example: 24.50). It is not nullable. I have chosen for this type because it supports storing a
  temperature with two decimals. The temperature is of length 4 since the sensor can only measure temperatures between
  0 and 50 degrees Celsius.
- `humidity` - The humidity at the time of measurement. It is of type `decimal(4,2)`. The length is 4 and the
  precision is 2 (example: 54.50). It is not nullable. I have chosen for this type because it supports storing a
  humidity with two decimals. The humidity is of length 4 since the sensor can only measure humidity between 0 and 100
  percent.