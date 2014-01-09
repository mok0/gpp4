/*
     mtzhdr -- a program to print header information from mtz
     file in csv format.

     Copyright: © 2014 Morten Kjeldgaard <mok@bioxray.dk>
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

#include "cmtzlib.h"
#include "ccp4_program.h"
#include "ccp4_general.h"
#include <strings.h>
#include <math.h>

void mtzhdrout (MTZ *mtz)
{
  char *s;
  register int i, j;

  printf ("spcgrp,");
  printf ("spcgrpname,");
  printf ("pgname,");
  printf ("symtyp,");

  printf ("nxtal,");
  printf ("nref,");
  printf ("ncol,");
  printf ("a,b,c,alpha,beta,gamma,");
  printf ("resmin,resmax,");
  printf ("nset,");
  printf ("wavelength\n");

  /* --- */

  printf ("%d,", mtz->mtzsymm.spcgrp);
  printf ("%s,", mtz->mtzsymm.spcgrpname);
  printf ("%s,", mtz->mtzsymm.pgname);
  printf ("%c,", mtz->mtzsymm.symtyp);
  printf ("%d,", mtz->nxtal);
  printf ("%d,", mtz->nref);
  printf ("%d,", mtz->ncol_read);
  j = 0;
  for (i=0; i<5; i++) 
    printf ("%.3f,", mtz->xtal[j]->cell[i]);
  printf ("%.2f,%.2f,", 1.0/sqrt(mtz->xtal[j]->resmin), 1.0/sqrt(mtz->xtal[j]->resmax));
  printf ("%d,", mtz->xtal[j]->nset);
  printf ("%f\n", mtz->xtal[j]->set[0]->wavelength);
}


int main(int argc, char **argv) 
{

  if (argc != 2) {
    puts("Usage: mtzhdr <mtzfile>");
    exit(1);
  }

  MTZ *mtz = MtzGet (argv[1], 1);
  if (!mtz) {
    printf ("error reading mtz file %s\n", argv[1]);
    exit (1);
  }
  mtzhdrout(mtz);
  exit(0);
}

/*
  Local variables:
  mode: font-lock
  End:
*/
