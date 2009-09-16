-*- mode: text -*-

Building gpp4 from the bzr distribution
=======================================

If you are reading this file, it is because you got the gpp4 distribution
by doing:

  bzr branch lp:gpp4

or something similar. Perhaps you downloaded ("branched") someone elses
version and not the official release on Launchpad.


1) create the configure script and Makefile.in's:

  ./bootstrap


2) configure gpp4, for example:

  ./configure --prefix=/usr

  (the default prefix is /usr/local)


3) build and install the library:

  make
  sudo make install


That's all there's to it! Enjoy!


-- 2009-09-16  Morten  Kjeldgaard  <mok@bioxray.dk>

