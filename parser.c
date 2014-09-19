#include <php.h>
#include "ext/standard/php_smart_str.h"
#include "ext/standard/php_string.h"
#include "ext/spl/spl_exceptions.h"
#include "parser.h"

zend_bool in_filter = 0;
zend_bool selection = 0;

zval* parse_jsonpath(char* str, zval* datasource TSRMLS_DC) {
    zval* matched;
    MAKE_STD_ZVAL(matched);

    if (strlen(str) == 0) {
        zend_throw_exception(spl_ce_InvalidArgumentException, "JsonPath query is empty", 0 TSRMLS_CC);
    }

    if (str[0] != '$') {
        zend_throw_exception(spl_ce_InvalidArgumentException, "JsonPath query must start with '$'", 0 TSRMLS_CC);
    }

    zval* exploded, *delimiter, *strzval;
    MAKE_STD_ZVAL(exploded);

    ZVAL_STRING(delimiter, ".", 1);
    ZVAL_STRING(strzval, str, 1);

    //php_explode(delimiter, strzval, exploded, 100);
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
