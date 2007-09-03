/*
     ccp4_program.h: Headers to utilies to set and fetch program information.
     Copyright (C) 2001  CCLRC, Peter Briggs
     Copyright (C) 2007 Morten Kjeldgaard

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

/*! @file ccp4_program.h
    @brief Header file for utilies to set and fetch program information
    @author Peter Briggs, CCP4
    @date May 2001
 */


/* Macro definitions */

#ifndef __CCP4Program__
#define __CCP4Program__


#ifdef  __cplusplus
namespace CCP4 {
extern "C" {
#endif

/*! Version of CCP4 that gpp4 is derived from */
#define CCP4_VERSION_NO "5.0"

/*! Patch level of CCP4 that gpp4 is derived from */
#define CCP4_PATCH_LEVEL "5.0.2" 

/*! GPP4 version is defined by autoconf */
#define GPP4_VERSION_NO VERSION   

/* Maximum lengths of strings holding program names and versions */
#define MAXLEN_PROGNAME    80  /*!<  Maximum length of program name */
#define MAXLEN_PROGVERSION 80  /*!<  Maximum length of program version string */
#define MAXLEN_RCSDATE     80  /*!<  Maximum length of date string */


/* Function Prototypes */

char *ccp4_prog_vers(char *progvers);
char *ccp4ProgramName(const char *progname);
char *ccp4RCSDate(const char *rcs_string);
void ccp4ProgramTime(int init);
int ccp4VerbosityLevel(int level);
int ccp4_licence_exists(const char *name);
int html_log_output(int ihtml_in);
int summary_output(int isumm_in);

#ifdef __cplusplus
} 
} 
#endif

#endif   /* __CCP4Program__ */

/*
  Local variables:
  mode: font-lock
  End:
*/
