/*
     cmap_skew.h: header file for cmap_skew.c
     Copyright (C) 2001  CCLRC, Charles Ballard

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

/*! @file cmap_skew.h
    @brief Declaration of the skew_set function.
    @author Charles Ballard.
*/

#ifndef __GUARD_MAPLIB_SKEW
#define __GUARD_MAPLIB_SKEW

#ifdef __cplusplus
extern "C" {
#endif

int skew_set(const CMMFile_Skew *skew);

#ifdef __cplusplus
}
#endif

#endif    /* __GUARD_MAPLIB_SKEW */

/*
  Local variables:
  mode: font-lock
  End:
*/