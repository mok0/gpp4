## -*- mode: Makefile ; mode: font-lock -*- 
## This file is to be processed by automake.

ACLOCAL_AMFLAGS = -I config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gpp4.pc gpp4f.pc

# Also distribute these files:
EXTRA_DIST = bootstrap README gpp4.pc.in gpp4f.pc.in gpp4.spec.in	\
gpp4.info.in COPYRIGHT

# Build in these directories
SUBDIRS = src src_f test data

DISTCLEANFILES = gpp4.info gpp4.spec gpp4.pc gpp4f.pc

####
