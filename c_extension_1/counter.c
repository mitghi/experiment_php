#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_test.h"

#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

ZEND_DECLARE_MODULE_GLOBALS(test)

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("counter.scale", "1", PHP_INI_ALL, OnUpdateLong, scale,
		zend_test_globals, test_globals)
PHP_INI_END()


PHP_FUNCTION(counter_count_commas)
{
    zend_string *input;
    size_t commas = 0;

	ZEND_PARSE_PARAMETERS_START(0, 1)
        Z_PARAM_OPTIONAL
		Z_PARAM_STR(input)
    ZEND_PARSE_PARAMETERS_END();

    char *values = ZSTR_VAL(input);

    for (int i =0; i < strlen(values); i++) {
        if (values[i] == ',') {
            commas += 1;
        }
    }

    RETVAL_LONG(commas);
}

static PHP_GINIT_FUNCTION(test)
{
#if defined(COMPILE_DL_BCMATH) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
}


PHP_MINIT_FUNCTION(counter)
{
	REGISTER_INI_ENTRIES();

	return SUCCESS;
}

PHP_MINFO_FUNCTION(counter)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "counter support", "enabled");
	php_info_print_table_end();
}

ZEND_BEGIN_ARG_INFO(arginfo_counter_count_commas, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

static const zend_function_entry counter_functions[] = {
	PHP_FE(counter_count_commas, arginfo_counter_count_commas)
	PHP_FE_END
};

zend_module_entry counter_module_entry = {
	STANDARD_MODULE_HEADER,
	"counter",
	counter_functions,
	PHP_MINIT(counter),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(counter),
	PHP_TEST_VERSION,
	PHP_MODULE_GLOBALS(test),
	PHP_GINIT(test),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_COUNTER
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(counter)
#endif
