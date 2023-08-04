# !/bin/sh

/usr/bin/mysqld_safe --datadir=/var/lib/mysql &

sed -i "s/skip-networking/# skip-networking/g" /etc/my.cnf.d/mariadb-server.cnf
sed -i "s/.*bind-address\s*=.*/bind-address=0.0.0.0\nport=3306/g" /etc/my.cnf.d/mariadb-server.cnf
sleep 3;

mysqladmin status 2> /dev/null
if [ $? -eq 0 ]; then
	if ! mysqladmin --wait=30 ping; then
		printf "mariadb is not running\n"
		exit 1
	fi
	eval "echo \"$(cat /tmp/query.sql)\"" | mariadb
else
	if ! mysqladmin --user=$MARIADB_ADMIN_USER --password=$MARIADB_ADMIN_PWD --wait=30 ping; then
		printf "mariadb is not running\n"
		exit 1
	fi
fi

mysqladmin --user=$MARIADB_ADMIN_USER --password=$MARIADB_ADMIN_PWD shutdown

/usr/bin/mysqld_safe --datadir=/var/lib/mysql