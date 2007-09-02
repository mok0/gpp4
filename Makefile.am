## -*- mode: Makefile ; mode: font-lock -*- 
## This file is to be processed by automake.

ACLOCAL_AMFLAGS = -I config

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gpp4.pc

#Distribute these directories:
DIST_SUBDIRS = $(SUBDIRS) 

# Also distribute these files:
EXTRA_DIST = bootstrap README gpp4.pc.in gpp4.spec.in gpp4.info.in

# Build in these directories
SUBDIRS = lib test data

####
