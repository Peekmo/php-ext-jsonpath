#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <php.h>
#include "ext/spl/spl_exceptions.h"
#include "ext/json/php_json.h"
#include "php_jsonpath.h"

zend_class_entry* jsonpath_ce_jsonstore;

static zend_function_entry store_methods[] = {
    PHP_ME(JsonStore, __construct, NULL, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(JsonStore, setData, NULL, ZEND_ACC_PUBLIC)
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

    zend_declare_property_null(jsonpath_ce_jsonstore, DATA_PROPERTY, DATA_LENGTH, ZEND_ACC_PUBLIC TSRMLS_CC);
}

// Updates data attribute with the given data
void updateData(zval* data, zval* store) {
    zval *decoded;
    MAKE_STD_ZVAL(decoded);
    char* jsonstr;
	smart_str buf = {0};

    switch(Z_TYPE_P(data)) {
        case IS_OBJECT:
            php_json_encode(&buf, data, 0 TSRMLS_CC);
            php_json_decode_ex(decoded, buf.c, buf.len, PHP_JSON_OBJECT_AS_ARRAY, DECODE_DEPTH TSRMLS_CC);

            zend_update_property(jsonpath_ce_jsonstore, store, DATA_PROPERTY, DATA_LENGTH, decoded TSRMLS_CC);
            break;
        case IS_STRING:
            jsonstr = Z_STRVAL_P(data);
            php_json_decode_ex(decoded, jsonstr, strlen(jsonstr), PHP_JSON_OBJECT_AS_ARRAY, DECODE_DEPTH TSRMLS_CC);

            zend_update_property(jsonpath_ce_jsonstore, store, DATA_PROPERTY, DATA_LENGTH, decoded TSRMLS_CC);
            break;
        case IS_ARRAY:
            zend_update_property(jsonpath_ce_jsonstore, store, DATA_PROPERTY, DATA_LENGTH, data TSRMLS_CC);
            break;
        default:
            zend_throw_exception(spl_ce_InvalidArgumentException, "Invalid data type in JsonStore. Expected object, array or string", 0 TSRMLS_CC);
    }
}


// ------------------ Class methods
PHP_METHOD(JsonStore, __construct) {
    zval *data;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data) == FAILURE) {
        php_printf("FAIL to get parameters from JsonStore constructor");
        return;
    }

    updateData(data, getThis());
}

PHP_METHOD(JsonStore, setData) {
    zval *data;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &data) == FAILURE) {
        php_printf("FAIL to get parameters from setData()");
        return;
    }

    updateData(data, getThis());
}
