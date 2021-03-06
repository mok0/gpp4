/*
     cmap_errno.h: error codes for map handling functions
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

/*! @file cmap_errno.h
    @brief Error codes for the library
    @author Charles Ballard.
*/

#ifndef __GUARD_MAPLIB_ERR
#define __GUARD_MAPLIB_ERR

#include "ccp4_errno.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMAP_ERRNO(n) (CCP4_ERR_MAP | (n))

/* error defs */
#define  CMERR_Ok                  0
#define  CMERR_NoChannel           1
#define  CMERR_NoFile              2
#define  CMERR_NoLogicalName       3
#define  CMERR_CantOpenFile        4
#define  CMERR_NoHeader            5
#define  CMERR_ReadFail            6
#define  CMERR_WriteFail           7
#define  CMERR_ParamError          8
#define  CMERR_UnrecognK           9
#define  CMERR_FileStamp           10
#define  CMERR_SymErr              11
#define  CMERR_AllocFail           12
#define  CMERR_MaxFile             13
#define  CMERR_SeekFail            14

#ifdef __cplusplus
}
#endif

#endif     /* __GUARD_MAPLIB_ERR */


/*
  Local variables:
  mode: font-lock
  End:
*/
