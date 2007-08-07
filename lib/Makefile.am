## -*- mode: Makefile ; mode: font-lock -*-
## This file is to be processed by automake.

lib_LTLIBRARIES = libgpp4.la

library_includedir=$(pkgincludedir)/ccp4

libgpp4_la_SOURCES = ccp4_array.c cmap_data.c cmtzlib.c ccp4_general.c	 \
cmap_header.c csymlib.c ccp4_parser.c cmap_labels.c cvecmat.c		 \
ccp4_program.c cmap_open.c library_err.c ccp4_unitcell.c cmap_skew.c	 \
library_file.c cmap_accessor.c cmap_stats.c library_utils.c cmap_close.c \
cmap_symop.c

# IMPORTANT!
# Read http://sourceware.org/autobook/autobook/autobook_91.html 
# before changing the version-info (read: don't change it)

libgpp4_la_LDFLAGS = -version-info 0:0:0

library_include_HEADERS = ccp4_array.h ccp4_unitcell.h cmap_stats.h	\
ccp4_errno.h ccp4_utils.h cmtzlib.h ccp4_file_err.h ccp4_vars.h		\
csymlib.h ccp4_fortran.h cmap_data.h cvecmat.h ccp4_general.h		\
cmap_errno.h ccp4_parser.h cmap_header.h library_file.h ccp4_program.h	\
cmap_labels.h mtzdata.h ccp4_spg.h cmaplib_f.h overview.h		\
ccp4_sysdep.h cmaplib.h ccp4_types.h cmap_skew.h

####
