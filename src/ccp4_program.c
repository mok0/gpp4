/*
     ccp4_program.c: Utilies to set and fetch program information.
     Copyright (C) 2001  CCLRC, Peter Briggs
     Copyright (C) 2007 Morten Kjeldgaard

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

/*! @file ccp4_program.c
    @brief Utilies to set and fetch program information.
    @author Peter Briggs
    @date May 2001
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ccp4_program.h"
#include "ccp4_parser.h"
#include "ccp4_utils.h"
#include "ccp4_general.h"

/*! Register or query program version.
    @param progvers Program version string, or NULL to query existing value.
    @return Program version string.
 */
char *ccp4_prog_vers(const char *progvers) 
{
  static char programversion[MAXLEN_PROGVERSION]="";

  if (progvers) {
    strncpy(programversion, progvers, MAXLEN_PROGVERSION);
    programversion[MAXLEN_PROGVERSION-1] = '\0';
  }
  return programversion;
}

static char ccp4version[MAXLEN_PROGVERSION];

/*! Query program version.
    @return Program version string.
*/
char *ccp4_vers_no(void)
{
  static int init=0;

  if (!init) {
    bzero(ccp4version,MAXLEN_PROGVERSION);
    strcpy(ccp4version,CCP4_VERSION_NO);
    init=1;
  }
  return ccp4version;
}


/*! Set or return program name.
  @param progname Program name, or NULL to query existing value.
  @return Program name

  Always returns a pointer to the program name If progname is not
  NULL then set the program name to progname.

  @note Default program name will be returned as "CCP4", until reset
  by the calling subprogram.
 */
char *ccp4ProgramName(const char *progname)
{
  static char programname[MAXLEN_PROGNAME]="CCP4";
  int         i;

  if (progname) {
    i = 0;
    while (progname[i] != '\0' && i < MAXLEN_PROGNAME) {
      programname[i] = progname[i];
      ++i;
    }
    if (i == MAXLEN_PROGNAME) {
      programname[MAXLEN_PROGNAME-1] = '\0';
    } else {
      programname[i] = '\0';
    }
  }
  return programname;
}


/*! Print program info for -i option.
 */
void ccp4_prog_info(void)
{
  printf("\\//\\| gpp4 library version version %s\n", GPP4_VERSION_NO);
  printf("Compatible with CCP4 library version %s\n", ccp4_vers_no());
  printf("Program:             %s", ccp4ProgramName(NULL));
  if (ccp4_prog_vers(NULL) && strlen(ccp4_prog_vers(NULL)))
    printf("; version %s", ccp4_prog_vers(NULL));
  printf("\n");
}


/*! Set or return program RCS date
  @param rcs_string Date string, or NULL to query existing value.
  @return Date string

  If the input string is not a NULL pointer then it is assumed to be
  an RCS string This is processed to extract a date string in the form
  "DD/MM/YY" (day/month/year), which is then stored.

  ccp4RCSDate always returns the currently stored date string.  

  @note This routine does not make sense in gpp4, since RCS idents are
  not expanede in the SCM system we are using.
*/
char *ccp4RCSDate(const char *rcs_string)
{
  static char RCSDate[MAXLEN_RCSDATE]="";
  char        tmpstr1[8],tmpstr2[3];

  /* Deconstruct the RCS string passed to this
     function */
  if (rcs_string) {
    /* Extract useful data from RCS string for examination */
    strncpy(tmpstr1,rcs_string,7);
    tmpstr1[7] = '\0';
    strncpy(tmpstr2,rcs_string,2);
    tmpstr2[2] = '\0';
    if (strncmp(tmpstr1,"$Date: ",7) == 0) {
      /* Raw form of RCS string (not exported) i.e.:
	 "$Date: 2008/06/18 17:34:27 $"
      */
      /* Build the date string in the form DD/MM/YY */
      strncpy(RCSDate,rcs_string+15,2);
      strncat(RCSDate,"/",1);
      strncat(RCSDate,rcs_string+12,2);
      strncat(RCSDate,"/",1);
      strncat(RCSDate,rcs_string+9,2);
    } else if (strlen(rcs_string) > 10 &&
	       (strncmp(tmpstr2,"19",2) == 0 || strncmp(tmpstr2,"20",2)) ) {
      /* RCS string after export i.e.:
	 "2003/05/14 11:45:13 ..." */
      /* Build the date string in the form DD/MM/YY */
      strncpy(RCSDate,rcs_string+8,2);
      strncat(RCSDate,"/",1);
      strncat(RCSDate,rcs_string+5,2);
      strncat(RCSDate,"/",1);
      strncat(RCSDate,rcs_string+2,2);
    } else {
      /* Fallback */
      strncpy(RCSDate,"",1);
    }
  }
  /* Always return the stored date */
  return RCSDate;
}

