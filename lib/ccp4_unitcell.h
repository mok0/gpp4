/*
     ccp4_unitcell.h: headers for C library for ccp4_unitcell.c
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

/** @file ccp4_unitcell.h
 *  @brief C library for manipulations based on cell parameters.
 *  @author Martyn Winn 
 */

#ifndef __CCP4_UNITCELL
#define __CCP4_UNITCELL

#ifdef  __cplusplus
namespace CCP4uc {
extern "C" {
#endif

#include <math.h>

double ccp4uc_frac_orth_mat(const double cell[6], const int ncode, 
			   double ro[3][3], double rf[3][3]);

double ccp4uc_calc_rcell(const double cell[6], double rcell[6]);

void ccp4uc_orth_to_frac(const double rf[3][3], const double xo[3], double xf[3]);

void ccp4uc_frac_to_orth(const double ro[3][3], const double xf[3], double xo[3]);

void ccp4uc_orthu_to_fracu(const double rf[3][3], const double uo[6], double uf[6]);

void ccp4uc_fracu_to_orthu(const double ro[3][3], const double uf[6], double uo[6]);

double ccp4uc_calc_cell_volume(const double cell[6]);

int ccp4uc_cells_differ(const double cell1[6], const double cell2[6], const double tolerance);

int ccp4uc_is_rhombohedral(const float cell[6], const float tolerance);

int ccp4uc_is_hexagonal(const float cell[6], const float tolerance);

#ifdef __cplusplus
} }
#endif

#endif  /*!CCP4_UNITCELL */
