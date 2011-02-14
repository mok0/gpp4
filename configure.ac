# -*- mode: Autoconf; mode: font-lock -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(gpp4, 1.3.1, mok@bioxray.dk)
AC_CONFIG_SRCDIR([src/ccp4_vars.h])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AM_INIT_AUTOMAKE

# check base installations
AC_PROG_CC
AC_PROG_CPP
AC_PROG_F77
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AC_F77_LIBRARY_LDFLAGS

# check for libm
AC_CHECK_LIBM
AC_SUBST(LIBM)
AC_CHECK_LIB(m, sin)

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
AC_CHECK_FUNCS([strnlen memmove memset mkdir pow putenv rint setenv sqrt strchr strdup strerror strrchr strstr strlcpy])

# check for mmdb
PKG_CHECK_MODULES(MMDB, mmdb >= 1.19)
AC_SUBST(MMDB_CFLAGS)
AC_SUBST(MMDB_LIBS)

# gpp4 wants to know its prefix
test "x$prefix" = xNONE && prefix=$ac_default_prefix
AC_DEFINE_UNQUOTED([GPP4_PREFIX],["$prefix"],[Base directory of gpp4 installation])
GPP4_PREFIX=$prefix
AC_SUBST(GPP4_PREFIX)

dnl The next section provides logic to allow user to disable the
dnl building of the Fortran API.

AC_ARG_WITH([fortran-api],
          [AS_HELP_STRING([--without-fortran-api],
          [disable building of the Fortran library gpp4f])],
          [],
          [with_fortran_api=yes])

# Define an automake conditional:
AM_CONDITIONAL([WANT_GPP4F],[test "x$with_fortran_api" = "xyes"])

# Define an autoconf substitution:
if test "x$with_fortran_api" = "xyes"; then
  WANT_GPP4F=1
else
  WANT_GPP4F=0
fi
AC_SUBST(WANT_GPP4F)
dnl  end of fortran-api selection

dnl  output the Makefiles
AC_CONFIG_FILES([
		Makefile
		gpp4.pc
		gpp4f.pc
		gpp4.spec
		gpp4.info
		Doxyfile
		src/Makefile
		src_f/Makefile
		data/Makefile
		test/Makefile
		src/ccp4_program.h
		])

AC_OUTPUT

####
