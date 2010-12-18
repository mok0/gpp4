/*
     check_mtz_stamp.c: check the arch stamp in an mtz file.
     Copyright (C) 2010 Morten Kjeldgaard

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

#include <stdio.h>
#include "ccp4_utils.h"

int main(int argc, char **argv) 
{
  union {
    unsigned int i;
    unsigned char mtstring[4];
  } res;


  if (argc != 2) {
    puts("Usage: checkarch <mtzfile>");
    exit(1);
  }

  CCP4File *fd = ccp4_file_open(argv[1], O_RDONLY);

  /* Now try to read the arch flag */

  ccp4_file_raw_seek(fd, 2*4, SEEK_SET);


  if (ccp4_file_raw_read(fd, (char *) &res, 4UL) != 4) {
    printf ("error\n");
    exit(1); 
  }

  if (res.i == 0) {
    printf ("no arch stamp found\n");
    exit (1);
  }
  exit(0);
}


/*
  Local variables:
  mode: font-lock
  End:
*/
