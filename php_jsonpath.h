#ifndef PHP_JSONPATH_H
#define PHP_JSONPATH_H 1
#define PHP_JSONPATH_VERSION "1.0"
#define PHP_JSONPATH_EXTNAME "jsonpath"

PHP_MINIT_FUNCTION(jsonpath);

extern zend_module_entry jsonpath_module_entry;
#define phpext_jsonpath_ptr &jsonpath_module_entry

#endif
