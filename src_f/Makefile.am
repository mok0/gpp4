## -*- mode: Makefile ; mode: font-lock -*-
## This file is to be processed by automake.

EXTRA_DIST = ccplib.f fftlib.f modlib.f parser.f rwbrook.f unix.m4

fsplit = ../util/fsplit

lib_LIBRARIES = libgpp4f.a

libgpp4f_c_files = ccp4_diskio_f.c ccp4_parser_f.c cmaplib_f.c		\
	csymlib_f.c ccp4_general_f.c ccp4_unitcell_f.c cmtzlib_f.c	\
	library_f.c

ccplib_f_files = ccfill.f ccpbyt.f ccpiby.f ccppag.f ccpzi.f litend.f	\
sts3r4.f ccp4_hash_lookup.f ccpcpi.f ccpii2.f ccppsf.f ccpzr.f		\
lstlsq.f ccp4_hash_setup.f ccpdex.f ccpmde.f ccpsi2.f csetnv.f		\
lunsti.f ccp4_hash_zeroit.f ccpdpn.f ccpmvb.f ccpstb.f fdir.f lunsto.f	\
ccp4_patch_level.f ccpe2i.f ccpmvi.f ccpsum.f fextn.f nbitst.f		\
ccpalc.f ccpgi2.f ccpmvr.f ccptoi.f froot.f nocrlf.f ccpale.f ccpgtb.f	\
ccpnun.f ccpufl.f hkleq.f stbits.f ccpbyi.f ccpi2i.f ccponl.f ccpzbi.f	\
lenstr.f sthlsq.f

fftlib_f_files = cmplft.f inv21.f prmvcr.f r4cftk.f realft.f sdiad.f	\
diprp.f mdftkd.f r2cftk.f r5cftk.f rpcftk.f srfp.f hermft.f prmvci.f	\
r3cftk.f r8cftk.f rsymft.f

modlib_f_files = cross.f fa01bs.f imatvec.f matmul4.f minvn.f unit.f	\
detmat.f fa01cs.f iminv3.f matmulgen.f ml3mat.f vdif.f dot.f fa01ds.f	\
inv44.f matmulnm.f msta1.f vset.f ea06c.f fm02ad.f jdvx.f		\
matmultrans.f msta2.f vsum.f ea08c.f gamma.f jvx.f matvc4.f ranmar.f	\
zipin.f ea09c.f gmprd.f matmli.f matvec.f scalev.f zipout.f		\
eigen_rs_asc.f icross.f matmln.f mc04b.f transfrm.f zjvx.f fa01as.f	\
idot.f matmul.f minv3.f transp.f

parser_f_files = blank.f gtnint.f gtprea.f keyerr.f putlin.f rdhead.f	\
rdscal.f chkkey.f gtnrea.f gttint.f keynum.f rdatomselect.f rdresl.f	\
rdsymm.f cmatch.f gtpint.f gttrea.f lerror.f rdcell.f rdreso.f		\
sblank.f

rwbrook_f_files = cvanisob.f rbfro1.f rbrorf2.f wbcells.f xyzcoord.f	\
cvanisou.f rbfror.f rbspgrp.f wbrook.f xyzinit.f cvfrac.f rbinit.f	\
res3to1.f wbspgrp.f xyzopen.f cvfrac2.f rbrcel.f rwbfin.f wremark.f	\
xyzopen2.f num_expected_waters.f rbrecip.f rwnohead.f xyzadvance.f	\
xyzrewd.f rbcell.f rbrinv.f sfread.f xyzatom.f rbfrac.f rbrook.f	\
sfread2.f xyzbksp.f rbfrac2.f rbrorf.f wbcell.f xyzclose.f

unix_f_files = ccpopn.f cexit.f rtnbks.f ubytes.f ugtarg.f ugtuid.f	\
vaxvms.f ccpspw.f hciftime.f ttsend.f ugerr.f ugtenv.f uisatt.f		\
winmvs.f

libgpp4f_f_files = $(fftlib_f_files)  $(modlib_f_files) \
  $(parser_f_files)  $(rwbrook_f_files) $(unix_f_files)

libgpp4f_a_SOURCES = $(libgpp4f_c_files) $(libgpp4f_f_files)
libgpp4f_a_CFLAGS = -I $(top_srcdir)/src

CLEANFILES = $(ccplib_f_files) $(fftlib_f_files)  $(modlib_f_files) \
  $(parser_f_files)  $(rwbrook_f_files) $(unix_f_files) unix.f

# IMPORTANT!
# Read http://sourceware.org/autobook/autobook/autobook_91.html 
# before changing the version-info (read: don't change it)

#libgpp4f_a_LDFLAGS = -version-info 0:0:0

$(ccplib_f_files): ccplib.f
	$(fsplit) ccplib.f

$(fftlib_f_files): fftlib.f
	$(fsplit) fftlib.f

$(modlib_f_files): modlib.f
	$(fsplit) modlib.f

$(parser_f_files): parser.f
	$(fsplit) parser.f

$(rwbrook_f_files): rwbrook.f
	$(fsplit) rwbrook.f

$(unix_f_files): unix.m4
	m4 < unix.m4 > unix.f
	$(fsplit) unix.f

####
