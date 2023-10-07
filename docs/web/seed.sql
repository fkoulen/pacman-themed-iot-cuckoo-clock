SET @defined_schema = 'iot';

-- Create a prepared statement to create a schema with the specified name
SET @sql = CONCAT('CREATE SCHEMA `', @defined_schema, '`');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

-- Create a prepared statement to use the specified schema
SET @sql = CONCAT('USE `', @defined_schema, '`');
PREPARE stmt FROM @sql;
EXECUTE stmt;
DEALLOCATE PREPARE stmt;

CREATE TABLE `appointment`
(
    `id`    int(11)     NOT NULL AUTO_INCREMENT,
    `name`  varchar(13) NOT NULL,
    `start` datetime    NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_general_ci;


CREATE TABLE `measurement`
(
    `id`               int(11)       NOT NULL AUTO_INCREMENT,
    `measurement_time` datetime      NOT NULL DEFAULT current_timestamp(),
    `temperature`      decimal(3, 1) NOT NULL,
    `humidity`         int(2)        NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_general_ci;