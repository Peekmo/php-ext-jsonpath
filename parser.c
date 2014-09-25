#include <php.h>
#include "ext/standard/php_smart_str.h"
#include "ext/standard/php_string.h"
#include "ext/standard/php_var.h"
#include "ext/spl/spl_exceptions.h"
#include "parser.h"

zend_bool in_filter = 0;
zend_bool selection = 0;

// Debug func
void debug(zval* data) {
    zval *function_name, *return_value;
    MAKE_STD_ZVAL(function_name);
    MAKE_STD_ZVAL(return_value);

    ZVAL_STRING(function_name, "var_dump", 1);

    zval* params = {data};

    call_user_function(CG(function_table), NULL, function_name, return_value, 1, &params TSRMLS_CC);
}

zval* parse_jsonpath(char* str, zval* datasource TSRMLS_DC) {
    zval* matched;
    MAKE_STD_ZVAL(matched);

    if (strlen(str) == 0) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "JsonPath query is empty", 0 TSRMLS_CC);
    }

    if (str[0] != '$') {
        zend_throw_exception(spl_ce_InvalidArgumentException, "JsonPath query must start with '$'", 0 TSRMLS_CC);
    }

    zval* exploded, *delimiter, *strzval, *function_name;
    MAKE_STD_ZVAL(exploded);
    MAKE_STD_ZVAL(delimiter);
    MAKE_STD_ZVAL(strzval);
    MAKE_STD_ZVAL(function_name);

    ZVAL_STRING(delimiter, ".", 0);
    ZVAL_STRING(strzval, str, 0);
    ZVAL_STRING(function_name, "explode", 1);

    zval* params;
    MAKE_STD_ZVAL(params);
    array_init(params);
    add_next_index_zval(params, delimiter);
    add_next_index_zval(params, strzval);

    debug(params);
    call_user_function(CG(function_table), NULL, function_name, exploded, 2, &params TSRMLS_CC);
    //php_explode(delimiter, strzval, exploded, 2);
    return exploded;
    /**for (int i=1; i<strlen(str); i++) {
        switch (str[i]) {
            case '.':
                break;
            case '[':
                break;
            case ']':
                break;
            case '*':
                break;
        }
    }**/
}
