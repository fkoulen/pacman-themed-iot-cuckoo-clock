CREATE TABLE `appointment`
(
    `id`    int(11)     NOT NULL AUTO_INCREMENT,
    `name`  varchar(50) NOT NULL,
    `start` datetime    NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB
  AUTO_INCREMENT = 5
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_general_ci;

CREATE TABLE `measurement`
(
    `id`               int(11)       NOT NULL AUTO_INCREMENT,
    `measurement_time` datetime      NOT NULL DEFAULT current_timestamp(),
    `temperature`      decimal(4, 2) NOT NULL,
    `humidity`         decimal(4, 2) NOT NULL,
    PRIMARY KEY (`id`)
) ENGINE = InnoDB
  AUTO_INCREMENT = 68
  DEFAULT CHARSET = utf8mb4
  COLLATE = utf8mb4_general_ci;