/*
     cmaplib_f.h: header files for cmaplib_f.c
     Copyright (C) 2001  CCLRC, Charles Ballard

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

/*! @file cmaplib_f.h
    @brief Definition of the IOConvMap structure.
    Apparently not used anywhere (?).
    @author Charles Ballard.
*/


#ifndef __GUARD_MAPLIB_FORTRAN
#define __GUARD_MAPLIB_FORTRAN

#include "cmaplib.h"

#define MAXMAP MAXFILES

typedef struct _IOConvMap IOConvMap;

struct _IOConvMap {
  int ipc;
  char *logname;
  CMMFile *mapfile;
};

#endif  /*  __GUARD_MAPLIB_FORTRAN */

/*
  Local variables:
  mode: font-lock
  End:
*/
