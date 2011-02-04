/*
     This file is part of the gpp4 library distribution.

     Copyright: 2008 Morten Kjeldgaard

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
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "ccp4_utils.h"

 /*!
   Find the path of the SYMINFO file. We will try to locate the file
   in several places (in increasing order of significance):
      -# $SYMINFO environment variable
      -# ./syminfo.lib
      -# $prefix/share/gpp4/syminfo.lib
      -# $prefix/lib/syminfo.lib
      -# $CCP4/lib/data/syminfo.lib
   where $prefix is defined by the --prefix switch to the configure script.
   The function allocates memory for the pathname that must be free'd
   by the caller in order to avoid a memory leak.
   @return path to syminfo.lib file.
 */
char *gpp4_open_syminfo_file()
{
  struct stat statbuf;
  char *str;
  char *fnam = (char *)ccp4_utils_malloc(512);

  if ((str = getenv("SYMINFO"))) {
    /* SYMINFO was defined, now check to see if file exists */
    strncpy (fnam, str, 512);
    if( stat(fnam,&statbuf) == 0) {
      printf("\n Spacegroup information obtained from library file: \n");
      printf(" Logical Name: SYMINFO   Filename: %s\n\n", fnam);
      return fnam;
    }
  }

  printf("Environment variable SYMINFO not set ... guessing location of symmetry file.\n");

  strncpy (fnam, "./syminfo.lib", 14);
  if( stat(fnam,&statbuf) == 0) {
    printf("\n Spacegroup information obtained from local file: %s\n", fnam);
    return fnam;
  }

  strncpy (fnam, GPP4_PREFIX, 512-24);
  strncat (fnam, "/share/gpp4/syminfo.lib", 24);
  if( stat(fnam,&statbuf) == 0) {
    printf("\n Spacegroup information obtained from system file: %s\n", fnam);
    return fnam;
  }

  strncpy (fnam, GPP4_PREFIX, 512-17);
  strncpy (fnam, "/lib/syminfo.lib", 17);
  if( stat(fnam,&statbuf) == 0) {
    printf("\n Spacegroup information obtained from system file: %s\n", fnam);
    return fnam;
  }

  /* Hmmm. Try one last time in the CCP4 installation */

  if (!(str = getenv("CCP4"))) {
    printf("Environment variable CCP4 not set ... big trouble! \n");
    free(fnam);
    return NULL;
  }

  strncpy(fnam, str, 512);
  strncat(fnam,"/lib/data/syminfo.lib", 22);
  if( stat(fnam,&statbuf) == 0) {
    printf("\n Spacegroup information obtained from CCP4 library: %s\n", fnam);
    return fnam;
  }

  /* We give up... */
  free(fnam);
  return NULL;
}

/*
  Local variables:
  mode: font-lock
  End:
*/
