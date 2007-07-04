# -*- mode: Autoconf; mode: font-lock -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gpp4, 1.0, mok@bioxray.dk)
AC_CONFIG_SRCDIR([lib/ccp4_vars.h])
AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# check for libm
AC_CHECK_LIBM
AC_SUBST(LIBM)


AC_HEADER_STDC([])

AC_CONFIG_FILES([
		Makefile
		lib/Makefile
		])

AC_OUTPUT

####
