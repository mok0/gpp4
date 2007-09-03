/*
     cvecmat.c: C library for vector and matrix manipulations
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

/*! @file cvecmat.c
    @brief C library for vector and matrix manipulations.
    @author Martyn Winn 
 */

#include "cvecmat.h"

/*! Vector cross product
   This function computes the vector cross product c = a X b  

  @param[in] a vector 1
  @param[in] b vector 2
  @param[out] c cross product vector

*/

void ccp4_dcross(const double a[3], const double b[3], double c[3])
{
  c[0] = a[1]*b[2] - b[1]*a[2];
  c[1] = a[2]*b[0] - b[2]*a[0];
  c[2] = a[0]*b[1] - b[0]*a[1];
}


/*! 3x3 matrix product
  This function computes the matrix product between two 3x3 matrices.
  @param[out] c matrix product 
  @param[in] a left matrix
  @param[in] b right matrix
*/
  
void ccp4_3matmul(double c[3][3], const double a[3][3], const double b[3][3])
{
  int i,j,k;

  for ( i = 0; i < 3; i++ ) 
    for ( j = 0; j < 3; j++ ) {
      c[i][j] = 0.0;
      for ( k = 0; k < 3; k++ ) 
        c[i][j] += a[i][k]*b[k][j];
    }
}

/*! 4x4 matrix product.
  This function computes the matrix product between two 4x4 matrices.
  @param[out] c matrix product 
  @param[in] a left matrix
  @param[in] b right matrix
*/
void ccp4_4matmul( float c[4][4], const float  a[4][4], const float b[4][4])
{
  int i,j,k;

  for ( i = 0; i < 4; i++ ) 
    for ( j = 0; j < 4; j++ ) {
      c[i][j] = 0.0;
      for ( k = 0; k < 4; k++ ) 
        c[i][j] += a[i][k]*b[k][j];
    }
}


/*! 3x3 matrix inversion.
  @param[in] a  3*3 matrix to be inverted 
  @param[out] ai inverse matrix
  @return  Determinant 
*/

double invert3matrix(const double a[3][3], double ai[3][3])

{ int i,j;
  double c[3][3],d;

  ccp4_dcross(a[1],a[2],c[0]);
  ccp4_dcross(a[2],a[0],c[1]);
  ccp4_dcross(a[0],a[1],c[2]);

  d = a[0][0]*c[0][0] + a[0][1]*c[0][1] + a[0][2]*c[0][2];

  if (d > 1.0e-30) {
    for ( i = 0; i < 3; i++ ) 
      for ( j = 0; j < 3; j++ ) 
        ai[i][j] = c[j][i] / d;
  } else {
    return 0;
  }
  return d;
}


/*! 4x4 matrix inversion.
  @param[in] a  4x4 matrix to be inverted 
  @param[out] ai inverse matrix
  @return Determinant 
*/

float invert4matrix(const float a[4][4], float ai[4][4])

{
    float c[4][4], d;
    int i, j;
    float x[3][3];
    int i1, j1, i2 ;
    float am;
    int ii, jj;

    /* Function Body */
    for (ii = 0; ii < 4; ++ii) {
	for (jj = 0; jj < 4; ++jj) {
	    i = -1;
	    for (i1 = 0; i1 < 4; ++i1) {
		if (i1 != ii) {
		    ++i;
		    j = -1;
		    for (j1 = 0; j1 < 4; ++j1) {
			if (j1 != jj) {
			    ++j;
			    x[i][j] = a[i1][j1];
			}
		    }
		}
	    }

	    am = x[0][0]*x[1][1]*x[2][2] - x[0][0]*x[1][2]*x[2][1] +
     +         x[0][1]*x[1][2]*x[2][0] - x[0][1]*x[1][0]*x[2][2] +
     +         x[0][2]*x[1][0]*x[2][1] - x[0][2]*x[1][1]*x[2][0];
	    i2 = ii + jj;
	    c[ii][jj] = ccp4_pow_ii(-1.0, i2) * am;
	}
    }

/* ---- Calculate determinant */

    d = 0.0;

    for (i = 0; i < 4; ++i) {
	d = a[i][0] * c[i][0] + d;
    }

/* ---- Get inverse matrix */


  if (d > 1.0e-30) {
    for (i = 0; i < 4; ++i) {
	for (j = 0; j < 4; ++j) {
	    ai[i][j] = c[j][i] / d;
	}
    }
  } else {
    return 0;
  }

  return d;
} 

/*! Compute powers.
  This function computes powers of any base to any integer power.
  @param[in] base 
  @param[in] power
  @return result of power calculation
 */
float ccp4_pow_ii(const float base, const int power) {

  int i = 0;
  float pow = 1;

  while (++i <= power)
    pow *= base;

  return pow;
}


/*
  Local variables:
  mode: font-lock
  End:
*/
