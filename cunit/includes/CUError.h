/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001  Anil Kumar
 *  Copyright (C) 2004  Anil Kumar, Jerry St.Clair
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *  Contains CUnit error codes which can be used externally.
 *
 *  Created By     : Anil Kumar on ...(in month of Aug 2001)
 *  Last Modified  : 09/Aug/2001
 *  Comment        : -------
 *  EMail          : aksaharan@yahoo.com
 *
 *  Modified       : 02/Oct/2001
 *  Comment        : Added proper Eror Codes
 *  EMail          : aksaharan@yahoo.com
 *
 *  Modified       : 13-Oct-2001
 *  Comment        : Added Error Codes for Duplicate TestGroup and Test
 *  EMail          : aksaharan@yahoo.com
 *
 *  Modified       : 3-Aug-2004 (JDS)
 *  Comment        : Converted error code macros to an enum, doxygen comments
 *                   moved error handing code here, changed file name from Errno.h,
 *                   added error codes for file open errors, added error action selection
 *  EMail          : jds2@users.sourceforge.net
 *
 *  Modified       : 5-Sep-2004 (JDS)
 *  Comment        : Added internal test interface.
 *  EMail          : jds2@users.sourceforge.net
 */

#ifndef _CUNIT_CUERROR_H
#define _CUNIT_CUERROR_H

#include <errno.h>

/*------------------------------------------------------------------------*/
typedef enum {
  /* basic errors */
  CUE_SUCCESS           = 0,  
  CUE_NOMEMORY          = 1,  
  /* Test Registry Level Errors */
  CUE_NOREGISTRY        = 10,  
  CUE_REGISTRY_EXISTS   = 11,  
  /* Test Suite Level Errors */
  CUE_NOSUITE           = 20,  
  CUE_NO_SUITENAME      = 21,  
  CUE_SINIT_FAILED      = 22,  
  CUE_SCLEAN_FAILED     = 23,  
  CUE_DUP_SUITE         = 24,  
  /* Test Case Level Errors */
  CUE_NOTEST            = 30,  
  CUE_NO_TESTNAME       = 31,  
  CUE_DUP_TEST          = 32,  
  CUE_TEST_NOT_IN_SUITE = 33,  
  /* File handling errors */
  CUE_FOPEN_FAILED      = 40,  
  CUE_FCLOSE_FAILED     = 41,  
  CUE_BAD_FILENAME      = 42,  
  CUE_WRITE_ERROR       = 43   
} CU_ErrorCode;

/*------------------------------------------------------------------------*/
typedef enum CU_ErrorAction {
  CUEA_IGNORE,    
  CUEA_FAIL,      
  CUEA_ABORT      
} CU_ErrorAction;

/* Error handling & reporting functions. */

#ifdef __cplusplus
extern "C" {
#endif

CU_ErrorCode   CU_get_error(void);
const char*    CU_get_error_msg(void);
void           CU_set_error_action(CU_ErrorAction action);
CU_ErrorAction CU_get_error_action(void);

#ifdef CUNIT_BUILD_TESTS
void test_cunit_CUError(void);
#endif

/* Internal function - users should not generally call this function */
void  CU_set_error(CU_ErrorCode error);

#ifdef __cplusplus
}
#endif

#ifdef USE_DEPRECATED_CUNIT_NAMES

#define get_error() CU_get_error_msg()
#endif  /* USE_DEPRECATED_CUNIT_NAMES */

#endif  /*  _CUNIT_CUERROR_H  */
