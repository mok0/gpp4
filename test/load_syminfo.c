/*
     load_syminfo.c: test program that loads syminfo.lib.

     Copyright: © 2007 Morten Kjeldgaard <mok@bioxray.dk>
     License: GPL-3+

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

#include "csymlib.h"
#include "ccp4_general.h"
#include "ccp4_program.h"

int main ()
{
  CCP4SPG *spg;

  ccpputenv ("SYMINFO", "../data/syminfo.lib");
  ccp4ProgramName("load_syminfo");
  ccp4_prog_vers (VERSION);

  ccp4_banner();
  spg = ccp4spg_load_by_standard_num (20);
  ccp4spg_print_centric_zones(spg);
  ccp4spg_print_epsilon_zones(spg);
  ccp4spg_print_recip_spgrp(spg);
  ccp4spg_print_recip_ops(spg);

  return 0;
}


/*
  Local variables:
  mode: font-lock
  End:
*/
