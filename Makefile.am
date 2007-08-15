## -*- mode: Makefile ; mode: font-lock -*- 
## This file is to be processed by automake.

# Build in these directories
SUBDIRS = lib test

ACLOCAL_AMFLAGS = -I config

#Distribute these directories:
DIST_SUBDIRS = $(SUBDIRS) data

EXTRA_DIST = bootstrap README gpp4.pc

install-data-hook:
	mkdir -p $(DESTDIR)/$(libdir)/pkgconfig
	$(INSTALL) -m644 gpp4.pc $(DESTDIR)/$(libdir)/pkgconfig

uninstall-hook:
	rm -f $(DESTDIR)/$(libdir)/pkgconfig/gpp4.pc

####
