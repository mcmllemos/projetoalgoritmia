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
 *  Contains ASSERT Macro definitions
 *
 *  Created By      : Anil Kumar on ...(in month of Aug 2001)
 *  Last Modified   : 09/Aug/2001
 *  Comment         : ASSERT definition
 *  EMail           : aksaharan@yahoo.com
 *
 *  Last Modified   : 12/Mar/2003
 *  Comment         : New Assert definitions
 *  EMail           : aksaharan@yahoo.com
 *
 *  Last Modified   : 27/Jul/2003
 *  Comment         : Modified ASSERT_XXX Macro definitions
 *  EMail           : aksaharan@yahoo.com
 *
 *  Last Modified   : 15-Jul-2004 (JDS)
 *  Comment         : New interface, changed action on assert failure to
 *                    not return, provided _FATAL versions of assertions
 *                    to return from test function on failure.
 *  EMail           : jds2@users.sourceforge.net
 *
 *  Last Modified   : 1-Sep-2004 (JDS)
 *  Comment         : Modified assertions for setjmp/longjmp mechanism of aborting
 *                    test runs, added CU_FAIL and CU_PASS macros.
 *  EMail           : jds2@users.sourceforge.net
 */

#ifndef _CUNIT_CUNIT_H
#define _CUNIT_CUNIT_H

#include <string.h>
#include <math.h>

#include "CUError.h"
#include "TestDB.h"   /* not needed here - included for user convenience */

