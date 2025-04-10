
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
 *  Contains all the Type Definitions and functions declarations
 *  for the CUnit test database maintenance.
 *
 *  Created By     : Anil Kumar on ...(in month of Aug 2001)
 *  Last Modified  : 09/Aug/2001
 *  Comment        : Added Preprocessor conditionals for the file.
 *  EMail          : aksaharan@yahoo.com
 *
 *  Last Modified  : 24/aug/2001 by Anil Kumar
 *  Comment        : Made the linked list from SLL to DLL(doubly linked list).
 *  EMail          : aksaharan@yahoo.com
 *
 *  Last Modified  : 31-Aug-2004 (JDS)
 *  Comment        : Restructured to eliminate global variables error_number, g_pTestRegistry
 *                   new interface, support for deprecated version 1 interface,
 *                   moved error handling code to CUError.h and CUError.c, moved
 *                   test run counts and _TestResult out of TestRegistry to
 *                   TestRun.h.
 *  EMail          : jds2@users.sourceforge.net
 *
 *  Last Modified  : 1-Sep-2004 (JDS)
 *  Comment        : Added jmp_buf to CU_Test.
 *  Email          : jds2@users.sourceforge.net
 *
 *  Modified       : 5-Sep-2004 (JDS)
 *  Comment        : Added internal test interface.
 *  EMail          : jds2@users.sourceforge.net
 */
#ifndef _CUNIT_TESTDB_H
#define _CUNIT_TESTDB_H
#include <setjmp.h>   /* jmp_buf */
#include "CUnit.h"
#include "CUError.h"
#ifdef __cplusplus
extern "C" {
    #endif
    /*  Type definition for Initialization/Cleaup/TestFunction */
    typedef int (*CU_InitializeFunc)(void);   
    typedef int (*CU_CleanupFunc)(void);      
    typedef void (*CU_TestFunc)(void);        
    typedef struct CU_Test
    {
      char*           pName;                  
      CU_TestFunc     pTestFunc;              
      jmp_buf*        pJumpBuf;               
      struct CU_Test* pNext;                  
      struct CU_Test* pPrev;                  
} CU_Test;
typedef CU_Test* CU_pTest;                
typedef struct CU_Suite
{
      char*             pName;                
      CU_pTest          pTest;                
      CU_InitializeFunc pInitializeFunc;      
      CU_CleanupFunc    pCleanupFunc;         
      unsigned int      uiNumberOfTests;      
      struct CU_Suite*  pNext;                
      struct CU_Suite*  pPrev;                
} CU_Suite;
typedef CU_Suite* CU_pSuite;              
typedef struct CU_TestRegistry
{
    #ifdef USE_DEPRECATED_CUNIT_NAMES
      union {
        unsigned int uiNumberOfSuites;        
        unsigned int uiNumberOfGroups;        
  };
  unsigned int uiNumberOfTests;           
  union {
        CU_pSuite    pSuite;                  
        CU_pSuite    pGroup;                  
  };
#else
  unsigned int uiNumberOfSuites;          
  unsigned int uiNumberOfTests;           
  CU_pSuite    pSuite;                    
#endif
} CU_TestRegistry;
typedef CU_TestRegistry* CU_pTestRegistry;  
/* Public interface functions */
CU_ErrorCode CU_initialize_registry(void);
void         CU_cleanup_registry(void);
CU_pSuite CU_add_suite(const char* strName, CU_InitializeFunc pInit, CU_CleanupFunc pClean);
CU_pTest  CU_add_test(CU_pSuite pSuite, const char* strName, CU_TestFunc pTestFunc);
#define CU_ADD_TEST(suite, test) (CU_add_test(suite, #test, (CU_TestFunc)test))
/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/*  This section is based conceptually on code
 *  Copyright (C) 2004  Aurema Pty Ltd.
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
 *
 *  Derived from code contributed by K. Cheung and Aurema Pty Ltd. (thanks!)
 *    test_case_t, test_group_t, test_suite_t
 */
typedef struct CU_TestInfo {
            char        *pName;     
            CU_TestFunc pTestFunc;  
} CU_TestInfo;
typedef CU_TestInfo* CU_pTestInfo;  
typedef struct CU_SuiteInfo {
            char              *pName;        
            CU_InitializeFunc pInitFunc;     
            CU_CleanupFunc    pCleanupFunc;  
            CU_TestInfo       *pTests;       
} CU_SuiteInfo;
typedef CU_SuiteInfo* CU_pSuiteInfo;  
#define CU_TEST_INFO_NULL { NULL, NULL }
#define CU_SUITE_INFO_NULL { NULL, NULL, NULL, NULL }
CU_ErrorCode CU_register_suites(CU_SuiteInfo suite_info[]);
CU_ErrorCode CU_register_nsuites(int suite_count, ...);
#ifdef USE_DEPRECATED_CUNIT_NAMES
typedef CU_TestInfo test_case_t;    
typedef CU_SuiteInfo test_group_t;  
typedef struct test_suite {
            char *name;            
            test_group_t *groups;  
} test_suite_t;
#define TEST_CASE_NULL { NULL, NULL }
#define TEST_GROUP_NULL { NULL, NULL, NULL, NULL }
#define test_group_register(tg) CU_register_suites(tg)
int test_suite_register(test_suite_t *ts)
{
            test_group_t *tg;
            int error;
            for (tg = ts->groups; tg->pName; tg++)
                    if ((error = CU_register_suites(tg)) != CUE_SUCCESS)
                            return error;
            return CUE_SUCCESS;
}
#endif    /* USE_DEPRECATED_CUNIT_NAMES */
/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
#ifdef USE_DEPRECATED_CUNIT_NAMES
typedef CU_InitializeFunc InitializeFunc; 
typedef CU_CleanupFunc CleanupFunc;       
typedef CU_TestFunc TestFunc;             
typedef CU_Test _TestCase;                
typedef CU_pTest PTestCase;               
typedef CU_Suite  _TestGroup;             
typedef CU_pSuite PTestGroup;             
typedef CU_TestRegistry  _TestRegistry;   
typedef CU_pTestRegistry PTestRegistry;   
/* Public interface functions */
#define initialize_registry() CU_initialize_registry()
#define cleanup_registry() CU_cleanup_registry()
#define add_test_group(name, init, clean) CU_add_suite(name, init, clean)
#define add_test_case(group, name, test) CU_add_test(group, name, test)
/* private internal CUnit testing functions */
#define get_registry() CU_get_registry()
#define set_registry(reg) CU_set_registry((reg))
#define get_group_by_name(group, reg) CU_get_suite_by_name(group, reg)
#define get_test_by_name(test, group) CU_get_test_by_name(test, group)
#define ADD_TEST_TO_GROUP(group, test) (CU_add_test(group, #test, (CU_TestFunc)test))
#endif  /* USE_DEPRECATED_CUNIT_NAMES */
/* Internal CUnit system functions.  Should not be routinely called by users. */
CU_pTestRegistry CU_get_registry(void);
CU_pTestRegistry CU_set_registry(CU_pTestRegistry pTestRegistry);
CU_pTestRegistry CU_create_new_registry(void);
void             CU_destroy_existing_registry(CU_pTestRegistry* ppRegistry);
CU_pSuite        CU_get_suite_by_name(const char* szSuiteName, CU_pTestRegistry pRegistry);
CU_pTest         CU_get_test_by_name(const char* szTestName, CU_pSuite pSuite);
#ifdef CUNIT_BUILD_TESTS
void test_cunit_TestDB(void);
#endif
#ifdef __cplusplus
}
#endif
#endif  /*  _CUNIT_TESTDB_H  */
