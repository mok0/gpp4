## -*- mode: Makefile ; mode: font-lock -*-
## This file is to be processed by automake.

EXTRA_DIST = unix.m4 dna_header.fh
AM_CFLAGS = -I $(top_srcdir)/src -DGFORTRAN

lib_LTLIBRARIES = libgpp4f.la

libgpp4f_c_files = ccp4_diskio_f.c ccp4_parser_f.c cmaplib_f.c csymlib_f.c \
	ccp4_general_f.c ccp4_unitcell_f.c cmtzlib_f.c library_f.c

libgpp4f_f_files = ccplib.f fftlib.f modlib.f parser.f rwbrook.f libhtml.f \
	keyparse.f unix.f dna_output.f pack_f.f

libgpp4f_la_SOURCES = $(libgpp4f_c_files) $(libgpp4f_f_files)

CLEANFILES = unix.f

libgpp4f_la_LIBADD = $(top_builddir)/src/libgpp4.la @MMDB_LIBS@ $(FLIBS)
libgpp4f_la_CFLAGS = $(AM_CFLAGS) @MMDB_CFLAGS@

# IMPORTANT!
# Read http://sourceware.org/autobook/autobook/autobook_91.html 
# before changing the version-info (read: don't change it)

libgpp4f_la_LDFLAGS = -version-info 0:0:0

unix.f: unix.m4
	m4 < unix.m4 > unix.f

####
