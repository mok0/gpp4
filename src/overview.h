/*
     overview.h: overview of the GGP4 library
     (C) 2003 CCLRC, Martyn Winn, modified by Morten Kjeldgaard 2007, 
     2009.

     This library is free software: you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation, either
     version 3 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with This library.  If not, see
     <http://www.gnu.org/licenses/>.

*/

/** @mainpage The gpp4 library

@section introduction Introduction

This distribution is a special version of the CCP4 library, released under
the Lesser GNU Public License version 2.1.

The goal of this project -- named gpp4 to distinguish it from CCP4 -- is to
provide a drop-in replacement for the CCP4 libraries, that as carefully as
possible will implement the current CCP4 library interface.

The initial motivation to create this public fork the CCP4 library was that
the licensing was changed in version 6.0 to be "non-free". At the time, the
last version of the CCP4 library covered by a free license was version
5.0.2.

There are several third-party applications, such as Phenix and Coot, that
depend on the CCP4 library. However, you could not legally create a derived
work containing both CCP4 6.* licensed code and GPL'd code, and distribute
the resulting program, since the GPL demands that the derived work be
distributed without additional restrictions. The CCP4 6.* license imposed
additional restrictions on redistribution - in particular (but not limited
to) an indemnity clause.

Version 5.0.2 of the CCP4 library was patched by Ralf Grosse-Kunstleve to
address some of the more serious deficiencies of the older libraries and
included with the Phenix distribution.

It is this patched version of the CCP4 library that forms the original
basis for this distribution, which includes a GNU autotools build
environment developed by Paul Emsley and Morten Kjeldgaard.

At this time, the CCP4 has revised its licensing policy, and the CCP4
library is again licensed under the Lesser GNU Public License. However,
there is still a very good reason to maintain and develop ggp4, because the
CCP4 library is tightly integrated with the entire CCP4 distribution, of
currently around 220Mb.

The ggp4 distribution thus serves as a small, standalone version, that can
be included in third party software distributions. It is also available
through the Ubuntu and Fedora software repositories for easy installation.


@section purpose Purpose

The CCP4 software suite is based around a library of routines which cover
common tasks, such as file opening, parsing keyworded input, reading and
writing of standard data formats, applying symmetry operations, etc.
Programs in the suite call these routines which, as well as saving the
programmer some effort, ensure that the varied programs in the suite have a
similar look-and-feel.  <p> Since 2002, there has been a major effort to
re-write much of the CCP4 library into C/C++. The aims are:

<ul>

<li>To implement a better representation of the underlying data model.  For
example, Eugene Krissinel's MMDB library acts on a data structure which
represents the various levels of structure of a protein model.  The new MTZ
library encapsulates the crystal/dataset hierarchy that is increasingly
being used by programs.

<li>To maintain support for existing programs. In particular, the existing
Fortran APIs will be maintained, although they will now often be only
wrappers to functions in the new library. It is hoped that many existing
programs will be migrated to using the new library directly.

<li>To provide support for scripting. It is possible to generate APIs for
Python, Tcl and Perl automatically from the core C code. Thus, much of the
standard CCP4 functionality wil be available to scripts used e.g. in ccp4i
or the molecular graphics project.
</ul>

This incremental approach, maintaining the existing suite while improving
the underlying code, puts constraints on what is possible, but is
considered more appropriate for a collaborative project like CCP4.

@section start This documentation

<p>
This documentation is generated automatically by 
<a href="http://www.doxygen.org/">Doxygen</a> from
comment sections in the code. It is therefore detailed and extensive. 
The library divides roughly into the following sections:
<dl>
<dt>CMTZ library
<dd>See the @ref cmtz_page page for C/C++ programmers, and the
@ref cmtz_f_page page for Fortran programmers.

<dt>CMAP library
<dd>See the @ref cmap_page page for C/C++ programmers, and the
@ref cmap_f_page page for Fortran programmers.

<dt>MMDB library
<dd>See Eugene's <a href="http://www.ebi.ac.uk/pdbe/docs/cldoc/">documentation</a>.

<dt>CSYM library <dd>See the @ref csym_page page for C/C++
programmers, and the @ref csym_f_page page for Fortran programmers.

<dt>CCP4 utility library
<dd>See the @ref utilities_page page for C/C++ programmers.

<dt>CCP4 Parser library
<dd>See the @ref cparser_page page for details on how to use the CCP4 parser routines from C/C++ programs.

<dt>CCP4 resizable arrays
<dd>See the @ref ccp4_array_page page for information on Kevin Cowtan's resizable array implementation.

<dt>Low level disk i/o
<dd>See the @ref diskio_f_page page for Fortran programmers.

</dl>

 */

/*
  Local variables:
  mode: font-lock
  End:
*/
