/*
     ccp4_types.h: CCP4 library.c macro definitions etc
     Copyright (C) 2001  CCLRC
     Copyright (C) 2007  Morten Kjeldgaard

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

/*! @file ccp4_types.h
  @brief Header file containing various commonly used type definitions 
         and some useful macros.
 */

#ifndef __CCP4_TYPES
#define __CCP4_TYPES

#include "ccp4_sysdep.h"

#ifdef HAVE_STDINT_H
#include <stdint.h>
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef unsigned char uint8;

#else

typedef unsigned short uint16;
#ifdef SIXTEENBIT
typedef unsigned long uint32;
#else
typedef unsigned int uint32;
#endif
typedef unsigned char uint8;
#endif

typedef float float32;

/*! @union float_uint_uchar
  @brief Common data structure for floats, ints, and chars
 */
union float_uint_uchar {
  float32 f;			/*!<  float member  */
  uint32 i;			/*!<  32 bit integer member  */
  uint8 c[4];			/*!<  member of four bytes */
  };

/*! @typedef pstr  generic character pointer */
typedef char *pstr;		

/* CCP4 library.c macro definitions */

#ifndef FALSE
#  define FALSE 0
#  define TRUE 1
#endif

/*! @struct COMPLEX 
    @brief Contruct representing a complex number.
*/
typedef struct { double r;             /*!<  real component */
                 double i;             /*!<  imaginary component */
               } COMPLEX;              /*!<  complex number type */

/*! @struct POLAR
    @brief Contruct representing a polar coordinate complex number.
 */
typedef struct { double r;             /*!<  radial component  */
                 double phi;           /*!<  angular component */
               } POLAR;                /*!<  complex number type */

/* some simple macros, which may exist anyway */

/*! @def SQR(x) 
@brief A macro that returns the square of x.
*/
#ifndef SQR
#  define SQR(x) ((x)*(x))
#endif

/*! @def DEGREE(x) 
  @brief Convert radians to degrees.
  The result will be in [0:360].
*/
#ifndef DEGREE
#  define DEGREE(x) ((((x < 0)?(x)+2*M_PI:(x))*360)/(2*M_PI))
#endif

/*! @def RADIAN(x) 
  @brief Convert degrees to radians.
  The result will be in [0:pi].
*/
#ifndef RADIAN
#  define RADIAN(x) ((((x<0)?(x)+360:(x))*2*M_PI)/360)
#endif

/*! @def MAX(x,y) 
@brief A macro that returns the maximum of \a x and \a y. 
*/
#ifndef MAX
#  define MAX(x, y) (((x)>(y))?(x):(y))
#endif

/*! @def MIN(x,y) 
@brief A macro that returns the minimum of \a x and \a y. 
*/
#ifndef MIN
#  define MIN(x, y) (((x)<(y))?(x):(y))
#endif

/*! @def ABS(x) 
@brief A macro that returns the absolute value of \a x.
*/
#ifndef ABS
#  define ABS(x) (((x)<0)?-(x):(x))
#endif

/*! @def SIGN(x) 
@brief Return the sign of \a x.
*/
#ifndef SIGN
#  define SIGN(x) (((x)<0)?-1:1)
#endif

#endif   /* __CCP4_TYPES */

/*
  Local variables:
  mode: font-lock
  End:
*/