#ifdef __cplusplus
extern "C" {
#endif

/*  Max string lengths for names (includes terminating NULL. */
#define MAX_TEST_NAME_LENGTH    256

#define MAX_SUITE_NAME_LENGTH   256

/* Global type Definitions to be used for boolean operators. */
#ifndef BOOL

  #define BOOL int
#endif

#ifndef TRUE

  #define TRUE 1
#endif

#ifndef FALSE

  #define FALSE 0
#endif

#ifndef CU_UNREFERENCED_PARAMETER

  #define CU_UNREFERENCED_PARAMETER(x) (void)x
#endif

//#include "TestRun.h"  /* not needed here - include (after BOOL define) for user convenience */

#define CU_PASS(msg) \
  { CU_assertImplementation(TRUE, __LINE__, ("CU_PASS(" #msg ")"), __FILE__, "", FALSE); }

#define CU_ASSERT(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", FALSE); }

#define CU_ASSERT_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", TRUE); }

#define CU_TEST(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", FALSE); }

#define CU_TEST_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, #value, __FILE__, "", TRUE); }

#define CU_FAIL(msg) \
  { CU_assertImplementation(FALSE, __LINE__, ("CU_FAIL(" #msg ")"), __FILE__, "", FALSE); }

#define CU_FAIL_FATAL(msg) \
  { CU_assertImplementation(FALSE, __LINE__, ("CU_FAIL_FATAL(" #msg ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_TRUE(value) \
  { CU_assertImplementation((value), __LINE__, ("CU_ASSERT_TRUE(" #value ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_TRUE_FATAL(value) \
  { CU_assertImplementation((value), __LINE__, ("CU_ASSERT_TRUE_FATAL(" #value ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_FALSE(value) \
  { CU_assertImplementation(!(value), __LINE__, ("CU_ASSERT_FALSE(" #value ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_FALSE_FATAL(value) \
  { CU_assertImplementation(!(value), __LINE__, ("CU_ASSERT_FALSE_FATAL(" #value ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_EQUAL(actual, expected) \
  { CU_assertImplementation(((actual) == (expected)), __LINE__, ("CU_ASSERT_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((actual) == (expected)), __LINE__, ("CU_ASSERT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation(((actual) != (expected)), __LINE__, ("CU_ASSERT_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((actual) != (expected)), __LINE__, ("CU_ASSERT_NOT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_PTR_EQUAL(actual, expected) \
  { CU_assertImplementation(((void*)(actual) == (void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_PTR_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((void*)(actual) == (void*)(expected)), __LINE__, ("CU_ASSERT_PTR_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_PTR_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation(((void*)(actual) != (void*)(expected)), __LINE__, ("CU_ASSERT_PTR_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_PTR_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(((void*)(actual) != (void*)(expected)), __LINE__, ("CU_ASSERT_PTR_NOT_EQUAL_FATAL(" #actual "," #expected ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_PTR_NULL(value) \
  { CU_assertImplementation((NULL == (void*)(value)), __LINE__, ("CU_ASSERT_PTR_NULL(" #value")"), __FILE__, "", FALSE); }

#define CU_ASSERT_PTR_NULL_FATAL(value) \
  { CU_assertImplementation((NULL == (void*)(value)), __LINE__, ("CU_ASSERT_PTR_NULL_FATAL(" #value")"), __FILE__, "", TRUE); }

#define CU_ASSERT_PTR_NOT_NULL(value) \
  { CU_assertImplementation((NULL != (void*)(value)), __LINE__, ("CU_ASSERT_PTR_NOT_NULL(" #value")"), __FILE__, "", FALSE); }

#define CU_ASSERT_PTR_NOT_NULL_FATAL(value) \
  { CU_assertImplementation((NULL != (void*)(value)), __LINE__, ("CU_ASSERT_PTR_NOT_NULL_FATAL(" #value")"), __FILE__, "", TRUE); }

#define CU_ASSERT_STRING_EQUAL(actual, expected) \
  { CU_assertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_EQUAL(" #actual ","  #expected ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_STRING_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_EQUAL_FATAL(" #actual ","  #expected ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_STRING_NOT_EQUAL(actual, expected) \
  { CU_assertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_NOT_EQUAL(" #actual ","  #expected ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_STRING_NOT_EQUAL_FATAL(actual, expected) \
  { CU_assertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __LINE__, ("CU_ASSERT_STRING_NOT_EQUAL_FATAL(" #actual ","  #expected ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_NSTRING_EQUAL(actual, expected, count) \
  { CU_assertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_NSTRING_EQUAL_FATAL(actual, expected, count) \
  { CU_assertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_EQUAL_FATAL(" #actual ","  #expected "," #count ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_NSTRING_NOT_EQUAL(actual, expected, count) \
  { CU_assertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_NOT_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(actual, expected, count) \
  { CU_assertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)(count))), __LINE__, ("CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(" #actual ","  #expected "," #count ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_DOUBLE_EQUAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) <= fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_DOUBLE_EQUAL_FATAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) <= fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_EQUAL_FATAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", TRUE); }

#define CU_ASSERT_DOUBLE_NOT_EQUAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) > fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_NOT_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", FALSE); }

#define CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(actual, expected, granularity) \
  { CU_assertImplementation(((fabs((double)(actual) - (expected)) > fabs((double)(granularity)))), __LINE__, ("CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", TRUE); }

#ifdef __cplusplus
}
#endif

#ifdef USE_DEPRECATED_CUNIT_NAMES

#define ASSERT(value) { if (FALSE == (int)(value)) { CU_assertImplementation((BOOL)value, __LINE__, #value, __FILE__, "", FALSE); return; }}

#define ASSERT_TRUE(value) { if (FALSE == (value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_TRUE(" #value ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_FALSE(value) { if (FALSE != (value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_FALSE(" #value ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_EQUAL(actual, expected) { if ((actual) != (expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_NOT_EQUAL(actual, expected) { if ((void*)(actual) == (void*)(expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_PTR_EQUAL(actual, expected) { if ((void*)(actual) != (void*)(expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_PTR_NOT_EQUAL(actual, expected) { if ((void*)(actual) == (void*)(expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_NOT_EQUAL(" #actual "," #expected ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_PTR_NULL(value)  { if (NULL != (void*)(value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_NULL(" #value")"), __FILE__, "", FALSE); return; }}

#define ASSERT_PTR_NOT_NULL(value) { if (NULL == (void*)(value)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_PTR_NOT_NULL(" #value")"), __FILE__, "", FALSE); return; }}

#define ASSERT_STRING_EQUAL(actual, expected) { if (strcmp((const char*)actual, (const char*)expected)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_STRING_EQUAL(" #actual ","  #expected ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_STRING_NOT_EQUAL(actual, expected) { if (!strcmp((const char*)actual, (const char*)expected)) { CU_assertImplementation(TRUE, __LINE__, ("ASSERT_STRING_NOT_EQUAL(" #actual ","  #expected ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_NSTRING_EQUAL(actual, expected, count) { if (strncmp((const char*)actual, (const char*)expected, (size_t)count)) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_NSTRING_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_NSTRING_NOT_EQUAL(actual, expected, count) { if (!strncmp((const char*)actual, (const char*)expected, (size_t)count)) { CU_assertImplementation(TRUE, __LINE__, ("ASSERT_NSTRING_NOT_EQUAL(" #actual ","  #expected "," #count ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_DOUBLE_EQUAL(actual, expected, granularity) { if ((fabs((double)actual - expected) > fabs((double)granularity))) { CU_assertImplementation(FALSE, __LINE__, ("ASSERT_DOUBLE_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", FALSE); return; }}

#define ASSERT_DOUBLE_NOT_EQUAL(actual, expected, granularity) { if ((fabs((double)actual - expected) <= fabs((double)granularity))) { CU_assertImplementation(TRUE, __LINE__, ("ASSERT_DOUBLE_NOT_EQUAL(" #actual ","  #expected "," #granularity ")"), __FILE__, "", FALSE); return; }}
#endif  /* USE_DEPRECATED_CUNIT_NAMES */

#endif  /*  _CUNIT_CUNIT_H  */
