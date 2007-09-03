/*
     ccp4_parser.h: Headers for functions to read in and "parse" CCP4
     keyworded input.  
     Copyright (C) 2001 CCLRC, Peter Briggs

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

/** @page cparser_page CParser library
 
* @section cparser_file_list File list

 - ccp4_parser.h - contains details of the C/C++ API

* @section cparser_overview Overview
 
These functions do CCP4-style parsing, as used for processing keywords
of CCP4 programs, MTZ header records, etc.

* @section cparser_usage Usage

The following code snippets illustrate how the functions might be used
to read from stdin:

* @code
int           ntok=0;
char          line[201],*key;
CCP4PARSERTOKEN * token=NULL;
CCP4PARSERARRAY * parser;

  parser = (CCP4PARSERARRAY *) ccp4_parse_start(20);
  key   = parser->keyword;
  token = parser->token;

  RC   = 0;
  while (!RC) {

    line[0] = '\0';
    ntok = ccp4_parser(line,200,parser,1);

    if (ntok < 1) {

      RC = 111;

    } else {      

      if (ccp4_keymatch("MINDIST",key))  {
	if (ntok != 2) {
	  ccperror ( 1,"MINDIST requires a single numerical argument" );
	  RC = -100;
	} else {
	  minDist = token[1].value;
        }
      }	else  {
	printf ( "Unrecognised keyword \"%s\"\n",token[0].fullstring );
	RC = -118;
      }
    }
  }

  ccp4_parse_end ( parser );
  * @endcode

  * @section cparser_examples Examples

See the distributed programs <a href="../ncont.html">NCONT</a> and
<a href="../pdbcur.html">PDBCUR</a>.

*/

/** @file ccp4_parser.h
 *
 *  @brief Functions to read in and "parse" CCP4-style keyworded input
 *
 *  @author Peter Briggs
 *  @date April 2001
 */


/* Macro definitions */


#ifndef __CCP4_Parser__
#define __CCP4_Parser__


/* note order: these must be outside CCP4 namespace */
#include <stdio.h>
#include"ccp4_utils.h"
#include"ccp4_spg.h"

/* Macro to make C functions callable from C++ */
#ifdef  __cplusplus
namespace CCP4 {
extern "C" {
typedef CSym::ccp4_symop ccp4_symop;
#endif


/* Parser String Sizes */

#define CCP4_PARSER_MAXLINELENGTH     200  /*!<  Maximum length of line to be parsed */
#define CCP4_PARSER_MAXFILENAMELENGTH 200  /*!<  Maximum length of file name to be parsed */


/* Structures and typedefs */


/*! @struct CCP4PARSERTOKEN 
   @brief CCP4 Parser token
   Construct to hold the information about a single token 
*/

typedef struct {
  char   *fullstring;   /*!<  Full string containing all of token */
  char   word[5];       /*!<  First four characters of token */
  double value;         /*!<  Equivalent numerical value */
  int    isstring;      /*!<  Flag: true if token is character string */
  int    strlength;     /*!<  Number of characters in whole token (strings only) */
  int    isnumber;      /*!<  Flag: true if token is number */
  int    intdigits;     /*!<  Number of 'digits' preceeding the decimal point
			   (numbers only) */
  int    frcdigits;     /*!<  Number of 'digits' after the decimal point (numbers
			   only) */
  int    isquoted;      /*!<  Flag: true if token is contained in quotes */
  int    isnull;        /*!<  Flag: true if token is null field */
  int    ibeg;          /*!<  Begin character positions of token in input line */
  int    iend;          /*!<  End character positions of token in input line */
} CCP4PARSERTOKEN;      /*!<  Type name for the CCP4 Parser token data structure  */ 

/*! @struct CCP4PARSERARRAY
    @brief CCP4 Parser array
    Construct to hold the information about a parsed line 
*/

typedef struct {
  /* "Public" members */
  char   keyword[5];      /*!<  Keyword (=token[1].token, uppercased) */
  int    ntokens;         /*!<  Number of tokens */
  CCP4PARSERTOKEN *token; /*!<  Array of tokens */
  /* "Private" members */
  FILE   *fp;             /*!<  Pointer to an external command file */
  int    maxtokens;       /*!<  Maximum number of tokens allowed */
  char   *delim;          /*!<  List of delimiter characters */
  char   *nulldelim;      /*!<  List of null delimiter characters */
  char   *comment;        /*!<  List of comment characters */
  double max_exponent;    /*!<  Largest allowed exponent for numerical tokens */
  double min_exponent;    /*!<  Smallest allowed exponent for numerical tokens */
} CCP4PARSERARRAY;        /*!<  Type name for the CCP4 Parser array data structure  */ 


/* Function Prototypes */


/* Core cparser functions */

CCP4PARSERARRAY* ccp4_parse_start(const int maxtokens);
int ccp4_parse_end(CCP4PARSERARRAY *parsePtr);
int ccp4_parse_init_token(const CCP4PARSERARRAY *parsePtr, const int itok);
int ccp4_parse_delimiters(CCP4PARSERARRAY *parsePtr, const char *delim,
				  const char *nulldelim);
int ccp4_parse_comments(CCP4PARSERARRAY *parsePtr, const char *comment_chars);
int ccp4_parse_maxmin(CCP4PARSERARRAY *parsePtr, const double max_exponent,
			      const double min_exponent);
int ccp4_parse_reset(CCP4PARSERARRAY *parsePtr);
int ccp4_parse(const char *line, CCP4PARSERARRAY *parser);
int ccp4_parser(char *line, const int n, CCP4PARSERARRAY *parser,
			const int print);

/* External utility functions */

int ccp4_keymatch(const char *keyin1, const char *keyin2);

/* Internal utility functions */

char *strtoupper (char *str1, const char *str2);
char *strtolower (char *str1, const char *str2);
int strmatch (const char *str1, const char *str2);
int charmatch(const char character, const char *charlist);
int doublefromstr(const char *str, const double max_exp, const double min_exp,
			  double *valuePtr, double *intvaluePtr, int *intdigitsPtr,
			  double *frcvaluePtr, int *frcdigitsPtr,
			  double *expvaluePtr, int *expdigitsPtr);

ccp4_symop symop_to_rotandtrn(const char *symchs_begin, const char *symchs_end);
const char * symop_to_mat4(const char *symchs_begin, const char *symchs_end, float *rot);
static int symop_to_mat4_err(const char *symop);
ccp4_symop mat4_to_rotandtrn(const float rsm[4][4]);
char *rotandtrn_to_symop(char *symchs_begin, char *symchs_end, const ccp4_symop symop);
void rotandtrn_to_mat4(float rsm[4][4], const ccp4_symop symop);
char *mat4_to_symop(char *symchs_begin, char *symchs_end, const float rsm[4][4]);
char *mat4_to_recip_symop(char *symchs_begin, char *symchs_end, const float rsm[4][4]);

#ifdef __cplusplus
}
}
#endif

#endif  /* __CCP4_Parser__ */

/*
  Local variables:
  mode: font-lock
  End:
*/
