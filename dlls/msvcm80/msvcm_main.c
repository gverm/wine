/*
 * Copyright 2010 Vincent Povirk for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>

#include "windef.h"
#include "winbase.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(msvcm);

typedef LONG streamoff;
typedef SSIZE_T streamsize;

typedef struct {
    const int *vbtable;
    streamsize count;
    /* virtual inheritance
     * basic_ios_char basic_ios;
     */
} basic_istream_char;

typedef struct _basic_ostream_char {
    const int *vbtable;
    /* virtual inheritance
     * basic_ios_char basic_ios;
     */
} basic_ostream_char;

typedef struct {
    const int *vbtable;
    streamsize count;
    /* virtual inheritance
     * basic_ios_wchar basic_ios;
     */
} basic_istream_wchar;

typedef struct _basic_ostream_wchar {
    const int *vbtable;
    /* virtual inheritance
     * basic_ios_wchar basic_ios;
     */
} basic_ostream_wchar;

/* void __cdecl <CrtImplementationDetails>::DoDllLanguageSupportValidation(void) */
void __cdecl CrtImplementationDetails_DoDllLanguageSupportValidation(void)
{
    FIXME("stub\n");
}

/* void __cdecl <CrtImplementationDetails>::RegisterModuleUninitializer(System.EventHandler^) */
void __cdecl CrtImplementationDetails_RegisterModuleUninitializer(void* handler)
{
    FIXME("%p: stub\n", handler);
}

/* handler is a "method" with signature int32 (*handler)(_exception*), but I'm
 * not sure what that means */
void __cdecl __setusermatherr_m(void *handler)
{
    FIXME("%p: stub\n", handler);
}

/* ?_Cin_func@std@@YAAAV?$basic_istream@DU?$char_traits@D@std@@@1@XZ */
/* ?_Cin_func@std@@YAAEAV?$basic_istream@DU?$char_traits@D@std@@@1@XZ */
basic_istream_char* __cdecl _Cin_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Cout_func@std@@YAAAV?$basic_ostream@DU?$char_traits@D@std@@@1@XZ */
/* ?_Cout_func@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@1@XZ */
basic_ostream_char* __cdecl _Cout_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Clog_func@std@@YAAAV?$basic_ostream@DU?$char_traits@D@std@@@1@XZ */
/* ?_Clog_func@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@1@XZ */
basic_ostream_char* __cdecl _Clog_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Cerr_func@std@@YAAAV?$basic_ostream@DU?$char_traits@D@std@@@1@XZ */
/* ?_Cerr_func@std@@YAAEAV?$basic_ostream@DU?$char_traits@D@std@@@1@XZ */
basic_ostream_char* __cdecl _Cerr_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Wcin_func@std@@YAAAV?$basic_istream@_WU?$char_traits@_W@std@@@1@XZ */
/* ?_Wcin_func@std@@YAAEAV?$basic_istream@_WU?$char_traits@_W@std@@@1@XZ */
basic_istream_wchar* __cdecl _Wcin_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Wcout_func@std@@YAAAV?$basic_ostream@_WU?$char_traits@_W@std@@@1@XZ */
/* ?_Wcout_func@std@@YAAEAV?$basic_ostream@_WU?$char_traits@_W@std@@@1@XZ */
basic_ostream_wchar* __cdecl _Wcout_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Wclog_func@std@@YAAAV?$basic_ostream@_WU?$char_traits@_W@std@@@1@XZ */
/* ?_Wclog_func@std@@YAAEAV?$basic_ostream@_WU?$char_traits@_W@std@@@1@XZ */
basic_ostream_wchar* __cdecl _Wclog_func(void)
{
    FIXME("()\n");

    return NULL;
}

/* ?_Wcerr_func@std@@YAAAV?$basic_ostream@_WU?$char_traits@_W@std@@@1@XZ */
/* ?_Wcerr_func@std@@YAAEAV?$basic_ostream@_WU?$char_traits@_W@std@@@1@XZ */
basic_ostream_wchar* __cdecl _Wcerr_func(void)
{
    FIXME("()\n");

    return NULL;
}

const streamoff std_BADOFF = -1;

/* ?_BADOFF_func@std@@YAABJXZ */
/* ?_BADOFF_func@std@@YAAEB_JXZ */
const streamoff * __cdecl BADOFF_func(void)
{
    return &std_BADOFF;
}

/* ?_Fpz@std@@3_JA  __int64 std::_Fpz */
__int64 std_Fpz = 0;

/* ?_Fpz_func@std@@YAAA_JXZ */
/* ?_Fpz_func@std@@YAAEA_JXZ */
__int64 * __cdecl _Fpz_func(void)
{
    return &std_Fpz;
}
