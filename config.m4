PHP_ARG_ENABLE(jsonpath, whether to enable JsonPath support, [ --enable-jsonpath   Enable JsonPath support])
if test "$PHP_JSONPATH" = "yes"; then
  AC_DEFINE(HAVE_JSONPATH, 1, [Whether you have JsonPath])
  PHP_NEW_EXTENSION(jsonpath, jsonpath.c, $ext_shared)
fi
