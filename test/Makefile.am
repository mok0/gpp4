## -*- mode: Makefile ; mode: font-lock -*- 
## Copyright 2007 Morten Kjeldgaard
## This code is distributed under the GPL license.

AM_CPPFLAGS = -I$(top_srcdir)/src
AM_LDFLAGS = $(top_builddir)/src/libgpp4.la @LIBM@

noinst_PROGRAMS = load_syminfo mtzhdr checkarch maphdr mtzcols mtz2csv

load_syminfo_SOURCES = load_syminfo.c
mtzhdr_SOURCES = mtzhdr.c
mtzcols_SOURCES = mtzcols.c
checkarch_SOURCES = checkarch.c
maphdr_SOURCES = maphdr.c
mtz2csv_SOURCES = mtz2csv.c

####
