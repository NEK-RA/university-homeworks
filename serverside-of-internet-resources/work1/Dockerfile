FROM php:7.4-apache
EXPOSE 80
RUN docker-php-ext-install pdo pdo_mysql mysqli
ADD index.php /var/www/html/
ADD style.css /var/www/html/

