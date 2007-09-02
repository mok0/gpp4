# -*- mode: Autoconf; mode: font-lock -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gpp4, 1.0.3, mok@bioxray.dk)
AC_CONFIG_SRCDIR([lib/ccp4_vars.h])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE

# check base installations
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# check for libm
AC_CHECK_LIBM
AC_SUBST(LIBM)

# check for std c headers
AC_HEADER_STDC([])

# check for various headers
AC_CHECK_HEADERS([fcntl.h float.h limits.h stddef.h stdlib.h stdint.h string.h sys/file.h sys/stat.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_SETVBUF_REVERSED
AC_FUNC_STRTOD
AC_FUNC_VPRINTF

# check for various c library functions
AC_CHECK_FUNCS([memmove memset mkdir pow putenv rint setenv sqrt strchr strdup strerror strrchr strstr])

# gpp4 wants to know it's prefix
test "x$prefix" = xNONE && prefix=$ac_default_prefix
AC_DEFINE_UNQUOTED([GPP4_PREFIX],["$prefix"],[Base directory of gpp4 installation])
GPP4_PREFIX=$prefix
AC_SUBST(GPP4_PREFIX)

# output the Makefiles
AC_CONFIG_FILES([
		Makefile
		gpp4.pc
		gpp4.spec
		gpp4.info
		lib/Makefile
		lib/Doxyfile
		data/Makefile
		test/Makefile
		])

AC_OUTPUT

####
