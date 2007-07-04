/*
     ccp4_program.h: Headers to utilies to set and fetch program information.
     Copyright (C) 2001  CCLRC, Peter Briggs

     This library is free software and is distributed under the terms and
     conditions of the CCP4 licence agreement as `Part 0' (Annex 2)
     software, which is version 2.1 of the GNU Lesser General Public
     Licence (LGPL) with the following additional clause:

        `You may also combine or link a "work that uses the Library" to
        produce a work containing portions of the Library, and distribute
        that work under terms of your choice, provided that you give
        prominent notice with each copy of the work that the specified
        version of the Library is used in it, and that you include or
        provide public access to the complete corresponding
        machine-readable source code for the Library including whatever
        changes were used in the work. (i.e. If you make changes to the
        Library you must distribute those, but you do not need to
        distribute source or object code to those portions of the work
        not covered by this licence.)'

     Note that this clause grants an additional right and does not impose
     any additional restriction, and so does not affect compatibility
     with the GNU General Public Licence (GPL). If you wish to negotiate
     other terms, please contact the maintainer.

     You can redistribute it and/or modify the library under the terms of
     the GNU Lesser General Public License as published by the Free Software
     Foundation; either version 2.1 of the License, or (at your option) any
     later version.

     This library is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the CCP4 licence and/or GNU
     Lesser General Public License along with this library; if not, write
     to the CCP4 Secretary, Daresbury Laboratory, Warrington WA4 4AD, UK.
     The GNU Lesser General Public can also be obtained by writing to the
     Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
     MA 02111-1307 USA
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

static char rcsidhp[] = "$Id: ccp4_program.h,v 1.19.2.1 2004/08/05 11:12:52 pjx Exp $";

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
