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

#include "cmtzlib.h"

int main(int argc, char **argv) 
{

  if (argc != 2) {
    puts("Usage: checkarch <mtzfile>");
    exit(1);
  }

  MTZ *fd = MtzGet (argv[1], 1);
  if (!fd) {
    printf ("error reading mtz file %s\n", argv[1]);
    exit (1);
  }
  exit(0);
}


/*
  Local variables:
  mode: font-lock
  End:
*/
