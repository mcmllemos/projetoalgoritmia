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
 *  Contains Memory Related Defines to use internal routines to detect Memory Leak
 *  in Debug Versions
 *
 *  Created By     : Anil Kumar on ...(18 June 2002)
 *  Last Modified  : 18/Jun/2002
 *  Comment        : Memory Debug Functions
 *  EMail          : aksaharan@yahoo.com
 *
 *  Modified       : 17-Jul-2004 (JDS)
 *  Comment        : New interface for global function names.
 *  EMail          : jds2@users.sourceforge.net
 *
 *  Modified       : 5-Sep-2004 (JDS)
 *  Comment        : Added internal test interface.
 *  EMail          : jds2@users.sourceforge.net
 */

#ifndef _CUNIT_MYMEM_H
#define _CUNIT_MYMEM_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef MEMTRACE
  void* CU_calloc(size_t nmemb, size_t size, unsigned int uiLine, const char* szFileName);
  void* CU_malloc(size_t size, unsigned int uiLine, const char* szFileName);
  void  CU_free(void *ptr, unsigned int uiLine, const char* szFileName);
  void* CU_realloc(void *ptr, size_t size, unsigned int uiLine, const char* szFileName);
  void  CU_dump_memory_usage(const char*);

  #define CU_CALLOC(x, y)         CU_calloc((x), (y), __LINE__, __FILE__)

  #define CU_MALLOC(x)            CU_malloc((x), __LINE__, __FILE__)

  #define CU_FREE(x)              CU_free((x), __LINE__, __FILE__)

  #define CU_REALLOC(x, y)        CU_realloc((x), (y), __LINE__, __FILE__)

  #define CU_CREATE_MEMORY_REPORT(x) CU_dump_memory_usage((x))

  #define CU_DUMP_MEMORY_USAGE(x) CU_dump_memory_usage((x))
#else

  #define CU_CALLOC(x, y)         calloc((x), (y))

  #define CU_MALLOC(x)            malloc((x))

  #define CU_FREE(x)              free((x))

  #define CU_REALLOC(x, y)        realloc((x), (y))

  #define CU_CREATE_MEMORY_REPORT(x)

  #define CU_DUMP_MEMORY_USAGE(x)
#endif

#ifdef CUNIT_BUILD_TESTS

void test_cunit_deactivate_malloc(void);
void test_cunit_activate_malloc(void);
unsigned int test_cunit_get_n_memevents(void* pLocation);
unsigned int test_cunit_get_n_allocations(void* pLocation);
unsigned int test_cunit_get_n_deallocations(void* pLocation);

void test_cunit_MyMem(void);
#endif


#ifdef __cplusplus
}
#endif

#endif  /*  _CUNIT_MYMEM_H  */
