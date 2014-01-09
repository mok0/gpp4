BUILT_SOURCES = $(srcdir)/gpp4_wrap.c
SWIG_SOURCES = gpp4.i

pkgpython_PYTHON = gpp4.py
pkgpyexec_LTLIBRARIES = _gpp4.la
_gpp4_la_SOURCES = $(srcdir)/gpp4_wrap.c $(SWIG_SOURCES)
_gpp4_la_CPPFLAGS = $(AX_SWIG_PYTHON_CPPFLAGS) -I$(top_srcdir)/src
_gpp4_la_LDFLAGS = -module
_gpp4_la_LIBADD = ../src/libgpp4.la

$(srcdir)/gpp4_wrap.c: $(SWIG_SOURCES)
	$(SWIG) $(AX_SWIG_PYTHON_OPT) -I$(top_srcdir)/src -o $@ $<
###
