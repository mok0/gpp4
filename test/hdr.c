#include <stdio.h>
#include <string.h>
#include "ccp4_program.h"

main ()
{
  char str0[100], str1[100], str2[100]; 
  register int i;
  int n1, n2;

#if defined(GPP4_VERSION_NO)

  char *box[4] = {"o","-","| "," |"};

  strlcpy (str1, box[2], 100);
  strlcat (str1, "\\//\\| gpp4 library version ", 100);
  //strlcat (str1, "/\\\\/| gpp4 library version ", 100);
  //strlcat (str1, "|//|| gpp4 library version ", 100);
  strlcat (str1, GPP4_VERSION_NO, 100);

  strlcpy (str2, box[2], 100);
  strlcat (str2, "CCP4 library compatibility: patch level ", 100);
  strlcat (str2, CCP4_PATCH_LEVEL, 100);
  strlcat (str2, box[3], 100);

#else

  char *box[4] = {"#","#","### ", " ###"};

  strlcpy (str1, box[2], 100);
  strlcat (str1, "CCP4 library version ", 100);
  strlcat (str1, CCP4_VERSION_NO, 100);

  strlcpy (str2, box[2], 100);
  strlcat (str2, "CCP4 library patch level: ", 100);
  strlcat (str2, CCP4_PATCH_LEVEL, 100);
  strlcat (str2, box[3], 100);

#endif

  n1 = strlen((const char *)str1);
  n2 = strlen((const char *)str2);

  int n = n2 - n1 - strlen((const char *)box[3]);

  for (i=0; i<n; i++)
    str1[n1+i] = ' ';
  str1[n1+i] = NULL;
  strlcat (str1, box[3], 100);

  strlcpy(str0, box[0], 100);
  for (i=0; i<n2-1; i++)
    str0[i+1] = box[1][0];
  str0[n2-1] = box[0][0];

  str0[n2] = NULL;

  puts (str0);
  puts (str1);
  puts (str2);
  puts (str0);


}

/*
  Local variables:
  mode: font-lock
  End:
*/
