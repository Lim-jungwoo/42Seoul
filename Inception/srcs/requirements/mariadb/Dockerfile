FROM alpine:3.13

RUN apk update && \
	apk add mariadb mariadb-client && \
	wget -O /usr/bin/dumb-init https://github.com/Yelp/dumb-init/releases/download/v1.2.5/dumb-init_1.2.5_x86_64 && \
	chmod +x /usr/bin/dumb-init && \
	mkdir -p /run/mysqld /var/lib/mysql && \
	mariadb-install-db --datadir=/var/lib/mysql --auth-root-authentication-method=normal && \
	chown -R mysql:mysql /var/lib/mysql /run/mysqld

COPY conf/query.sql /tmp/query.sql
COPY tools/script.sh /tmp/script.sh

RUN chmod +x /tmp/script.sh

ENTRYPOINT [ "/usr/bin/dumb-init", "--" ]

CMD [ "sh", "-c", "/tmp/script.sh" ]