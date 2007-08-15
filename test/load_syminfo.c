/* @(#)load_syminfo.c
 */

#include "csymlib.h"

main ()
{
  CCP4SPG *spg;

  ccpputenv ("SYMINFO", "../data/syminfo.lib");
  ccp4ProgramName("load_syminfo");
  ccp4_prog_vers ("0.1");

  ccp4_banner();
  spg = ccp4spg_load_by_standard_num (20);
  ccp4spg_print_centric_zones(spg);
  ccp4spg_print_epsilon_zones(spg);
  ccp4spg_print_recip_spgrp(spg);
  ccp4spg_print_recip_ops(spg);
}


