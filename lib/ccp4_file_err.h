/*
     ccp4_file_err.h: header file with file handling error codes
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
#ifndef _GUARD_FILE_ERR
#define _GUARD_FILE_ERR

#define CCP4_ERRNO(y) (CCP4_ERR_FILE | (y))
#define CIO_Ok 0
#define CIO_BadMode 1
#define CIO_CantOpenFile 2
#define CIO_MaxFile 3
#define CIO_ReadFail 4
#define CIO_WriteFail 5
#define CIO_CloseFail 6
#define CIO_SeekFail 7
#define CIO_NullPtr 8
#define CIO_EOF 9
#define CIO_NoFile 10
#define CIO_NotOpen 11
#define CIO_UnlinkFail 12

#endif

