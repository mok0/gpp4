## -*- mode: Makefile ; mode: font-lock -*- 
## This file is to be processed by automake.

ACLOCAL_AMFLAGS = -I config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gpp4.pc

# Also distribute these files:
EXTRA_DIST = bootstrap README gpp4.pc.in gpp4f.pc.in gpp4.spec.in	\
  gpp4.info.in COPYRIGHT Doxyfile.in gpp4.m4

# Build in these directories
SUBDIRS = src test data

if WANT_GPP4F
  SUBDIRS += src_f
  pkgconfig_DATA += gpp4f.pc
endif

DISTCLEANFILES = gpp4.info gpp4.spec gpp4.pc gpp4f.pc Doxyfile

####
