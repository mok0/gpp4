/*
     checkarch.c: check the arch stamp in an mtz file.

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

#include <stdio.h>
#include <string.h>
#include "ccp4_utils.h"
#include "ccp4_sysdep.h"


int whatkind (CCP4File *fd)
{
  char buf[12];

  ccp4_file_raw_seek(fd, 0, SEEK_SET);  
  if (ccp4_file_raw_read(fd, buf, 4UL) != 4) {
    return -1; 
  }

  if (strncmp (buf, "MTZ ", 4) == 0)
    return 1;

  /* now see if file is a map */
  ccp4_file_raw_seek(fd, 208, SEEK_SET);  
  if (ccp4_file_raw_read(fd, buf, 4UL) != 4) {
    return -1;
  }

  if (strncmp (buf, "MAP ", 4) == 0)
    return 2;

  /* else return unknown */
  return 0;
}

int process_file (char *fnam, int verbose)
{
  int stamp_loc = 0;
  union {
    unsigned int i;
    unsigned char mtstring[4];
  } res;

  CCP4File *fd = ccp4_file_open(fnam, O_RDONLY);
  printf ("%s; ", fnam);

  /* First figure out what kind of file this is */
  switch (whatkind(fd)) {
  case -1:
    printf ("read error\n");
    return 1;
  case 1:
    stamp_loc = 8;
    printf ("MTZ format; ");
    break;
  case 2:
    stamp_loc = 212;
    printf ("MAP format; ");
    break;
  case 0:
    printf ("unknown file\n");
    return 1;
  }

  /* Now try to read the arch flag */

  ccp4_file_raw_seek(fd, stamp_loc, SEEK_SET);

  if (ccp4_file_raw_read(fd, (char *) &res, 4UL) != 4) {
    printf ("error\n");
    return 1; 
  }

  if (res.i == 0) {
    printf ("no arch stamp found\n");
    return 1;
  }

  int fconvert = res.mtstring[0]>>4;
  int iconvert = res.mtstring[1]>>4;

  if (iconvert == DFNTI_MBO)
    printf ("Motorola byte order; ");
  else if (iconvert == DFNTI_IBO)
    printf ("Intel byte order; ");

  switch (fconvert) {
  case DFNTF_BEIEEE:
    printf ("big endian ieee; ");
    break;
  case DFNTF_LEIEEE:
    printf ("little endian ieee; ");
    break;
  case DFNTF_VAX:
    printf ("vax floats; ");
    break;
  case DFNTF_CONVEXNATIVE:
    printf ("convex native floats; ");
    break;
 }

  if (iconvert == NATIVEIT && fconvert == NATIVEFT) 
    printf ("native to this machine\n");
  else
    printf ("not native to this machine\n");

  return 0;
}


int main(int argc, char **argv) 
{
  int status;

  if (argc != 2) {
    puts("Usage: checkarch <mtzfile>");
    exit(1);
  }

  status = process_file (argv[1], 1);
  exit(status);
}


/*
  Local variables:
  mode: font-lock
  End:
*/
