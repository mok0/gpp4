/*
     mtzhdr -- a program to print header information from mtz
     file. Inspired by Ralf Grosse-Kunstleves mail to ccp4-dev mailing
     list 20100915.  

     Copyright (C) 2010 Morten Kjeldgaard

     This program is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later
     version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free
     Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
     Boston, MA 02110-1301 USA
*/

#include "cmtzlib.h"
#include <strings.h>
#include <math.h>

void mtzhdrout (MTZ *mtz)
{
  char *s;
  register int i, j, k;

  printf ("Title: %s\n", mtz->title);
  printf ("Space group number: %d\n", mtz->mtzsymm.spcgrp);
  printf ("Space group name: %s\n", mtz->mtzsymm.spcgrpname);
  printf ("Point  group name: %s\n", mtz->mtzsymm.pgname);
  printf ("Lattice type: %c\n", mtz->mtzsymm.symtyp);
  printf ("Space group confidence: %c ", mtz->mtzsymm.spg_confidence);
  if (mtz->mtzsymm.spg_confidence == 'L') {
    printf("  (only Bravais lattice is fixed so far)\n");
  } else if (mtz->mtzsymm.spg_confidence == 'P') {
    printf("  (only pointgroup is fixed so far)\n");
  } else if (mtz->mtzsymm.spg_confidence == 'E') {
    printf("  (one of pair of enantiomorphic spacegroups)\n");
  } else if (mtz->mtzsymm.spg_confidence == 'S') {
    printf("  (spacegroup is known)\n");
  }
  else {
    printf ("  (unknown)\n");
  }

  printf ("Number of crystals: %d\n", mtz->nxtal);
  printf ("Number of reflections: %d\n", mtz->nref);
  printf ("Number of reflections from file: %d\n", mtz->nref_filein);
  printf ("Resolution limits from file: %.2f %.2f\n", mtz->resmax_out, mtz->resmin_out);

  printf ("History:\n");
  s = mtz->hist;
  for (i=0; i< mtz->histlines; i++) {
    putchar(' ');
    for (j=0; j<80; j++) 
      putchar(*s++);
    putchar('\n');
  }
  printf ("Number of columns: %d\n", mtz->ncol_read);
  if (mtz->refs_in_memory) {
    printf ("Reflections are held in memory\n");
  } 
  printf ("Original number of batches: %d\n", mtz->n_orig_bat);

  for (j = 0; j < mtz->nxtal; j++) {
    printf ("Crystal %d:\n", j+1);
    printf ("  Name: %s\n", mtz->xtal[j]->xname);
    printf ("  Project: %s\n", mtz->xtal[j]->pname);
    printf ("  Id: %d\n", mtz->xtal[j]->xtalid);
    printf ("  Unit cell:", mtz->xtal[j]->cell[i]);
    for (i=0; i<6; i++)
      printf (" %.3f", mtz->xtal[j]->cell[i]);
    printf ("\n");
    printf ("  Resolution range: %.2f %.2f\n", 1.0/sqrt(mtz->xtal[j]->resmin), 1.0/sqrt(mtz->xtal[j]->resmax));
    printf ("  Number of datasets: %d\n", mtz->xtal[j]->nset);

    for (i=0; i < mtz->xtal[j]->nset; i++) {
      printf ("  Dataset %d:\n", i+1);
      printf ("    Name: %s\n", mtz->xtal[j]->set[i]->dname);
      printf ("    Id: %d\n", mtz->xtal[j]->set[i]->setid);
      printf ("    Wavelength: %f\n", mtz->xtal[j]->set[i]->wavelength);
      printf ("    Number of columns: %d\n", mtz->xtal[j]->set[i]->ncol);
      printf ("%31s%11s%10s%11s%11s%8s\n", "label", "#valid", "%valid", "min", "max", "type");

      for (k=0; k < mtz->xtal[j]->set[i]->ncol; k++) {

	printf ("%31s", mtz->xtal[j]->set[i]->col[k]->label);
	{
	  float *r = mtz->xtal[j]->set[i]->col[k]->ref;
	  register int h;
	  int ct=0;
	  for (h=0; h < mtz->nref; h++) {
	    if (ccp4_ismnf(mtz, *r++))
	      ct++;
	  }
	  printf (" %10d", mtz->nref-ct); 
	  printf (" %8.2f%%", 100.0*(mtz->nref-ct)/mtz->nref);
	}

	printf (" %10.2f", mtz->xtal[j]->set[i]->col[k]->min);
	printf (" %10.2f", mtz->xtal[j]->set[i]->col[k]->max);
	printf (" %7s:", mtz->xtal[j]->set[i]->col[k]->type);

	switch (mtz->xtal[j]->set[i]->col[k]->type[0]) {
	case 'H':
	  printf (" index h,k,l\n");
	  break;
	case 'F':
	  printf (" amplitude\n");
	  break;
	case 'J':
	  printf (" intensity\n");
	  break;
	case 'G':
	  printf (" amplitude associated with F(+) or F(-)\n");
	  break;
	case 'K': 
	  printf (" intensity associated with I(+) or I(-)\n"); 
	  break;
	case 'D':
	  printf (" anomalous difference\n");
	  break;
	case 'Q':
	  printf (" standard deviation\n");
	  break;
	case 'I':
	  printf (" integer\n");
	  break;
	case 'R': 
	  printf (" real\n"); 
	  break;
	case 'L': 
	  printf (" standard deviation of a column of type G\n"); 
	  break;
	case 'M': 
	  printf (" standard deviation of a column of type K\n"); 
	  break;
	case 'E': 
	  printf (" normalised structure factor\n"); 
	  break;
	case 'P': 
	  printf (" phase angle (degrees)\n"); 
	  break;
	case 'W': 
	  printf (" weight\n"); 
	  break;
	case 'A': 
	  printf (" phase probability coefficients\n"); 
	  break;
	case 'B': 
	  printf (" batch number\n"); 
	  break;
	case 'Y': 
	  printf (" packed partial/reject flag and symmetry number\n"); 
	  break;
	default:
	  printf ("\n");
	  break;
	}
      }
    }
  }
  return;
}


int main(int argc, char **argv) 
{

  if (argc != 2) {
    puts("Usage: mtzhdr <mtzfile>");
    exit(1);
  }

  ccp4ProgramName("mtzhdr");
  ccp4_prog_vers (VERSION);
  ccp4_banner();

  MTZ *mtz = MtzGet (argv[1], 1);
  if (!mtz) {
    printf ("error reading mtz file %s\n", argv[1]);
    exit (1);
  }
  mtzhdrout(mtz);
  //  ccp4_lhprt(mtz, 4);
  exit(0);
}

/*
  Local variables:
  mode: font-lock
  End:
*/
