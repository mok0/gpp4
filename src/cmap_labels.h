/*
     cmap_labels.h: header for cmap_labels.c
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

/*! @file cmap_labels.h
    @brief Declaration of routines to parse and output map labels.
    @author Charles Ballard.
*/

#ifndef __GUARD_MAPLIB_LABEL
#define __GUARD_MAPLIB_LABEL

#ifdef __cplusplus
extern "C" {
#endif

int parse_maplabels(CMMFile *mfile);
int write_maplabels(const CMMFile *mfile);


#ifdef __cplusplus
}
#endif

#endif    /* __GUARD_MAPLIB_LABEL */

/*
  Local variables:
  mode: font-lock
  End:
*/
