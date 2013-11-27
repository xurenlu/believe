dnl $Id$
dnl config.m4 for extension believe

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(believe, for believe support,
dnl Make sure that the comment is aligned:
dnl [  --with-believe             Include believe support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(believe, whether to enable believe support,
 Make sure that the comment is aligned:
 [  --enable-believe           Enable believe support])

if test "$PHP_BELIEVE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-believe -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/believe.h"  # you most likely want to change this
  dnl if test -r $PHP_BELIEVE/$SEARCH_FOR; then # path given as parameter
  dnl   BELIEVE_DIR=$PHP_BELIEVE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for believe files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       BELIEVE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$BELIEVE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the believe distribution])
  dnl fi

  dnl # --with-believe -> add include path
  dnl PHP_ADD_INCLUDE($BELIEVE_DIR/include)

  dnl # --with-believe -> check for lib and symbol presence
  dnl LIBNAME=believe # you may want to change this
  dnl LIBSYMBOL=believe # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $BELIEVE_DIR/lib, BELIEVE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_BELIEVELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong believe lib version or lib not found])
  dnl ],[
  dnl   -L$BELIEVE_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(BELIEVE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(believe, believe.c, $ext_shared)
fi
