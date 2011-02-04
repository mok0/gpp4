/*
     ccp4_general.h: header for general library functions and utilities.
     Copyright (C) 2001  CCLRC, Peter Briggs et al

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

/**  @file ccp4_general.h
     @brief Header file for CCP4 library clones
*/


/* Macro definitions */


#ifndef __CCPGeneral__
#define __CCPGeneral__


/* note order: this must be outside CCP4 namespace */
#include "ccp4_parser.h"

#ifdef  __cplusplus
namespace CCP4 {
extern "C" {
#endif

  /** Maximum number of characters in lines read from
     environ.def and default.def files (@ref ccp4fyp) */
#define CCP4_MAXLINE  200 

  /** Maximum number of tokens in lines read from environ.def
     and default.def files (@ref ccp4fyp) */
#define CCP4_MAXTOKS  3   

  /** Maximum number of logical names that can be read and
      stored from environ.def (@ref ccp4fyp) */
#define CCP4_MAXNAMES 150 

  /** To guarantee that process id is always 5 characters,
	 take the id number modulo 100,000 */
#define CCP4_MODULO   100000

/* stuff for error reporting */
#define CGEN_ERRNO(n) (CCP4_ERR_GEN | (n))

/* error defs */
#define  CGENERR_Ok                  0
#define  CGENERR_AllocFail           1
#define  CGENERR_CantSetEnvironment  2
#define  CGENERR_MaxNamesExceeded    3
#define  CGENERR_EOptionUseError     4
#define  CGENERR_DOptionUseError     5
#define  CGENERR_LogicalNameUseError 6
#define  CGENERR_CantOpenEnvFile     7
#define  CGENERR_CantOpenDefFile     8
#define  CGENERR_ParseEnvFail        9
#define  CGENERR_ParseDefFail        10
#define  CGENERR_CantFindInFile      11
#define  CGENERR_EnvPathFail         12
#define  CGENERR_DefPathFail         13
#define  CGENERR_CantGetClibd        14
#define  CGENERR_CantGetCcp4Scr      15

/*------------------------------------------------------------------*/

/* Structures and typedefs */

/*------------------------------------------------------------------*/

/* <None declared> */

/*------------------------------------------------------------------*/

/* Function Prototypes */

/*------------------------------------------------------------------*/

void ccp4f_mem_tidy(void);

int ccperror(int ierr, const char *message);

int ccperror_noexit(int ierr, const char *message);

int ccp4printf(int level, char *format, ...);

int ccp4fyp(int argc, char **argv);

int ccp4fyp_cleanup(int ienv, char **envname, char **envtype, char **envext,
		    char *logical_name, char *file_name, char *file_type,
		    char *file_ext, char *env_file, char *def_file,
		    char *dir, CCP4PARSERARRAY *parser);

int ccp4setenv(char *logical_name, char* value, char **envname,
	       char **envtype, char **envext, int *ienv, int no_overwrt);

int ccp4setenv_cleanup(char *file_ext, char *file_root, char *file_path,
		       char *file_name);

int ccpexists(char *filename);

int ccpputenv(char *logical_name, char *file_name);

void ccp4_banner(void);

#ifdef __cplusplus
}
}
#endif

#endif   /* __CCPGeneral__ */

/*
  Local variables:
  mode: font-lock
  End:
*/
