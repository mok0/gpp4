/*
     maphdr -- a program to print header information from a map
     file.

     Copyright (C) 2010 Morten Kjeldgaard

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

#include "cmaplib.h"
#include "ccp4_program.h"
#include "ccp4_general.h"

void maphdrout(CMMFile *map)
{
  register int i;

  printf ("File name: %s\n", map->file_name);
  printf ("Data mode: %u\n", map->data_mode);
  printf ("Close mode: %u\n", map->close_mode);
  printf ("Unit cell:");
  for (i=0; i<6; i++)
    printf (" %.3f", map->cell[i]);
  printf ("\n");
  printf ("Map dimensions: %4d %4d %4d\n",
	  map->map_dim[0],map->map_dim[1],map->map_dim[2]);
  printf ("Map origin:     %4d %4d %4d\n",
	  map->origin[0],map->origin[1],map->origin[2]);
  printf ("Map size:       %4d %4d %4d\n",
	  map->cell_grid[0],map->cell_grid[1],map->cell_grid[2]);

  printf ("Axis order:     %4d %4d %4d\n",
	  map->axes_order[0],map->axes_order[1],map->axes_order[2]);


}

int main(int argc, char **argv) 
{

  if (argc != 2) {
    puts("Usage: maphdr <mapfile>");
    exit(1);
  }

  ccp4ProgramName("maphdr");
  ccp4_prog_vers (VERSION);
  ccp4_banner();

  CMMFile *map = ccp4_cmap_open(argv[1], O_RDONLY);
  if (!map) {
    printf ("error reading map file %s\n", argv[1]);
    exit (1);
  }
  maphdrout(map);

  exit(0);
}

/*
  Local variables:
  mode: font-lock
  End:
*/
