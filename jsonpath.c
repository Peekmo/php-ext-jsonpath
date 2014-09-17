#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <php.h>
#include "php_jsonpath.h"

zend_class_entry* jsonpath_ce_jsonstore;

static zend_function_entry store_methods[] = {
    PHP_ME(JsonStore, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    {NULL, NULL, NULL}
};

zend_module_entry jsonpath_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_JSONPATH_EXTNAME,
    NULL,
    PHP_MINIT(jsonpath),
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_JSONPATH_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// -------------------------------- Install the module
#ifdef COMPILE_DL_JSONPATH
ZEND_GET_MODULE(jsonpath)
#endif

PHP_MINIT_FUNCTION(jsonpath) {
    jsonpath_init_jsonstore(TSRMLS_C);
}

// Init class JsonStore
void jsonpath_init_jsonstore(TSRMLS_D) {
    zend_class_entry ce;

    INIT_CLASS_ENTRY(ce, "Peekmo\\JsonPath\\JsonStore", store_methods);

    jsonpath_ce_jsonstore = zend_register_internal_class(&ce TSRMLS_CC);

    zend_declare_property_null(jsonpath_ce_jsonstore, DATA_PROPERTY, DATA_LENGTH, ZEND_ACC_PRIVATE TSRMLS_CC);
}


// ------------------ Class methods
PHP_METHOD(JsonStore, __construct) {
    zval* data;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data) == FAILURE) {
        php_printf("FAIL to get parameters from JsonStore constructor");
        return;
    }

    zend_update_property(jsonpath_ce_jsonstore, getThis(), DATA_PROPERTY, DATA_LENGTH, data TSRMLS_CC);
}
