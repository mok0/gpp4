# -*- mode: sh; mode: font-lock -*-
# AM_PATH_GPP4([ACTION-IF-FOUND [,ACTION-IF-NOT-FOUND]]) 
AC_DEFUN([AM_PATH_GPP4],
[
AC_PROVIDE([AM_PATH_GPP4])

AC_ARG_WITH(gpp4,
  AC_HELP_STRING( [--with-gpp4=PFX], [use gpp4 library (default is NO) and set prefix]),
  [
    test "$withval" = no || with_gpp4=yes 
    test "$withval" = yes || gpp4_prefix="$withval" ],
  [ with_gpp4="$enable_gpp4" ] ) #dnl default is no for now

if test x$with_gpp4 = xyes ; then  

#user override
AS_IF([test "x$CCP4_LIBS" != x && test "x$CCP4_CXXFLAGS" != x ],
[
  have_gpp4=yes
],
[
AC_MSG_CHECKING([for ccp4_errno in gpp4])

saved_LIBS="$LIBS"
saved_CXXFLAGS="$CXXFLAGS"
CCP4_LIBS=""
CCP4_CXXFLAGS=""

if test "x$gpp4_prefix" != x; then
 # ie. gpp4=thing was given (thing is what we're checking for)
 ac_CCP4_CXXFLAGS="-I$gpp4_prefix/include/gpp4"
 ac_CCP4_LDOPTS="-L$gpp4_prefix/lib -lgpp4"
else
 # treat as standard lib/include
 ac_CCP4_CXXFLAGS=""
 ac_CCP4_LDOPTS="-lgpp4"
fi

LIBS="$ac_CCP4_LDOPTS $saved_LIBS"
CXXFLAGS="$ac_CCP4_CXXFLAGS $saved_CXXFLAGS"
#
# AC_TRY_LINK uses the c compiler (set by AC_LANG), so we will
# temporarily reassign $CC to the c++ compiler.
#
AC_LANG_PUSH(C++)
AC_TRY_LINK([#include "ccp4/ccp4_errno.h"],
  [int a = ccp4_errno; CCP4::ccp4_error("conftest"); ], have_gpp4=yes, have_gpp4=no)
AC_LANG_POP(C++)  # the language we have just quit
AC_MSG_RESULT($have_gpp4)

 LIBS="$saved_LIBS"
 CXXFLAGS="$saved_CXXFLAGS"
]) #user override

AS_IF([test x$have_gpp4 = xyes],
  [
    CCP4_CXXFLAGS="$ac_CCP4_CXXFLAGS"
    CCP4_LIBS="$ac_CCP4_LDOPTS"
    ifelse([$1], , :, [$1]) ],
  [
    ifelse([$2], , :, [$2]) ]
)

fi #dnl --with-gpp4

AC_SUBST(CCP4_CXXFLAGS)
AC_SUBST(CCP4_LIBS)
])
