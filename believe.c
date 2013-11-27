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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_believe.h"

/* If you declare any globals in php_believe.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(believe)
*/

/* True global resources - no need for thread safety here */
static int le_believe;

/* {{{ believe_functions[]
 *
 * Every user visible function must have an entry in believe_functions[].
 */
const zend_function_entry believe_functions[] = {
	PHP_FE(confirm_believe_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(believe_call,NULL)
	PHP_FE(believe_error,NULL)
	PHP_FE_END	/* Must be the last line in believe_functions[] */
};
/* }}} */

/* {{{ believe_module_entry
 */
zend_module_entry believe_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"believe",
	believe_functions,
	PHP_MINIT(believe),
	PHP_MSHUTDOWN(believe),
	PHP_RINIT(believe),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(believe),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(believe),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_BELIEVE
ZEND_GET_MODULE(believe)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("believe.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_believe_globals, believe_globals)
    STD_PHP_INI_ENTRY("believe.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_believe_globals, believe_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_believe_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_believe_init_globals(zend_believe_globals *believe_globals)
{
	believe_globals->global_value = 0;
	believe_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(believe)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(believe)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(believe)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(believe)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(believe)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "believe support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

PHP_FUNCTION(believe_error){
    char * ferr = dlerror();
    if(ferr!=NULL){
    	RETURN_STRINGL(ferr,strlen(ferr),1);
	}else{
		RETURN_FALSE;
	}
}

PHP_FUNCTION(believe_call)
{
	char *arg_so = NULL;
	int arg_so_len=0;
    char * arg_func = NULL;
    int arg_func_len = 0;
    char * arg_input = NULL;
    int arg_input_len = 0;

	char *strg;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sss", &arg_so, &arg_so_len,&arg_func,&arg_func_len,&arg_input,&arg_input_len) == FAILURE) {
		return;
	}

	char *(* func)(char * );
	void * fhandle =dlopen(arg_so,RTLD_LAZY);
	if(fhandle==NULL){
		RETURN_FALSE;
	}

	char * ferr = dlerror();
	if(ferr!=NULL){
		RETURN_FALSE;
	}
	func = dlsym(fhandle,arg_func);
	ferr = dlerror();
	if(ferr!=NULL){
		RETURN_FALSE;
	}
	char * result = (*func)(arg_input);
	if(result==NULL){
		RETURN_FALSE;
	}else{
		RETURN_STRINGL(result,strlen(result),1);
	}
}
/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_believe_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_believe_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "believe", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
