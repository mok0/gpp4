## -*- mode: Makefile ; mode: font-lock -*- 
## This file is to be processed by automake.

ACLOCAL_AMFLAGS = -I config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gpp4.pc

# Also distribute these files:
EXTRA_DIST = bootstrap README gpp4.pc.in gpp4.spec.in gpp4.info.in
DISTCLEANFILES = gpp4.pc gpp4.spec gpp4.info

# Build in these directories
SUBDIRS = src test data

####
