/*
     cvecmat.h: header file for cvecmat.c
     Copyright (C) 2001  CCLRC, Martyn Winn

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

/*! @file cvecmat.h
    @brief Declarations of matrix and vector handling functions.
    @author Martyn Winn
*/

#ifndef __CCP4_VECMAT
#define __CCP4_VECMAT

#ifdef  __cplusplus
extern "C" {
#endif

void ccp4_dcross(const double a[3], const double b[3], double c[3]);
void ccp4_3matmul(double c[3][3], const double a[3][3], const double b[3][3]);
void ccp4_4matmul( float c[4][4], const float  a[4][4], const float b[4][4]);
double invert3matrix(const double a[3][3], double ai[3][3]);
float invert4matrix(const float a[4][4], float ai[4][4]);

float ccp4_pow_ii(const float base, const int power);

#ifdef __cplusplus
}
#endif

#endif  /*!CCP4_VECMAT */

/*
  Local variables:
  mode: font-lock
  End:
*/
