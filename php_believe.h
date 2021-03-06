/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_BELIEVE_H
#define PHP_BELIEVE_H

extern zend_module_entry believe_module_entry;
#define phpext_believe_ptr &believe_module_entry

#ifdef PHP_WIN32
#	define PHP_BELIEVE_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_BELIEVE_API __attribute__ ((visibility("default")))
#else
#	define PHP_BELIEVE_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(believe);
PHP_MSHUTDOWN_FUNCTION(believe);
PHP_RINIT_FUNCTION(believe);
PHP_RSHUTDOWN_FUNCTION(believe);
PHP_MINFO_FUNCTION(believe);

PHP_FUNCTION(confirm_believe_compiled);	/* For testing, remove later. */
PHP_FUNCTION(believe_call);
PHP_FUNCTION(believe_error);
/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(believe)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(believe)
*/

/* In every utility function you add that needs to use variables 
   in php_believe_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as BELIEVE_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define BELIEVE_G(v) TSRMG(believe_globals_id, zend_believe_globals *, v)
#else
#define BELIEVE_G(v) (believe_globals.v)
#endif

#endif	/* PHP_BELIEVE_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
