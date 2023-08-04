# !/bin/sh

grep -E "listen = 127.0.0.1" /etc/php7/php-fpm.d/www.conf 2> /dev/null

if [ $? -eq 0 ]; then
	sed -i "s/.*listen = 127.0.0.1.*/listen = 9000/g" /etc/php7/php-fpm.d/www.conf
	echo "env[MARIADB_HOST] = \$MARIADB_HOST" >> /etc/php7/php-fpm.d/www.conf
	echo "env[MARIADB_USER] = \$MARIADB_USER" >> /etc/php7/php-fpm.d/www.conf
	echo "env[MARIADB_PWD] = \$MARIADB_PWD" >> /etc/php7/php-fpm.d/www.conf
	echo "env[MARIADB_DB] = \$MARIADB_DB" >> /etc/php7/php-fpm.d/www.conf
fi

if [ ! -f "/var/www/wordpress/wp-config.php" ]; then
	cp /tmp/wp-config.php /var/www/wordpress/wp-config.php
	sleep 5;

	if ! mysqladmin -h $MARIADB_HOST --user=$MARIADB_USER --password=$MARIADB_PWD --wait=60 ping; then
		printf "mariadb is not running\n";
		exit 1
	fi
	wp core install --url="$WP_URL" --title="$WP_TITLE" --admin_user="$WP_ADMIN_USER" --admin_password="$WP_ADMIN_PWD" --admin_email="$WP_ADMIN_EMAIL" --skip-email --path=/var/www/wordpress
	wp plugin update --all --path=/var/www/wordpress
	wp user create $WP_USER $WP_USER_EMAIL --role=author --user_pass=$WP_USER_PWD --path=/var/www/wordpress
fi

php-fpm7 --nodaemonize
