<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the installation.
 * You don't have to use the web site, you can copy this file to "wp-config.php"
 * and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * Database settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** Database settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', getenv('MARIADB_DB') );

/** Database username */
define( 'DB_USER', getenv('MARIADB_USER') );
// define( 'DB_USER', getenv('jlim2') );

/** Database password */
define( 'DB_PASSWORD', getenv('MARIADB_PWD') );
// define( 'DB_PASSWORD', getenv('12342') );

/** Database hostname */
define( 'DB_HOST', getenv('MARIADB_HOST') );

/** Database charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The database collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Change these to different unique phrases! You can generate these using
 * the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}.
 *
 * You can change these at any point in time to invalidate all existing cookies.
 * This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         'QNX21!9ek{?s|{NJ7iMZ{%&X5r+.`-QQC`+(-a=Df`j?=Wr)<7/5{|(/mg2Aifga');
define('SECURE_AUTH_KEY',  ',vUG-n.8*#(Y7O-[hzx]=h-oo+e? mSh@ey8f7idvr;/L.w=,h@<on|>^)&9==o$');
define('LOGGED_IN_KEY',    'R J,T`#$rF<|) X[|-f&}+@MD@dxb%GIV@lo6G@nu{3mAdB|=$Qw!xPT ja=92|q');
define('NONCE_KEY',        'koCJ_5pbn@.9)w9qmsz8/>7M~T_eN?Ex`hu8@pHEt#;a<:oS<P1o|,dVv@Z[KmyL');
define('AUTH_SALT',        '@4>xAtE}k1#F!X;8r<XC-&60XU,>^*~ /B-*u=ynjO|d&eC-wN^C`=)<!VqvMZ3-');
define('SECURE_AUTH_SALT', 'w{[i8}+sAqBZW//{}-t: zrC^aq&/CI|P&iFkg,43 d2PaLHL@c>@>l:|.toEwb0');
define('LOGGED_IN_SALT',   '1&^)t>+<N4d-NcU6ln.1f:y5PhO<IE^HT53S=OJyOF~j_@0)pr.k3F?n]{Y$QSHS');
define('NONCE_SALT',       'Ree!Pu)`;?-<CJ{e!*uNv[#)2}YOZs?JuLG}0 ;K^I0_?h=?,f+kW3[7.qr>dXY;');

/**#@-*/

/**
 * WordPress database table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* Add any custom values between this line and the "stop editing" line. */



/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';