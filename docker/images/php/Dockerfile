FROM php:8.1-fpm

RUN apt-get update && apt-get install -y git zip

RUN curl --silent --show-error https://getcomposer.org/installer | php && mv composer.phar /usr/local/bin/composer
RUN docker-php-ext-install mysqli && docker-php-ext-enable mysqli
RUN docker-php-ext-install pdo_mysql && docker-php-ext-enable pdo_mysql