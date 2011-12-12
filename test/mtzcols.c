/*
     mtzcols -- a program to print the full mtz paths of columns in
     an MTZ file.

     Copyright: © 2010 Morten Kjeldgaard <mok@bioxray.dk>
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
  register int i, j, k;

  for (j = 0; j < mtz->nxtal; j++) {

    /* 
       simply print a list of project/crystal/datase lines
    */

    for (i=0; i < mtz->xtal[j]->nset; i++) {

      for (k=0; k < mtz->xtal[j]->set[i]->ncol; k++) {
	printf ("%s/", mtz->xtal[j]->pname);
	printf ("%s/", mtz->xtal[j]->set[i]->dname);
	printf ("%s\n", mtz->xtal[j]->set[i]->col[k]->label);
      }
    }
  }
  return;
}


int main(int argc, char **argv) 
{

  if (argc != 2) {
    puts("Usage: mtzcols <mtzfile>");
    exit(1);
  }

  ccp4ProgramName("mtzcols");
  ccp4_prog_vers (VERSION);
  ccp4_banner();

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