/*! Set or print program time information 
   @param init 
   The timer is started when this routine is called with a non-zero
   argument. When the routine is called with a 0 argument, timing
   information is printed to stdout. @note Only one timer can be
   handled.
 */
void ccp4ProgramTime(int init)
{
  static int elaps0=0;
  static float tarray0[2];
  int elaps;
  float tarray[2];

  if (init || !elaps0 ) {
    elaps0 = time(NULL);
    ccp4_utils_etime(tarray0);
  } else {
    elaps = time(NULL) - elaps0;
    ccp4_utils_etime(tarray);

    printf("Times: User: %9.1fs System: %6.1fs Elapsed: %5d:%2.2d  \n",
	   tarray[0]-tarray0[0],tarray[1]-tarray0[1],elaps/60,elaps%60);
  }

}

/*! Set or return the reference verbosity level
   @param level Verbosity level, or -1 to query existing value.
   @return Verbosity level
   Always return the verbosity level - if verboselevel is between 0
   and 9 then reset the verbosity level to verboselevel
*/
int ccp4VerbosityLevel(int level)
{
  /* The default level is 1 */
  static int verbositylevel=1;

  if (level > -1 && level < 10)
    verbositylevel = level;
  return verbositylevel;
}

/*!
   Set or invoke a user-defined callback function.
   Internal function: applications should use the API functions
   ccp4SetCallback and ccp4InvokeCallback
 */
int ccp4Callback(CCP4INTFUNCPTR mycallback, char *mode, int ierr, 
		 const char *message)
{
  static CCP4INTFUNCPTR callback=ccp4NullCallback;

  if (strncmp(mode,"set",3) == 0) {
    /* Set callback
       Store the pointer to the callback function */
    callback=mycallback;
    return 1;
  } else if (strncmp(mode,"invoke",3) == 0) {
    /* Invoke callback
       Execute the callback function */
    return callback(ierr,message);
  }
  /* Unrecognised mode */
  return 0;
}

/*!
   Store a pointer to a user-defined callback function of
   the form "int func(int, char *)"
   This is a wrapper to ccp4Callback in "set" mode.
 */
int ccp4SetCallback(CCP4INTFUNCPTR mycallback)
{
  return ccp4Callback(mycallback,"set",-1,"No message");
}

/*!
   Execute the user-defined callback function (previously
   set up using ccp4SetCallback) with the supplied
   arguments.
   This is a wrapper to ccp4Callback in "invoke" mode.
 */
int ccp4InvokeCallback(int ierr, const char *message)
{
  return ccp4Callback(ccp4NullCallback,"invoke",ierr,message);
}

/*! 
  Default null callback function
   Internal function: this is the default callback function
   used by ccp4Callback if no user-defined function has been
   specified.
 */
int ccp4NullCallback(int level, const char *message)
{
  /* This is the default callback function which takes no
     action */
  return 1;
}

/*! Check existence of licence agreement
    @param name Name of licence, e.g. "CCP4".
    @return always return 1.
    This is a dummy routine in gpp4.
*/

int ccp4_licence_exists(const char *name)
{
  return 1;
}

/*! Register or query html output level.
    @param ihtml_in 0 = turn off html output, 1 = turn on html output, 
    -1 = query existing value
    @return 0 = no html output, 1 = html output
    html_log_output and summary_output currently only used by ccperror to
    tidy up Fortran program output. Defaults are 0 for C programs.
 */
int html_log_output(int ihtml_in) {
  static int ihtml=0;

  if (ihtml_in >= 0)
    ihtml = ihtml_in;
  return ihtml;
}

/*! Register or query summary output level.
    @param isumm_in 0 = turn off summary output, 1 = turn on summary
    output, -1 = query existing value
    @return 0 = no summary output, 1 = summary output
*/

int summary_output(int isumm_in) {
  static int isumm=0;

  if (isumm_in >= 0)
    isumm = isumm_in;
  return isumm;
}


/*
  Local variables:
  mode: font-lock
  End:
*/
