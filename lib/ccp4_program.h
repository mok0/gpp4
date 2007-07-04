/*
     ccp4_program.h: Headers to utilies to set and fetch program information.
     Copyright (C) 2001  CCLRC, Peter Briggs

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


/** @file ccp4_program.h
 *  Utilies to set and fetch program information.
 *  Peter Briggs CCP4 May 2001
 */

/*------------------------------------------------------------------*/

/* Macro definitions */

/*------------------------------------------------------------------*/

#ifndef __CCP4Program__
#define __CCP4Program__


#ifdef  __cplusplus
namespace CCP4 {
extern "C" {
#endif

#define CCP4_VERSION_NO "5.0"
#define CCP4_PATCH_LEVEL "5.0.2"

/* Maximum lengths of strings holding program names and versions */
#define MAXLEN_PROGNAME    80
#define MAXLEN_PROGVERSION 80
#define MAXLEN_RCSDATE     80

/*------------------------------------------------------------------*/

/* Function Prototypes */

/*------------------------------------------------------------------*/

/** Register or query program version.
 * @param progvers Program version string, or NULL to query existing value.
 * @return Program version string.
 */
char *ccp4_prog_vers(char *progvers);

/** Set or return program name.
 * @param progname Program name, or NULL to query existing value.
 * @return Program name
 */
char *ccp4ProgramName(const char *progname);

/** Set or return program RCS date
 * @param rcs_string Date string, or NULL to query existing value.
 * @return Date string
 */
char *ccp4RCSDate(const char *rcs_string);

/** Set or print program time information
 * @param init
 */
void ccp4ProgramTime(int init);

/** Set or return the reference verbosity level
 * Always return the verbosity level - if verboselevel is
 * between 0 and 9 then reset the verbosity level to
 * verboselevel
 * @param level Verbosity level, or -1 to query existing value.
 * @return Verbosity level
 */
int ccp4VerbosityLevel(int level);

/** Check existence of licence agreement
 * @param name Name of licence, e.g. "CCP4".
 * @return 1 for licence exists, else 0.
 */
int ccp4_licence_exists(const char *name);

/** Register or query html output level.
 * @param ihtml_in 0 = turn off html output, 1 = turn on html output, -1 = query existing value
 * @return 0 = no html output, 1 = html output
 */
int html_log_output(int ihtml_in);

/** Register or query summary output level.
 * @param isumm_in 0 = turn off summary output, 1 = turn on summary output, -1 = query existing value
 * @return 0 = no summary output, 1 = summary output
 */
int summary_output(int isumm_in);

#ifdef __cplusplus
} 
} 
#endif

#endif   /* __CCP4Program__ */
