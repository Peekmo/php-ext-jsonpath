#ifndef PHP_JSONPATH_H
#define PHP_JSONPATH_H 1
#define PHP_JSONPATH_VERSION "1.0"
#define PHP_JSONPATH_EXTNAME "jsonpath"

#define DATA_PROPERTY "data"
#define DATA_LENGTH strlen("data")
#define DECODE_DEPTH 512

void jsonpath_init_jsonstore(TSRMLS_D);

PHP_METHOD(JsonStore, __construct);
PHP_METHOD(JsonStore, setData);

PHP_MINIT_FUNCTION(jsonpath);

extern zend_module_entry jsonpath_module_entry;
#define phpext_jsonpath_ptr &jsonpath_module_entry

#endif
