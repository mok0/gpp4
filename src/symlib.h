/*
     symlib.h: overview of syminfo library
     Copyright (C) 2003  CCLRC, Martyn Winn
     Modified by Morten Kjeldgaard 2007.

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later
     version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free
     Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
     Boston, MA 02110-1301 USA
*/

/*! 
@page csym_f_page Software Library for handling symmetry operations

@section DESCRIPTION

From CCP4 5.0, the core handling of symmetry information is done by a
set of C functions. Separate @ref csym_page documentation describes
the structures and functions used, and the API for C/C++ programs.

For Fortran programs, the original set of subroutines (held in @c
symlib.f) has been replaced by an @ref csym_page interface to the C
library. From the point of view of an application programmer, this
interface should be identical to the original set of subroutines. This
document originates from the original Fortran library, but should be
applicable to the new library.

The available Fortran calls have been arranged as much as possible
into groups by function. There are often several versions of calls
apparently performing the same or very similar tasks, reflecting the
policy of never removing existing functionality in order to maintain
compatibility with programs written using older versions of the
library.

@section CONTENTS

- @ref symmetry_library DESCRIPTION OF THE SYMMETRY LIBRARY
- @ref symmetry_store HOW SYMMETRY OPERATIONS ARE STORED AND APPLIED
- @ref describe_group DESCRIPTION OF THE GROUPS OF ROUTINES
  -# @ref group_1 Deriving and manipulating symmetry operations
      - @ref group_1_a 1.a. Deriving symmetry operator matrices
      - @ref group_1_b 1.b. Deriving information from symmetry operators
      .
      
  -# @ref group_2 Testing reflection data
      - @ref group_2_a 2.a. Centric reflections
      - @ref group_2_b 2.b. Epsilon zones
      .
    
  -# @ref group_3 Choosing asymmetric units
      - @ref group_3_a 3.a. Choosing asymmetric units for reflection data
      - @ref group_3_b 3.b. Choosing asymmetric units in real space consistent
        with FFT expectations
      .
    
  -# @ref group_4 Testing coordinate data
  -# @ref group_5 Permuting symmetry operators
  -# @ref group_6 Generating and accessing a hash table
  -# @ref group_7 Miscellaneous routines
  .
- @ref list_of_routines FORTRAN API (arranged alphabetically)
- @ref asymmetric_unit DEFINITION OF THE CCP4 ASYMMETRIC UNIT
  - @ref recip_asym_unit a. Reciprocal space
  - @ref real_asym_unit b. Real space
  .

@section symmetry_library DESCRIPTION OF THE SYMMETRY LIBRARY

In CCP4, the primary symmetry information is held in a library data
file defined by the logical name SYMINFO. In the standard
configuration of CCP4 this is the file syminfo.lib which normally
resides in $CLIBD. This file replaces the previous data file SYMOP
(i.e. $CLIBD/symop.lib).

@c syminfo.lib holds information for all the standard spacegroups in
the International Tables. For each spacegroup, several alternative
settings are included (e.g. "P񁦤�1", "P񁦣�2" (a.k.a. 1003) and
"P񁺏�1" for spacegroup 3).

@subsection format Format of the symmetry library file

Each setting of a spacegroup is delimited by begin_spacegroup /
end_spacegroup records, and contains the following items:

@verbatim
  number = standard spacegroup number 
  basisop = change of basis operator 
  symbol ccp4 = CCP4 spacegroup number e.g. 1003 
                (0 if not a CCP4 group) 
  symbol Hall = Hall symbol 
  symbol xHM =  extended Hermann Mauguin symbol 
  symbol old =  CCP4 spacegroup name 
                (blank if not a CCP4 group) 
  symbol laue = Laue group symbol 
  symbol patt = Patterson group symbol 
  symbol pgrp = Point group symbol 
  hklasu ccp4 = reciprocal space asymmetric unit 
                (with respect to standard setting) 
  mapasu ccp4 = CCP4 real space asymmetric unit 
                (with respect to standard setting) 
                (negative ranges if not a CCP4 group) 
  mapasu zero = origin based real space asymmetric unit 
                (with respect to current setting) 
  mapasu nonz = non-origin based real space asymmetric unit 
                (with respect to current setting) 
  cheshire = Cheshire cell 
                (with respect to standard setting) 
  symop = list of primitive symmetry operators 
  cenop = list of centering operators 
   
@endverbatim

For example:

@verbatim
begin_spacegroup
number  3
basisop z,x,y
symbol ccp4 1003
symbol Hall ' P 2y (z,x,y)'
symbol xHM  'P 1 1 2'
symbol old  'P 1 1 2'
symbol laue '-P 2' '2/m'
symbol patt '-P 2' '2/m'
symbol pgrp ' P 2' '2'
hklasu ccp4 'k>=0 and (l>0 or (l=0 and h>=0))'
mapasu ccp4 0\<=x\<=1/2; 0\<=y\<1; 0\<=z\<1
mapasu zero 0\<=x\<1; 0\<=y\<=1/2; 0\<=z\<1
mapasu nonz 0\<=x\<1; 0\<=y\<=1/2; 0\<=z\<1
cheshire 0\<=x\<=1/2; 0\<=y\<=0; 0\<=z\<=1/2
symop x,y,z
symop -x,-y,z
cenop x,y,z
end_spacegroup
@endverbatim

A call to @ref msymlb3 MSYMLB3 should be used to retrieve information 
from the symmetry library. Note that not all the data items are compulsory 
for MSYMLB3, although older versions of the routine (MSYMLB2, MSYMLB,
MSYGET) still need them.


@section symmetry_store HOW SYMMETRY OPERATIONS ARE STORED AND APPLIED

@subsection storage Storage of symmetry operations

In syminfo.lib the symmetry operations in each spacegroup are listed as
strings, for example X,Y,Z or -Y,X-Y,Z+1/3 etc. To be useful within a
program these string representations have to be converted to some
mathematical representation.

Typically a symmetry operation RSym will consist of a rotation
operation R and a translation operation T (basically a vector). These
are applied to a vector x to obtain x':

<center>
x' = Rx + T
</center>

It is convenient to represent the rotation by a 3*3 matrix:

@verbatim
            ( R11  R12  R13 )
      [R] = ( R21  R22  R23 )
            ( R31  R32  R33 )
@endverbatim               

and the translation by a column vector with 3 elements:

@verbatim
            ( T1 )
      [T] = ( T2 )
            ( T3 ).
@endverbatim

CCP4 uses 4x4 arrays to store these symmetry operations as follows:

@verbatim
      RSym = ( R11  R12  R13  T1 )
             ( R21  R22  R23  T2 )
             ( R31  R32  R33  T3 )
             (  0    0    0   1  )
@endverbatim

or

@verbatim
      RSym = (    [R]    | [T] ) 
             (  0  0  0  |  1  )
@endverbatim

Essentially this is a 4x4 matrix holding 3x3 transformation matrix in
the "top-left-hand corner", the 3-element column (translation) vector
in the "top-right-hand corner", and then (0 0 0 1) in the bottom row.

The subroutine @ref msymlb3 MSYMLB3 will obtain the set of symmetry
matrices in this representation for a given spacegroup, whilst
@ref symfr2 SYMFR2 or @ref symfr3 SYMFR3 will obtain
individual matrices from the string representation mentioned above.
(@ref symtr4 SYMTR4 will perform the inverse operation, converting
matrices to string representation.)

@subsection application Application of symmetry operations

@subsubsection real_space_coordinates 1. Real Space Coordinates

Using the convention outlined above, post-multiplying the 4x4 matrix by a column
vector as follows:

@verbatim
     RSym . [xf]
            [yf]
            [zf]
            [1 ]
@endverbatim

will apply both the symmetry and the translation operations to real space
coordinates with a single matrix multiplication. The CCP4
@ref modlib MODLIB library provides
@ref matrix_vector_ops matrix-vector routines MATVEC4 and
TRANSFRM which can be used to perform this operation.

@subsubsection reciprocal_space 2. Reciprocal Space

The inverse of real-space symmetry matrices are applied to reflection
indices by pre-multiplying them by a row vector representing hkl,

<center>
ie. h' = h R<sup>-1</sup>
</center>
or,
<center>
(h' k' l') = (h k l) R<sup>-1</sup>
</center>

Note that only the operations in the appropriate Laue group are
applied to reflection indices, so there are no translational
components (i.e. the vector part of the operation, [T], is zero).  The
subroutine @ref invsym INVSYM will invert a 4x4 matrix stored in this
representation, for the purpose of applying symmetry operations to
reflection indices.

@subsubsection  axis_vectors 3. Axis Vectors

Real space axis vectors are transformed like reciprocal space
vectors, i.e.

<center>
(a' b' c') = (a b c) R<sup>-1</sup>
</center>

while reciprocal space axis vectors are transformed like real space
coordinates, i.e.

<center>
(a*' b*' c*') = R (a* b* c*)
</center>

(See also the REINDEX documentation.)


@section describe_group DESCRIPTION OF THE GROUPS OF ROUTINES

The routines have been broken down into groups according to function.

@subsection group_1 Subroutines for deriving and manipulating symmetry operations

This group contains routines for obtaining the lists of symmetry
operators from the library, and converting between the string (eg Y,X,-Z
etc) and matrix representations of symmetry operators. 

@subsection group_1_a Group 1a: Deriving symmetry operator matrices

<dl>
<dt> @ref msymlb3 MSYMLB3
   </dt><dd> Gets the symmetry
operators in matrix representation for a specified spacegroup from the
symmetry library. Will match to any valid s/g name but always returns
the longest name, and will match to the spacegroup number if no name
matches. Always uses the s/r PGDEFN to guess the point group and the
number of primitive symmetry operations (so that any listed in the
library are automatically ignored). Checks that the symmetry operations
form a closed set. <br> Replaces: @ref msymlb2 MSYMLB2,
                  @ref msymlb MSYMLB,
                  @ref msyget MSYGET
</dd><dt> @ref symfr2 SYMFR2, @ref symfr3 SYMFR3
   </dt><dd> Translates a character string containing symmetry operator(s) into matrix represenation, stored in a 4*4 matrix/array.
   <br> NB: SYMFR2 will translate real space coordinate operations (e.g.
<tt>x+z,z,-y</tt>), reciprocal space operations (e.g. <tt>h,l-h,-k</tt>) and
reciprocal- and real-space axis vector operations (e.g. <tt>a*+c*,c*,-b*</tt> and
<tt>a,c-a,-b</tt> respectively). SYMFR3 only translates real space coordinate
operations.
</dd><dt> @ref symtr4 SYMTR4
   </dt><dd> Translates symmetry matrices into character strings with the equivalent symmetry operations.
   <br> Replaces: @ref symtrn SYMTRN, @ref symtr3 SYMTR3
</dd><dt> @ref invsym INVSYM
   </dt><dd> Invert the 4*4 array holding the symmetry matrices, to get the inverse symmetry operation.
</dd></dl>

Use MSYMLB3 to obtain the set of symmetry operator matrices given the spacegroup name
or number. SYMFR2/3 will generate individual symmetry operator matrices from their string
representation (useful if the operators are a subset of a spacegroup). SYMTR4
performs the opposite action, and generates string representations of individual
symmetry operations from the matrices.

INVSYM will generate the inverse matrix of a real space symmetry operation, to be
applied to reflection indices as described in @ref symmetry_store section 2.

@subsubsection internal_routines Internal routines:

<dl>
<dt> @ref determ DETERM  </dt><dd> Calculate the determinant of 4*4 matrix.
</dd></dl>


@subsection group_1_b Group 1b: Deriving information from symmetry operators

<dl>
<dt> @ref pgdefn PGDEFN
   </dt><dd> Obtain/guess pointgroup and primitive set of symmetry operators from analysis of all symmetry operators.
</dd><dt> @ref pgmdf PGMDF
   </dt><dd> Gronigen subroutine: determine the nature of the rotation and screw axes from the symmetry matrices.
</dd><dt> @ref pgnlau PGNLAU
   </dt><dd> Determine the Laue group from pointgroup name.
</dd><dt> @ref patsgp PATSGP
   </dt><dd>Determine the Patterson spacegroup from true spacegroup.
</dd><dt> @ref hklrange HKLRANGE
   </dt><dd> Return HKL ranges chosen in PGNLAU
</dd></dl>

These routines all derive additional information from the symmetry operators or
the spacegroup name. The subroutine HKLRANGE returns the information stored in
the common block which it shares with PGNLAU



@subsection group_2 Group 2: Subroutines for testing reflection data



@subsection group_2_a a) Centric reflections

<dl>
<dt> @ref centric CENTRIC
    </dt><dd>Sets up symmetry elements; must be called first.
</dd><dt> @ref centr CENTR
    </dt><dd>Tests if a reflection is centric
</dd></dl>

Nb: routines @ref centrc CENTRC and CENPHS both appear to be unused.

Call CENTRIC once to set up the symmetry elements in common blocks shared with CENTR.
This defines the set of centric reflections. Then for each reflection, a call to
CENTR will return whether it is centric.

@subsection group_2_b b) Epsilon zones

<dl>
<dt> @ref epsln EPSLN
    </dt><dd> Sets up tables of epsilon zones; must be called first.
</dd><dt> @ref epslon EPSLON
    </dt><dd> Returns the
epsilon zone of a given reflection, as well as whether the reflection
is systematically absent (using a call to SYSAB).
</dd><dt> @ref sysab SYSAB
    </dt><dd> Function: determines if a reflection is systematically absent.
</dd></dl>Call EPSLN once to generate the epsilon zones (general sets
of reflections eg 00l or 0k0) and determine the multiplicity/fold. For
each reflection a call to EPSLON returns the zone and if the reflection
is systematically absent. SYSAB is not called directly.

@ref hkleq HKLEQ - used in SCALA to test if two reflections have equal indices.


@subsection group_3 Group 3: Subroutines for choosing asymmetric units

Remember that the choice of asymmetric unit is NOT UNIQUE. These routines define the
set of CCP4 asymmetric units. The limits for these definitions are given in 
@ref asymmetric_unit section 3.

@subsubsection group_3_a  a) Subroutines for choosing asymmetric units for reflection data

<dl>
<dt>  @ref asuset ASUSET
   </dt><dd> Set up symmetry for ASUPUT and ASUGET; must be called first. Calls PRTRSM.
</dd><dt>  @ref asuput ASUPUT
   </dt><dd> Put reflection into asymmetric unit defined in ASUSET (reverse operation of ASUGET). Calls INASU.
</dd><dt>  @ref asuget ASUGET
   </dt><dd> Recover original indices of a reflection in the asymmetric unit defined in ASUSET (reverse opertaion of ASUPUT).
</dd><dt>  @ref asuphp ASUPHP
   </dt><dd> Change phase for symmetry related reflection.
</dd></dl>Call ASUSET first to set up symmetry operations in common
blocks shared with the other
routines. For each reflection calls can then be made to ASUPUT (return
the unique hkl
indices in the asymmetric unit and symmetry number) or ASUGET (obtain
real space indices
given unique hkl's and symmetry number). INASU will determine whether a
given reflection lies in the asymmetric unit and ASUPHP will convert
the phase.
<h4>Internal routines:</h4>

<dl>
<dt> @ref inasu INASU
   </dt><dd> Funtion: test if reflection is in the asymmetric unit defined by ASUSET.
</dd><dt> @ref prtrsm PRTRSM
   </dt><dd> Print reciprocal space symmetry operations.
</dd></dl>

Both these routines are called from within other routines, although they can also be
called independently. ASUSET must be called before INASU can be used.

@subsubsection group_3_b b) Subroutines for choosing asymmetric units in real space consistent with FFT expectations; FFT grids etc.

<dl>
<dt> @ref setlim SETLIM
   </dt><dd> Set the appropriate box
(=asymmetric unit) for the true spacegroup (ie not the FFT spacegroup).
For cubic symmetry spacegroups, this will be more than one asymmetric
unit.
</dd><dt> @ref setlim_zero SETLIM_ZERO
   </dt><dd> Set the
appropriate box (=asymmetric unit) for the true spacegroup (ie not the
FFT spacegroup). For cubic symmetry spacegroups, this will be more than
one asymmetric unit.<br><i>NB: This s/r differs from SETLIM in using asu limits derived from cctbx.</i>
</dd><dt> @ref setgrd SETGRD
   </dt><dd> Set up a suitable sampling grid for FFT. Calls FNSMP.
</dd></dl>

@subsubsection internal_routines_2 Internal routines:

<dl>
<dt>@ref factrz FACTRZ
   </dt><dd> Function: returns TRUE if N has all prime factors \< 19.
</dd><dt>@ref fndsmp FNDSMP
   </dt><dd> Find suitable grid sample.
</dd></dl>

@subsection group_4 Group 4: Subroutines for testing coordinate data

<dl>
<dt> @ref calc_orig_ps CALC_ORIG_PS
   </dt><dd> Creates a list of equivalent origins for a given spacegroup
</dd><dt> @ref xspecials XSPECIALS
   </dt><dd> Finds which
coordinates occupy special positions (i.e. have occupancies less than
1.0) from consideration of the symmetry operations.
</dd><dt> @ref krot KROT
   </dt><dd> Function: apply symmetry operation to coordinate triplet and check if the result lies in the asymmetric unit.
</dd></dl>

<p>Neither of the routines XSPECIALS or KROT appear to be used in supported CCP4
programs.

@subsection group_5 Group 5: Subroutines for permuting symmetry operators

Three subroutines for permuting symmetry operations. They do not really
belong here in symlib, but are widely used invisibly in FFT routines using symmetry
operations to permute axes for easier fast fourier calculations.

<dl>
<dt> @ref prmvci PRMVCI
  </dt><dd> Permutes specified column of an integer input matrix using another matrix.
</dd><dt> @ref prmvcr PRMVCR
  </dt><dd> Equivalent to PRMVCI but operates on a real input matrix.
</dd><dt> @ref rotfix ROTFIX
  </dt><dd> Permutes inverse symmetry operations.
</dd></dl>

@subsection group_6  Group 6: Subroutines for generating and accessing a hash table

A set of routines used in SCALA, POSTREF and REBATCH.

<dl>
<dt>@ref ccp4_hash_setup CCP4_HASH_SETUP</dt><dd>
Places a value in the internal look-up table.
</dd><dt>@ref ccp4_hash_lookup CCP4_HASH_LOOKUP</dt><dd>
Access a value stored in the table.
</dd><dt>@ref ccp4_hash_zeroit CCP4_HASH_ZEROIT</dt><dd>
Initialise contents of the table to zero.
</dd></dl>

These routines are not directly related to symmetry operations. Hashing
is a method of storing data value pairs in such a way that they can be
be efficiently retreived later on; the hash table is the resulting data
structure.
<p>

@subsection group_7 Group 7: Miscellaneous subroutines

<dl>
<dt>@ref setrsl SETRSL</dt><dd>
Routine to calculate set coefficients for calculation of (sin(theta)/lambda)**2,
from cell dimensions and angles.
</dd><dt>@ref sthlsq STHLSQ</dt><dd>
Calculate (sin(theta)/lambda)**2 from h,k,l, using coefficients set by a
call to SETRSL.
</dd><dt>@ref sts3r4 STS3R4</dt><dd>
Calculate (sin(theta)/lambda)**2 from h,k,l, using coefficients set by a
call to SETRSL. Duplicates STHLSQ exactly.
</dd></dl>

These three routines share the common block RECPLT. SETRSL and STHLSQ are used only
in CAD, whilst STS3R4 does not appear in any supported program.

This is how the routines are used in CAD. A call to SETRSL with the cell dimensions
and angles sets up coefficients in RECPLT, which are then used by the function STHLSQ
to calculate the quantity "(sin(theta)/lamba)**2" for any given set of
h, k, l indices. From Bragg's Law, this quantity is equal to 1/(4*d**2), that is,
one-quarter of the resolution. Within CAD, multiplication by 4 yields the resolution
1/d**2.

<dl>
<dt>@ref pstoph PSTOPH</dt><dd>
Phase angle conversion routine.
</dd></dl>

The exact function of this routine is unclear and it does not appear
in any supported program.

@section list_of_routines FORTRAN API

The following calls are available to Fortran programs. They are arranged alphabetically.

@subsection asuget Subroutine ASUGET(IHKL,JHKL,ISYM)
Get original indices of reflection from  asymmetric unit,
i.e. reverse operation of ASUPUT. Symmetry defined by call to ASUSET.

On input:

<dl>
<dt>IHKL(3)</dt><dd>input unique indices hkl</dd>
<dt>ISYM</dt><dd>symmetry number for output @n
                 odd  numbers are for I+ @n
                 even numbers are for I- @n
               real-space symmetry operation number L = (ISYM-1)/2 + 1
</dd></dl>
On output:
<dl>
<dt>JHKL(3)</dt><dd>
    output original indices hkl
</dd></dl>
The real-space symmetry matrices are applied in ASUPUT by
premultiplying them by a row vector hkl,  ie  (h'k'l') = (hkl)R.
So here we calculate (hkl) = (h'k'l') R**-1

@subsection asuphp Subroutine ASUPHP(JHKL,LSYM,ISIGN,PHASIN,PHSOUT)
Generate phase of symmetry equivalent JHKL from that of IHKL.
<p>
On input:
<dl>
<dt>JHKL(3)</dt><dd>
    indices hkl generated in ASUPUT
</dd><dt>LSYM</dt><dd>
       symmetry number for generating JHKL ( found by ASUPUT)
</dd><dt>ISIGN</dt><dd>
         =  1   for I+<br>
         = -1   for I-
</dd><dt>PHASIN</dt><dd>
     phase for reflection IHKL(3)
</dd></dl>
On output:
<dl>
<dt>PHSOUT</dt><dd>
     phase for reflection JHKL(3)
</dd></dl>

@subsection asuput Subroutine ASUPUT(IHKL,JHKL,ISYM)
Put reflection into asymmetric unit defined by call to ASUSET
<p>
On input:
<dl>
<dt>IHKL(3)</dt><dd>
    input indices hkl
</dd></dl>
On output:
<dl>
<dt>JHKL(3)</dt><dd>
    output indices hkl
</dd><dt>ISYM</dt><dd>
       symmetry number for output<br>
                 odd  numbers are for I+<br>
                 even numbers are for I-<br>
               real-space symmetry operation number L = (ISYM-1)/2 + 1
</dd></dl>
The real-space symmetry matrices are applied by premultiplying them
by a row vector hkl,  ie  (h'k'l') = (hkl)R

@subsection asuset Subroutine ASUSET
Set up &amp; store symmetry informtion for later use in ASUPUT or ASUGET
<p>
On input:
<dl>
<dt>SPGNAM</dt><dd>
 space-group name (not used) ( character)
</dd><dt>NUMSGP</dt><dd>
  space-group number (not used)
</dd><dt>PGNAME</dt><dd>
  point-group name ( character)
</dd><dt>MSYM</dt><dd>
    total number of symmetry operations
</dd><dt>RRSYM(4,4,MSYM)</dt><dd>
 symmetry matrices (real-space)
</dd><dt>LPRINT</dt><dd>
  - printing flag. ( logical)
</dd></dl>
On output:
<dl>
<dt>PGNAME</dt><dd>
  point-group name ( character)
</dd><dt>MSYMP</dt><dd>
   number of primitive symmetry operations
</dd><dt>MLAUE</dt><dd>
   Laue group number - See PGNLAU for details
</dd></dl>

@subsection calc_orig_ps Subroutine CALC_ORIG_PS(NAMSPG_CIF,NSYM,RSYM,NORIG,ORIG,LPAXISX,LPAXISY,LPAXISZ)
Creates a list of equivalent origins for the named spacegroup.

<p>ARGUMENTS
<dl>
<dt>(I) NAMSPG_CIF</dt><dd>
  spacegroup name (character)
</dd><dt>(I) NSYM</dt><dd>
  number of symmetry operations
</dd><dt>(I) RSYM(4,4,NSYM)</dt><dd>
  symmetry ops stored as 4x4 matrices
</dd><dt>(O) NORIG</dt><dd>
  number of origins.
</dd><dt>(O) ORIG(3,i)</dt><dd>
  vector of alternate origin (for example : 0.5,0.0,0.5)
                only positive components. include vector: (0,0,0)
</dd><dt>(O) LPAXISX</dt><dd>
  logical; set true if s/grp is polar along x axis
</dd><dt>(O) LPAXISY</dt><dd>
  logical; set true if s/grp is polar along y axis
</dd><dt>(O) LPAXISZ</dt><dd>
  logical; set true if s/grp is polar along z axis
</dd></dl>
                        
<p>Taken from Alexei Vagin

@subsection ccp4_hash_lookup <i>Integer</i> Function CCP4_HASH_LOOKUP(NSER)
The function CCP4_HASH_LOOKUP returns the value NFIND (which was input when
setting up the function in the subroutine CCP4_HASH_SETUP) for the large
range variable NSER.  Uses hashing. (see comments for
CCP4_HASH_SETUP for description of hashing method).

@subsection ccp4_hash_setup Subroutine CCP4_HASH_SETUP(NSER,NFIND)
This subroutine sets up a value for the function ccp4_hash_lookup.
<p>
When ccp4_hash_lookup(nser) is later evaluated it will return nfind
<p>
This function will allow the efficient retrieval of an identifier
for a large range variable (such as a crystal number). The values
of the function ccp4_hash_lookup(nser) are stored in the array
it(2, kpri) where kpri is the prime number used to generate the
function.
<p>
The array 'it' lives in the common block which is shared by
ccp4_hash_setup and the function ccp4_hash_lookup
<p>
NOTES: A hash table is a way of storing information so that it
easily be retrieved without the need for indexing or long searches.
NSER is referred to as the "key", which is "hashed" (computer-
science speak for "messed up") by the hashing function (in this
case MOD(NSER4,KPRI) + 1) to determine where the value pair will
be stored. The function LOOKUP can then search on the same basis
when supplied with the key, to retreive the pair in (at most) 3
calculations. Note that KPRI (the table size) MUST BE A PRIME in
order for this method to work.

@subsection ccp4_hash_zeroit Subroutine CCP4_HASH_ZEROIT()
Initialises elements of array 'it' used in ccp4_hash_setup and
ccp4_hash_lookup to zero.

@subsection centr Subroutine CENTR(IH,IC)
Input IH(3) - reflection indices
<p>
Returns IC
<p>
Determine whether a reflection is centric (return IC=1)
or not (IC=0).  If none of the zone tests is satisfied,
the reflection is non-centric.

@subsection centrc <i>Logical</i> Function CENTRC(KHKL,ICENT)
Returns value as true if reflection khkl is centric, false otherwise.
It is general for all point groups - but only for the unique set of
indices which conforms to the criterion of maximising the value of
<br>
<center>        (khkl(3)*256 + khkl(2))*256 + khkl(1)</center>
<br>
as produced by e.g. subroutine turnip in protin and ulysses.
<p>
In this case the required tests are controlled by 7 flags in
icent for
<p>
<center>0KL  H0L  HK0  HKK  HKH  HHL  H,-2H,L</center>
<p>
(the last is needed in pg312)

@subsection centric Subroutine CENTRIC(NSM,RSMT,IPRINT)
This is Randy Read's method of defining centric reflections.
It uses NSM and the symmetry operators stored in RSMT(4,4,NSM)
<p>
It decides how many centric zones there are, and flags them.
<p>
set up tests for 0kl h0l hk0 hhl hkh hkk h,-hl hk-h hk-k
-h 2h l   2h -h l  hkl
<p>
Zones are encoded using an idea from a program by Bricogne.
If h*zone(1) + k*zone(2) + l*zone(3) is equal to 0.0,
that reflection is in that zone.  All that is needed is the
most general conditions - a reflection is either centric or
not.

@subsection determ Subroutine DETERM(det,a)
Gets determinant of a matrix
<dl>
<dt>Input A</dt><dd>
4*4 matrix  (real)
</dd><dt>Output DET</dt><dd>
determinant of A.
</dd></dl>


@subsection epsln Subroutine EPSLN(NSM,NSMP,RSMT,IPRINT)
It works out the epsilon cards using NSM and the symmetry operators stored in
RSMT(4,4,NSM).

This is Randys program description:

@note
zones defined as for centric zones, but
fourth number on each line is the multiplicity corresponding
to this zone.  last card should always be 0 0 0 n, where n is
appropriate for the lattice (1 for primitive, 2 for face-
centred, etc.), so that general reflections get a value
for epsilon. be very careful of the order of the zones. cards
for reciprocal lattice rows should be given before those for
planes, because the first test that is satisfied defines
the zone.
@n
set up tests for @n
h00 0k0 00l hh0 h0h 0kk h,-h0 h0-h 0k-k -h2h0 2h-h0 hhh hkl


@subsection epslon Subroutine EPSLON(IH,EPSI,ISYSAB)
Input IH(3) - reflection indices

Returns EPSI ( epsilon zone) , and ISYSAB flag.
Systematic absences flagged with ISYSAB = 1

Find the zone a reflection falls into, and return the
appropriate value for the reflection multiplicity factor.
Each reflection must have a zone.

@subsection factrz <i>Logical</i> Function FACTRZ(N)
Returns true if N has all prime factors \<= 19


@subsection fndsmp Subroutine FNDSMP(MINSMP, NMUL, SAMPLE, NSAMPL)
Find suitable grid sample, approximately = SAMPLE/2 * maximum index,
with required factor, and no prime factor > 19
<p>
On entry:
<dl>
<dt>MINSMP</dt><dd>
     minimum sample, approximately 2 * maximum index
</dd><dt>NMUL</dt><dd>
       required factor
</dd><dt>SAMPLE</dt><dd>
     desired sample factor, ie if = 1.0 (minimum), try to get sample close to MINSMP
</dd></dl>
On exit:
<dl>
<dt>nsampl</dt><dd>
     grid sample; if MINSMP\<=0, nsampl=nmul
</dd></dl>

@subsection hkleq <i>Logical</i> Function HKLEQ(IH,KH)
Checks if indices are equal.
<p>
Returns true if indices ih = kh

@subsection hklrange Subroutine HKLRANGE(IHRNG0,IKRNG1,IKRNG0,IKRNG1,ILRNG0,ILRNG1)
Return HKL ranges chosen in PGNLAUE
<p>     
Arguments: (INTEGER) HRNG0,HRNG1,KRNG0,KRNG1,LRNG0,LRNG1

@subsection inasu <i>Integer</i> Function INASU(IH, NLAUE)
Arguments:                                               
<dl>
<dt>NLAUE</dt><dd>
 - code number for this pointgroup
</dd><dt>IH(3)</dt><dd>
 - indices
</dd></dl>
Returns:
<p>
INASU = +1  if  h k l chosen<br>
INASU = -1  if -h-k-l chosen<br>
INASU =  0   if reflection is out-of-bounds

@subsection invsym Subroutine INVSYM(S,ST)
Inverts a 4*4 matrix. Used here to get inverse symmetry operation for
generating equivalent h k l, i.e.
<p>
<center>
[h']    = [h][St]
<p>
h'(j) =Sum(I=1,3)[ h(i)*St(I,J,NS)]
</center>
<p>
Arguments:
<dl>
<dt>Input S</dt><dd>
4*4 matrix to be inverted
</dd><dt>Output ST</dt><dd>
4*4 matrix (inverse of S)
</dd></dl>

@subsection krot <i>Integer</i> Function KROT(NS)
Apply NS'th symmetry operation to JP to get LP,
check if lies in asymmetric unit given by NAU.
<p>
Returns KROT=0  correct operation, =1  if not.

@subsection msyget Subroutine MSYGET(IST,LSPGRP,NSYM,ROT)
Get symmetry operations for space-group LSPGRP
from library file, logical name SYMINFO.
<p>
Arguments:
<dl>
<dt>IST</dt><dd>
dummy parameter for backwards compatibility
</dd><dt>LSPGRP (input)</dt><dd>
Name of spacegroup
</dd><dt>IST (input)</dt><dd>
Stream of library file
</dd><dt>NSYM (output)</dt><dd>
Number of symmetry operations
</dd><dt>ROT(4,4,NSYM) (output)</dt><dd>
Rotation/translation matrices
</dd></dl>

@subsection msymlb Subroutine MSYMLB(IST,LSPGRP,NAMSPG,NAMPG,NSYMP,NSYM,ROT)
Get symmetry operations from library file, logical name SYMINFO.
Space group defined by LSPGRP - spacegroup number or NAMSPG - spacegroup name.
<p>
Arguments:
<dl>
<dt>IST</dt><dd>
dummy parameter for backwards compatibility
</dd><dt>LSPGRP (I/O)</dt><dd>
spacegroup number
</dd><dt>NAMSPG (I/O)</dt><dd>
spacegroup name
</dd><dt>NAMPG  (O)</dt><dd>
pointgroup name
</dd><dt>NSYMP  (O)</dt><dd>
number of primitive symmetry operations
</dd><dt>NSYM   (O)</dt><dd>
number of symmetry operations
</dd><dt>ROT(4,4,NSYM)</dt><dd>
rotation/translation  matrices
</dd></dl>

@subsection msymlb2 Subroutine MSYMLB2(IST,LSPGRP,NAMSPG_CIF,NAMPG,NSYMP,NSYM,ROT)
Identical to MSYMLB, except that on output NAMSPG_CIF
has correct CIF format, e.g. 'P 21 21 21'
<p>
NAMSPG_CIF should be as in _symmetry.space_group_name_H-M

@subsection msymlb3 Subroutine MSYMLB3(IST,LSPGRP,NAMSPG_CIF,NAMSPG_CIFS,NAMPG,NSYMP,NSYM,RlSymmMatrx)
Another version of MSYMLB, with the following changes:
<ol>
<li>The routine will try first to match the assigned NAMSPG_CIF
    to ANY name given on the spacegroup line:
    <p>It is satisfied by the first fit it finds:
    <p>eg: 47 8 8 Pmmm PGmmm ORTHORHOMBIC 'P 2/m 2/m 2/m' 'P m m m'
    <p>You could call the subroutine with NAMSPG_CIF = 'Pmmm' or 'P 2/m 2/m 2/m' or
    'P m m m'
    <p>
    But it will always return the LONGEST possible name. ie 'P 2/m 2/m 2/m'
<li>If there is no match to the spacegroup NAME, the space group is
    identified by its number.
    This requires that the number is UNIQUE, so alternate settings are
    numbered n000 + Int Tab number
<li>The point group name is always guessed at by the SR PGDEFN
    and the guess on the data line is ignored.
<li>The number of primitive symmetry operators is also determined
    by the SR PGDEFN. The non-primitive operators are stored in the
    first NSYMP symmetry matrices and the guess on the data line is ignored.
<li>The symmetry operators are checked to make sure they are a closed group.
</ol>
In the library file, the header for each entry may contain
(Order not guaranteed, but must start with)
<p>
LSPGRP   NLINS and contain either NAMSPG or NAMSPG_CIF
<p>
LSPGRP   NLINS   NLINP   NAMSPG  NAMPG CRYSTAL  NAMSPG_CIF
<p>where:
<dl>
<dt>LSPGRP</dt><dd>
spacegroup number
</dd><dt>NLINS</dt><dd>
total number of lines of symmetry operators.
</dd><dt>NLINP</dt><dd>
number of LINES of primitive symmetry operators (not used now..)
</dd><dt>NAMSPG_CIF</dt><dd>
spacegroup name (in CIF format? presumably)
</dd><dt>NAMPG</dt><dd>
name of corresponding pointgroup (not used now..)
</dd></dl>
<p>
On entry:
<dl>
<dt>IST</dt><dd>
stream number to read file
</dd><dt>LSPGRP</dt><dd>
spacegroup number
</dd><dt>NAMSPG or NAMSPG_CIF</dt><dd>
any acceptable spacegroup name: this will be used to 
identify the spacegroup if possible
</dd></dl>
<p>
Returns:
<dl>
<dt>LSPGRP</dt><dd>
spacegroup number
</dd><dt>NAMSPG_CIF</dt><dd>
full spacegroup name 
</dd><dt>NAMSPG_CIFS</dt><dd>
name without any spaces
</dd><dt>NAMPG</dt><dd>
pointgroup name ( obtained from pgdefn - not 100% reliable!)
</dd><dt>NSYMP</dt><dd>
number of primitive symmetry operations obtained from pgdefn- 
only different from NSYM in non-primitive spacegroups
</dd><dt>NSYM</dt><dd>
total number of symmetry operations
</dd><dt>RlSymmMatrx(4,4,NSYM)</dt><dd>
Symmetry Rotation/translation  matrices
</dd></dl>

@subsection patsgp Subroutine PATSGP(SPGNAM, PGNAME, PATNAM, LPATSG)
Determine Patterson spacegroup from true space-group
<p>
On entry:
<dl>
<dt>SPGNAM</dt><dd>
    space-group name. Only used to determine lattice centering
</dd><dt>PGNAME</dt><dd>
    point-group name
</dd></dl>
On exit:
<dl>
<dt>PATNAM</dt><dd>
    name of Patterson spacegroup
</dd><dt>LPATSG</dt><dd>
    number of Patterson spacegroup
</dd></dl>

@subsection pgdefn Subroutine PGDEFN(NAMPG,NSYMP,NSYM,RSYMT,LPRINT)
Arguments:
<dl>
<dt>Input NSYM</dt><dd>
  - number of symmetry operators. ( integer)
</dd><dt>Input RSYMT</dt><dd>
 - 4*4 symmetry matrices. ( real)
</dd><dt>Input LPRINT</dt><dd>
  - printing flag. ( logical)
</dd><dt>Returns  NAMPG</dt><dd>
 - name of point group. ( character)
</dd><dt>Returns  NSYMP</dt><dd>
 - number of primitive symmetry operators. ( integer)
</dd><dt>Returns  RSYMT</dt><dd>
 - possibly reordered.
</dd></dl>
<p>
This subroutine chooses the primitive set of symmetry operators.
<p>
If necessary it re-orders the symmetry operators to give the 
primitive ones first.
<p>
This subroutine works out the point group name NAMPG. That is ; it checks
rotation axes, etc etc and recognises these point groups.  (It DOES NOT cope
with mirror planes etc)
<p>
Gronigen MDF stuff:  It now sets up the common block MDFPAR for 
MDF file mods and  fills in the symmetry info.  See subroutine for
details.

@subsection pgmdf Subroutine PGMDF(JLASS,JCENTR,JSCREW)
Gronigen subroutine.
<p>
Use this subroutine to transfer information to and from MDFPAR.<br>
If JLASS eq 0   then fill JLASS JCENTR JSCREW from common block.<br>
If JLASS gt 0   then fill KLASS ICENTR ISCREW in common block.

@subsection pgnlau Subroutine PGNLAU(NAMPG,NLAUE,LAUNAM)
Choose Laue group from PG name.
<p>
On entry:
<dl>
<dt>NAMPG</dt><dd>
      point-group name ( character)
</dd></dl>
On exit:
<dl>
<dt>NLAUE</dt><dd>
     Laue group number ( integer)
</dd><dt>LAUNAM</dt><dd>
    Laue group name ( character)
</dd></dl>

This subroutine returns a laue code number used to choose
the unique region of reciprocal space for each point group.  

The number nlaue is the same as the one set in CAD for this purpose.

@verbatim
Pointgroup Laue group        Limits

 3 pg1     1bar       hkl:l>=0  hk0:h>=0  0k0:k>=0   1,2
   pg1bar
 4 pg2 (b) 2/m        hkl:k>=0, l>=0  hk0:h>=0       3/b,4/b....
   pgm pg2/m
 5 pg2 (c) 2/m        hkl:k>=0, l>=0  h0l:h>=0       1003,1004
 6 pg222   mmm        hkl:h>=0, k>=0, l>=0            16 ...
   pgmm2 pgmmm 
 7 pg4     4/m        hkl:h>=0, l>=0 with k>=0 if  h=0  and
   pg4bar pg4/m                            k>0 if h>0
 8 pg422   4/mmm       hkl:h>=0, k>=0, l>=0            89..
   pg4mm pg4bar2m pg4barm2 pg4/mmm
 9 pg3     3bar      hkl:h>=0, k>0  00l:l>0         143..
   pg3bar
10 pg312   3/m        hkl:h>=0, k>=0 with k\<=h for all l.
   pg32 pg3m pg3m1 pg3barm1 if k = 0  l>=0
         Space group numbers :   149-151-153 157 159 162 163
11 pg321   3bar1m     hkl:h>=0, k>=0 with k\<=h for all l.
   pg31m pg3bar1m      if h = k  l>=0
         Space group numbers :   150-152-154
12 pg6     6/m        hkl:h>=0, k>=0, l>=0 with k>=0 if  h=0
   pg6bar  6/m        and k> 0 if h>0
13 pg622   6/mmm       hkl:h>=0, k>=0, l>=0 with h>=k 177..
   pg6mm pg6barm2 pg6bar2m  pg 6/mmm
14 pg23    m3         hkl:h>=0, k>=0, l>=0 with l>=h,  k>=h
   pgm3bar 
15 pg432   m3m        hkl:h>=0, k>=0, l>=0  with  k>=l
   pg4bar3m pgm3barm
@endverbatim

@subsection prmvci Subroutine PRMVCI(PERM,JV,N,N1)
<dl>
<dt>Input PERM</dt><dd>
 - 4*4 matrix  (real)
</dd><dt>Input JV</dt><dd>
   - N1*3 matrix (integer)
</dd><dt>Output JV</dt><dd>
  - N1*3 matrix (integer)<p> 
    This has been modified by permuting the Nth column by matrix PERM.
</dd></dl>
Here is the code for clarity:

@code
C---- Permute
C
C     DO 10 I = 1,3
C       BV(I) = PERM(I,1)*JV(N,1) + PERM(I,2)*JV(N,2) +
C    +          PERM(I,3)*JV(N,3)
C  10 CONTINUE
C
C---- Copy back
C
C     DO 20 I = 1,3
C       JV(N,I) = NINT(BV(I))
C  20 CONTINUE
@endcode

@subsection prmvcr Subroutine PRMVCR(PERM,AV,N,N1)
<dl>
<dt>Input PERM</dt><dd>
 - 4*4 matrix  (real)
</dd><dt>Input AV</dt><dd>
   - N1*3 matrix (real)
</dd><dt>Output AV</dt><dd>
  - N1*3 matrix (real)
   This has been modified by permuting the Nth column by matrix PERM.
</dd></dl>
<p>
See PRMVCI - this routine is its real equivalent.

@subsection prtrsm Subroutine PRTRSM(PGNAME, NSYMP, RSYMIV)
Print reciprocal space symmetry operations
<p>
The real-space symmetry matrices are applied by premultiplying them
by a row vector hkl,  ie  (h'k'l') = (hkl)R

@subsection pstoph Subroutine PSTOPH (PSIX,PSIY,PSIZ,PHIX,PHIY,PHIZ,AVPHI)
Convert PSIX,PSIY,PSIZ (= epsx,epsy,epsz) to PHIX,PHIY,PHIZ, using AVPHI
<p>
All angles in radians

@subsection rotfix Subroutine ROTFIX
Permutes inverse symmetry operations
<p>
Matrices passed in Common block ATSYM

@subsection setgrd Subroutine SETGRD(NLAUE,SAMPLE,NXMIN,NYMIN,NZMIN,NX,NY,NZ)
Set up a suitable sampling grid for FFT
<p>
Input:
<dl>
<dt>NLAUE</dt><dd>
         Laue-group for FFT/SF calculation
</dd><dt>SAMPLE</dt><dd>
        default fineness of sample, ie if = 1.0 (minimum),
        try to get sampling as close to minimum as possible.<br>
        Typically = 1.5 to get sample at traditional 3 * maximum index
</dd><dt>NXMIN NYMIN NZMIN</dt><dd>
        minimum sampling (true XYZ)
</dd></dl>
Output:
<dl>
<dt>NX,NY,NZ</dt><dd>
       sampling intervals along X,Y,Z
</dd></dl>

The sampling intervals must satisfy the following conditions:

  -# approximately SAMPLE * minimum sampling
  -# no prime factor \> 19
  -# special restrictions for particular space-groups
  .

This is ALL the point groups.

@verbatim 
 PG1 PG1bar PG2 PGm PG2/m PG222 PGmm2 PGmmm 
 PG4 PG4bar PG4/m PG422 PG4mm PG4bar2m PG4/mmm 
 PG3 PG3bar PG32 PG3m PG3barm 
 PG6 PG6bar PG6/m PG622 PG6mm PG6bar2m  PG6/mmm
 PG23 PGm/3bar PG432 PG4bar3m PGm3bar m
@endverbatim

We use:

@verbatim 
 PG1 PG1bar PG2  PG2/m PG222  PGmmm 
 PG4 PG4/m PG422 PG4/mmm 
 PG3 PG3bar PG32 PG3bar/m 
 PG6 PG6/m PG622 PG6/mmm
 PG23 PGm/3bar PG432 PGm3barm
@endverbatim

For grid restrictions we only need to know the laue number.
Here is the table:

@verbatim
   3 pg1     1bar      hkl:l>=0  hk0:h>=0  0k0:k>=0   1,2
   4 pg2    2/m        hkl:k>=0, l>=0  hk0:h>=0       3/b,4/b....
   5 pg2(c) 2/m        hkl:k>=0, l>=0  h0l:h>=0       1003,1004
   6 pg222  mmm        hkl:h>=0, k>=0, l>=0            16 ...
   7 pg4    4/m        hkl:h>=0, l>=0 with k>=0 if  h=0  and
   8 pg422 4/mmm       hkl:h>=0, k>=0, l>=0            89..
   9 pg3     3bar      hkl:h>=0, k>0  00l:l>0         143..
  10 pg312  3/m        hkl:h>=0, k>=0 with k\<=h for all l.
                           if k = 0  l>=0
           Space group numbers :   149-151-153
  11 pg321  3/m        hkl:h>=0, k>=0 with k\<=h for all l.
                           if h = k  l>=0
           Space group numbers :   150-152-154
  12 pg6    6/m        hkl:h>=0, k>=0, l>=0 with k=0 if  h=0
  13 pg622  6/mmm
  14 pg23   m3
  15 pg432  m3m
@endverbatim


@subsection setlim Subroutine SETLIM(LSPGRP,XYZLIM)
Set appropriate box (asymmetric unit) for spacegroup (true spacegroup rather than
FFT spacegroup) LSPGRP. For cubic symmetry spacegroups, this will be more than
one asymmetric unit.
<p>
On entry:
<dl>
<dt>lspgrp</dt><dd>
    true spacegroup (not FFT spacegroup)
</dd></dl>
On exit:
<dl>
<dt>xyzlim(2,3)</dt><dd>
  minimum, maximum limits on x,y,z (fractions of cell); if spacegroup not
  recognized, returns xzylim(1,1) = -1.0<br>
  Note that the minimum limits (xyzlim(1,)) will always = 0.0
</dd></dl>

@subsection setlim_zero Subroutine SETLIM_ZERO(LSPGRP,XYZLIM)
Set appropriate box (asymmetric unit) for spacegroup (true spacegroup rather than
FFT spacegroup) LSPGRP. For cubic symmetry spacegroups, this will be more than
one asymmetric unit.
<p>
NB This s/r differs from SETLIM in that the limits are taken from cctbx
via CCP4's syminfo.lib file.
<p>
On entry:
<dl>
<dt>lspgrp</dt><dd>
    true spacegroup (not FFT spacegroup)
</dd></dl>
On exit:
<dl>
<dt>xyzlim(2,3)</dt><dd>
  minimum, maximum limits on x,y,z (fractions of cell); if spacegroup not
  recognized, returns xzylim(1,1) = -1.0<br>
  Note that the minimum limits (xyzlim(1,)) will always = 0.0
</dd></dl>

@subsection setrsl Subroutine SETRSL(A,B,C,ALPHA,BETA,GAMMA)
Routine to calculate coefficients for (sin(theta)/lambda)**2 from
h,k,l for general axes.
<p>
First calculates the components of input axes in an orthonormal
basis, then calculate components of reciprocal axes in same basis.
<p>
The input angles are in degrees.

@subsection sthlsq <i>Real</i> Function STHLSQ(IH,IK,IL)
Calculate (sin(theta)/lambda)**2 from h,k,l. The coefficients are set by
a previous call to SETRSL. Works for any kind of axes.

@subsection sts3r4 <i>Real</i> Function STS3R4(IH,IK,IL)
Calculate (sin(theta)/lambda)**2 from h,k,l. The coefficients are set by a
call to SETRSL. Works for any kind of axes.

@subsection symfr2 Subroutine SYMFR2(ICOL,I1,NS,ROT)
Read and interpret symmetry operations

<p>SYMFR2 recognises the following types of input:
@verbatim     real space symmetry operations, e.g. X+1/2,Y-X,Z
     reciprocal space operations,    e.g. h,l-h,-k
     reciprocal axis vectors,        e.g. a*+c*,c*,-b*
     real space axis vectors,        e.g. a,c-a,-b
@endverbatim
<p>The subroutine returns the appropriate 4x4 transformation
matrix for each operation. The calling program must
interpret the resulting matrix(ces) correctly.

<p>On entry I1 is the first character of ICOL to look at (say after
keyword 'SYMM')

<p>NS is the number of the first symmetry operation to be read, &amp; returns
with the number of the last one read.

<p>On exit, ROT(4,4,NS) contains the real-space symmetry matrices, in standard
convention, i.e.
<p>
<center>
[x']    = [s][x]
<p>
x'(I)=Sum(J=1,3)ROT(I,J,NS)*x(J) + ROT(I,4,NS)
</center>
<p>
Input:
<dl>
<dt>ICOL</dt><dd>
character string containing symmetry operations
</dd><dt>I1</dt><dd>
first character in ICOL to interpret from.
</dd></dl>
Output:
<dl>
<dt>ROT(I,4,NS)</dt><dd>
contains the fractional translations.
</dd></dl>

@subsection symfr3 Subroutine SYMFR3(ICOL,I1,NS,ROT,EFLAG)
Read and interpret symmetry operations.
<p>
Arguments:
<p>
<dl>
<dt>ICOL      (I)	CHARACTER*80</dt><dd>
Line containing the symmetry operations
</dd><dt>I1        (I)	INTEGER</dt><dd>
First character to look at in ICOL (say after keyword 'SYM')
</dd><dt>NS        (I/O)	INTEGER</dt><dd>
is the number of the first symmetry operation to be read, &amp; returns with the
number of the last one read (ie you can have more than one on a line!)
</dd><dt>ROT       (O)	REAL</dt><dd>
Array (4,4,at_least_NS), on exit contains the real-space
symmetry matrices, in standard convention, i.e.
<br><center>[x']    = [s][x]</center>
<br><center>x'(I)=Sum(J=1,3)ROT(I,J,NS)*x(J) + ROT(I,4,NS)</center>
<br>ROT(I,4,NS) contains the fractional translations
</dd><dt>EFLAG     (O)	INTEGER</dt><dd>
Error flag - on exit, if 0 then OK, \> 0, an error occurred.
</dd></dl>

@subsection symtrn Subroutine SYMTRN(NSM,RSM)
Symmetry translation from matrix back to characters
<p>
This translates the symmetry matrices RSM(4,4,NSM) into INT TAB
character strings
<p>
It gives the real and reciprocal space operations.
@verbatim                eg     X,Y,Z        H  , K, L
                eg     -Y,X-Y, Z   -H-K, H, L  etc
@endverbatim
That is more complicated than you might think!!

@subsection symtr3 Subroutine SYMTR3(NSM,RSM)
Symmetry translation from matrix back to characters
<p>
This translates the symmetry matrices RSM(4,4,NSM) into INT TAB
character strings
<p>
It gives the real and reciprocal space operations.
@verbatim                eg     X,Y,Z        H  , K, L
                eg     -Y,X-Y, Z   -H-K, H, L  etc
@endverbatim
That is more complicated than you might think!!
<p>
Arguments :
<dl>
<dt>NSM       (I)     INTEGER</dt><dd>
Number of Symmetry operations
</dd><dt>RSM       (I)     REAL</dt><dd>
Array of dimension (4,4,at least NSM) containing symmetry operations on input
</dd><dt>SYMCHS    (O)     CHARACTER*(*)</dt><dd>
Array of dimension at least NSM containing int tab char strings on output
</dd><dt>IPRINT    (I)     INTEGER</dt><dd>
Print flag<br>
=0 No printing<br>
=1 Print the int tab strings
</dd></dl>

@subsection symtr4 Subroutine SYMTR4(NSYM,RSM,SYMCHS)
Symmetry translation from matrix back to characters
<p>
This translates the symmetry matrices RSM(4,4,NSM) into INT TAB
character strings
<p>
It gives the real and reciprocal space operations.
@verbatim                eg     X,Y,Z        H  , K, L
                eg     -Y,X-Y, Z   -H-K, H, L  etc
@endverbatim
That is more complicated than you might think!!
<p>
Arguments :
<dl>
<dt>Nsym (I) INTEGER</dt><dd>
Number of Symmetry operations
</dd><dt>Rsm  (I) REAL</dt><dd>
Array of dimension (4,4,at least Nsym) containing symmetry operations on input
</dd><dt>Symchs (O) CHARACTER*(*)</dt><dd>
Array of dimension at least Nsym containing int tab char strings on output
</dd></dl>

@subsection sysab Subroutine SYSAB(IN,ISYSAB)
Input IN(3) - reflection indices
<p>
Returns  ISYSAB flag.
Systematic absences flagged with ISYSAB = 1
Only reflns with EPSI \> 1 need be considered.

@subsection xspecials Subroutine XSPECIALS(NSYM,RSYM,XF,YF,ZF,NSPEC)
<dl>
<dt>Input NSYM</dt><dd>
  - number of symmetry operators. ( integer)
</dd><dt>Input RSYM</dt><dd>
  - 4*4*NSYM symmetry matrices. ( real)
</dd><dt>Input XF YF ZF</dt><dd>
  - a coordinate in fractional coordinates.
</dd><dt>Output NSPEC</dt><dd>
 - the multiplicity of the coordinate.
   eg: NSPEC = 3 for an atom on a 3fod axis.
</dd></dl>

This subroutine finds what coordinates occupy special positions
i.e. have occupancies less than 1.0
from consideration of the symmetry operations.

@section asymmetric_unit DEFINITION OF THE CCP4 ASYMMETRIC UNIT

There is no standard defined asymmetric unit so the definitions are 
arbitrary and may differ between differ packages. The subroutines in
@ref group_3_a group 3.a are used to define the CCP4 asymmetric unit, and
to determine whether a reflection falls within this definition.

Below are the definitions of the @ref recip_asym_unit reciprocal space
and the @ref real_asym_unit real space asymmetric units under the CCP4
convention.

@subsection recip_asym_unit a. Reciprocal Space Asymmetric Unit Definitions

The reciprocal space asymmetric unit is defined in the subroutine ASUSET 
from the Laue group using calls to the s/r's PGDEFN and PGNLAU. The 
limits of the CCP4 asymmetric unit are (from @ref pgnlau PGNLAU):


<table border="1">
<tr>
 <th colspan="2"> Pointgroup
 </th><th>Laue group
 </th><th>Limits
 </th><th>Spacegroup Nos
</th></tr><tr>
 <td>3
 </td><td>pg1 <br> pg1bar
 </td><td>1bar
 </td><td>hkl:l\>=0 <br> hk0:h\>=0 <br> 0k0:k\>=0
 </td><td>1,2
</td></tr><tr>
 <td>4
 </td><td>pg2 (b) <br> pgm pg2/m
 </td><td>2/m
 </td><td>hkl:k\>=0, l\>=0 <br> hk0:h\>=0
 </td><td>3,4....
</td></tr><tr>
 <td>5
 </td><td>pg2 (c)
 </td><td>2/m
 </td><td>hkl:k\>=0, l\>=0 <br> h0l:h\>=0
 </td><td>1003, 1004
</td></tr><tr>
 <td>6
 </td><td>pg222 <br> pgmm2 <br> pgmmm
 </td><td>mmm
 </td><td>hkl:h\>=0, k\>=0, l\>=0
 </td><td>16 ...
</td></tr><tr>
 <td>7
 </td><td>pg4 <br> pg4bar <br> pg4/m
 </td><td>4/m
 </td><td>hkl:h\>=0, l\>=0 with k\>=0 if h=0<br>
     and k\>0 if h\>0
 </td><td>75,..
</td></tr><tr>
 <td>8
 </td><td>pg422 pg4mm pg4bar2m <br> pg4barm2 pg4/mm
 </td><td>4/mmm
 </td><td>hkl:h\>=0, k\>=0, l\>=0
 </td><td>89,..
</td></tr><tr>
 <td>9
 </td><td>pg3 <br> pg3bar
 </td><td>3bar
 </td><td>hkl:h\>=0, k\>0 00l:l\>0
 </td><td>143,..
</td></tr><tr>
 <td>10
 </td><td>pg312 pg32 <br> pg3m pg3m1 pg3barm1
 </td><td>3/m
 </td><td>hkl:h\>=0, k\>=0 with k\<=h for all l. <br>
                                   if k=0  l\>=0
 </td><td>149 151 153 157 159 162 163
</td></tr><tr>
 <td>11
 </td><td>pg321 pg31m pg3bar1m
 </td><td>3bar1m
 </td><td>hkl:h\>=0, k\>=0 with k\<=h for all l. <br>
                                   if k=h  l\>=0
 </td><td>150 152 154
</td></tr><tr>
 <td>12
 </td><td>pg6 pg6bar
 </td><td>6/m
 </td><td>hkl:h\>=0, k\>=0, l\>=0 with k\>=0 if h=0
                                   and k\>0 if h\>0
 </td><td>168..
</td></tr><tr>
 <td>13
 </td><td>pg622 pg6mm pg6barm2 pg6bar2m pg6/mmm
 </td><td>6/mmm
 </td><td>hkl:h\>=0, k\>=0, l\>=0 with h\>=k
 </td><td>177..
</td></tr><tr>
 <td>14
 </td><td>pg23 pgm3bar
 </td><td>m3
 </td><td>hkl:h\>=0, k\>=0, l\>=0 with l\>=h, k\>=h
 </td><td>195..
</td></tr><tr>
 <td>15
 </td><td>pg432 pg4bar3m pgm3barm
 </td><td>m3m
 </td><td>hkl:h\>=0, k\>=0, l\>=0 with k\=1
 </td><td>209..
</td></tr>
</table>


@subsection real_asym_unit b. Real Space Asymmetric Unit Definitions

The subroutine @ref setlim SETLIM contains the definitions of the
real space asymmetric unit. Note that not all of the spacegroups have a
definition within SETLIM.

<table border="1">
<tr>
 <th>No.
 </th><th>Spacegroup
 </th><th>Upper limits on x, y, z @ref asterisk (*)
</th></tr><tr>
 <td>  1
 </td><td>P 1                 
 </td><td>x \< 1,    y \< 1,    z \< 1,    
</td></tr><tr>
 <td>  2
 </td><td>P -1                
 </td><td>x \< 1,    y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td>  3
 </td><td>P 1 2 1             
 </td><td>x \<= 1/2, y \< 1,    z \< 1,    
</td></tr><tr>
 <td>  4
 </td><td>P 1 21 1            
 </td><td>x \< 1,    y \< 1/2,  z \< 1,    
</td></tr><tr>
 <td>  5
 </td><td>C 1 2 1             
 </td><td>x \<= 1/2, y \< 1/2,  z \< 1,    
</td></tr><tr>
 <td> 10
 </td><td>P 1 2/M 1           
 </td><td>x \<= 1/2, y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td> 16
 </td><td>P 2 2 2             
 </td><td>x \<= 1/2, y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td> 17
 </td><td>P 2 2 21            
 </td><td>x \<= 1/2, y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td> 18
 </td><td>P 21 21 2           
 </td><td>x \< 1,    y \<= 1/4, z \< 1,    
</td></tr><tr>
 <td> 19
 </td><td>P 21 21 21          
 </td><td>x \< 1,    y \< 1,    z \<= 1/4, 
</td></tr><tr>
 <td> 20
 </td><td>C 2 2 21            
 </td><td>x \<= 1/2, y \<= 1/4, z \< 1,    
</td></tr><tr>
 <td> 21
 </td><td>C 2 2 2             
 </td><td>x \<= 1/2, y \<= 1/4, z \< 1,    
</td></tr><tr>
 <td> 22
 </td><td>F 2 2 2             
 </td><td>x \<= 1/4, y \<= 1/4, z \< 1,    
</td></tr><tr>
 <td> 23
 </td><td>I 2 2 2             
 </td><td>x \<= 1/2, y \<= 1/4, z \<= 1,   
</td></tr><tr>
 <td> 24
 </td><td>I 21 21 21          
 </td><td>x \<= 1/2, y \<= 1/4, z \< 1,    
</td></tr><tr>
 <td> 47
 </td><td>P 2/M 2/M 2/M       
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td> 65
 </td><td>C 2/M 2/M 2/M       
 </td><td>x \<= 1/2, y \<= 1/4, z \<= 1/2, 
</td></tr><tr>
 <td> 69
 </td><td>F 2/M 2/M 2/M       
 </td><td>x \<= 1/4, y \<= 1/4, z \<= 1/2, 
</td></tr><tr>
 <td> 71
 </td><td>I 2/M 2/M 2/M       
 </td><td>x \<= 1/2, y \<= 1/4, z \<= 1/2, 
</td></tr><tr>
 <td> 75
 </td><td>P 4                 
 </td><td>x \<= 1/2, y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td> 76
 </td><td>P 41                
 </td><td>x \< 1,    y \< 1,    z \< 1/4,  
</td></tr><tr>
 <td> 77
 </td><td>P 42                
 </td><td>x \<= 1/2, y \< 1,    z \< 1/2,  
</td></tr><tr>
 <td> 78
 </td><td>P 43                
 </td><td>x \< 1,    y \< 1,    z \< 1/4,  
</td></tr><tr>
 <td> 79
 </td><td>I 4                 
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td> 80
 </td><td>I 41                
 </td><td>x \<= 1/2, y \< 1,    z \< 1/4,  
</td></tr><tr>
 <td> 83
 </td><td>P 4/M               
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td> 87
 </td><td>I 4/M               
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/4, 
</td></tr><tr>
 <td> 89
 </td><td>P 4 2 2             
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td> 90
 </td><td>P 4 21 2            
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td> 91
 </td><td>P 41 2 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td> 92
 </td><td>P 41 21 2           
 </td><td>x \< 1,    y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td> 93
 </td><td>P 42 2 2            
 </td><td>x \<= 1/2, y \< 1,    z \<= 1/4, 
</td></tr><tr>
 <td> 94
 </td><td>P 42 21 2           
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td> 95
 </td><td>P 43 2 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td> 96
 </td><td>P 43 21 2           
 </td><td>x \< 1,    y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td> 97
 </td><td>I 4 2 2             
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/4, 
</td></tr><tr>
 <td> 98
 </td><td>I 41 2 2            
 </td><td>x \<= 1/2, y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td>123
 </td><td>P 4/M 2/M 2/M       
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>139
 </td><td>I 4/M 2/M 2/M       
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/4, 
</td></tr><tr>
 <td>143
 </td><td>P 3                 
 </td><td>x \<= 2/3, y \<= 2/3, z \< 1,    
</td></tr><tr>
 <td>144
 </td><td>P 31                
 </td><td>x \< 1,    y \< 1,    z \< 1/3,  
</td></tr><tr>
 <td>145
 </td><td>P 32                
 </td><td>x \< 1,    y \< 1,    z \< 1/3,  
</td></tr><tr>
 <td>146
 </td><td>H 3                 
 </td><td>x \<= 2/3, y \<= 2/3, z \< 1/3,  
</td></tr><tr>
 <td>147
 </td><td>P -3                
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/2, 
</td></tr><tr>
 <td>148
 </td><td>R -3                
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/6, 
</td></tr><tr>
 <td>149
 </td><td>P 3 1 2             
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/2, 
</td></tr><tr>
 <td>150
 </td><td>P 3 2 1             
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/2, 
</td></tr><tr>
 <td>151
 </td><td>P 31 1 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/6, 
</td></tr><tr>
 <td>152
 </td><td>P 31 2 1            
 </td><td>x \< 1,    y \< 1,    z \<= 1/6, 
</td></tr><tr>
 <td>153
 </td><td>P 32 1 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/6, 
</td></tr><tr>
 <td>154
 </td><td>P 32 2 1            
 </td><td>x \< 1,    y \< 1,    z \<= 1/6, 
</td></tr><tr>
 <td>155
 </td><td>H 3 2               
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/6, 
</td></tr><tr>
 <td>162
 </td><td>P -31 2/M           
 </td><td>x \<= 2/3, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>164
 </td><td>P -3 2/M 1          
 </td><td>x \<= 2/3, y \<= 1/3, z \<= 1,   
</td></tr><tr>
 <td>166
 </td><td>R -3 2/M            
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/6, 
</td></tr><tr>
 <td>168
 </td><td>P 6                 
 </td><td>x \<= 2/3, y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td>169
 </td><td>P 61                
 </td><td>x \< 1,    y \< 1,    z \< 1/6,  
</td></tr><tr>
 <td>170
 </td><td>P 65                
 </td><td>x \< 1,    y \< 1,    z \< 1/6,  
</td></tr><tr>
 <td>171
 </td><td>P 62                
 </td><td>x \< 1,    y \< 1,    z \< 1/3,  
</td></tr><tr>
 <td>172
 </td><td>P 64                
 </td><td>x \< 1,    y \< 1,    z \< 1/3,  
</td></tr><tr>
 <td>173
 </td><td>P 63                
 </td><td>x \<= 2/3, y \<= 2/3, z \< 1/2,  
</td></tr><tr>
 <td>175
 </td><td>P 6/M               
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/2, 
</td></tr><tr>
 <td>177
 </td><td>P 6 2 2             
 </td><td>x \<= 2/3, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>178
 </td><td>P 61 2 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/12,
</td></tr><tr>
 <td>179
 </td><td>P 65 2 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/12,
</td></tr><tr>
 <td>180
 </td><td>P 62 2 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/6, 
</td></tr><tr>
 <td>181
 </td><td>P 64 2 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/6, 
</td></tr><tr>
 <td>182
 </td><td>P 63 2 2            
 </td><td>x \<= 2/3, y \<= 2/3, z \<= 1/4, 
</td></tr><tr>
 <td>191
 </td><td>P 6/M 2/M 2/M       
 </td><td>x \<= 2/3, y \<= 1/3, z \<= 1/2, 
</td></tr><tr>
 <td>195
 </td><td>P 2 3               
 </td><td>x \< 1,    y \< 1,    z \<= 1/2, 
</td></tr><tr>
 <td>196
 </td><td>F 2 3               
 </td><td>x \<= 1/4, y \<= 1/4, z \< 1,    
</td></tr><tr>
 <td>197
 </td><td>I 2 3               
 </td><td>x \< 1,    y \< 1,    z \<= 1/2, 
</td></tr><tr>
 <td>198
 </td><td>P 21 3              
 </td><td>x \<= 1/2, y \<= 1/2, z \< 1,    
</td></tr><tr>
 <td>199
 </td><td>I 21 3              
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>200
 </td><td>P 2/M -3            
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>202
 </td><td>F 2/M -3            
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/4, 
</td></tr><tr>
 <td>204
 </td><td>I 2/M -3            
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>207
 </td><td>P 4 3 2             
 </td><td>x \< 1,    y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>208
 </td><td>P 42 3 2            
 </td><td>x \<= 1/2, y \< 1,    z \<= 1/4, 
</td></tr><tr>
 <td>209
 </td><td>F 4 3 2             
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>210
 </td><td>F 41 3 2            
 </td><td>x \<= 1/2, y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td>211
 </td><td>I 4 3 2             
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/4, 
</td></tr><tr>
 <td>212
 </td><td>P 43 3 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td>213
 </td><td>P 41 3 2            
 </td><td>x \< 1,    y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td>214
 </td><td>I 41 3 2            
 </td><td>x \<= 1/2, y \< 1,    z \<= 1/8, 
</td></tr><tr>
 <td>221
 </td><td>P 4/M -3 2/M        
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/2, 
</td></tr><tr>
 <td>225
 </td><td>F 4/M -3 2/M        
 </td><td>x \<= 1/2, y \<= 1/4, z \<= 1/4, 
</td></tr><tr>
 <td>229
 </td><td>I 4/M -3 2/M        
 </td><td>x \<= 1/2, y \<= 1/2, z \<= 1/4, 
</td></tr>
</table>

@anchor asterisk (*) The limits are in fractional coordinates,
and the lower limits are always x=0, y=0, z=0.

*/

/*
  Local variables:
  mode: font-lock
  End:
*/
