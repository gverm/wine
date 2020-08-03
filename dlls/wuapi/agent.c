/*
 * IWindowsUpdateAgentInfo implementation
 *
 * Copyright 2020 Gijs Vermeulen
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

#define COBJMACROS

#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "winuser.h"
#include "ole2.h"
#include "wuapi.h"
#include "wuapi_private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(wuapi);

typedef struct _agentinfo
{
    IWindowsUpdateAgentInfo IWindowsUpdateAgentInfo_iface;
    LONG refs;
} agentinfo;

static inline agentinfo *impl_from_IWindowsUpdateAgentInfo(IWindowsUpdateAgentInfo *iface)
{
    return CONTAINING_RECORD(iface, agentinfo, IWindowsUpdateAgentInfo_iface);
}

static ULONG WINAPI agentinfo_AddRef(IWindowsUpdateAgentInfo *iface)
{
    agentinfo *This = impl_from_IWindowsUpdateAgentInfo(iface);
    return InterlockedIncrement(&This->refs);
}

static ULONG WINAPI agentinfo_Release(IWindowsUpdateAgentInfo *iface)
{
    agentinfo *This = impl_from_IWindowsUpdateAgentInfo(iface);
    LONG refs = InterlockedDecrement(&This->refs);
    if (!refs)
    {
        TRACE("destroying %p\n", This);
        HeapFree(GetProcessHeap(), 0, This);
    }
    return refs;
}

static HRESULT WINAPI agentinfo_QueryInterface(IWindowsUpdateAgentInfo *iface,
                    REFIID riid, void **ppvObject)
{
    agentinfo *This = impl_from_IWindowsUpdateAgentInfo(iface);

    TRACE("%p %s %p\n", This, debugstr_guid(riid), ppvObject);

    if (IsEqualGUID(riid, &IID_IWindowsUpdateAgentInfo) ||
        IsEqualGUID(riid, &IID_IDispatch) ||
        IsEqualGUID(riid, &IID_IUnknown))
    {
        *ppvObject = iface;
    }
    else
    {
        FIXME("interface %s not implemented\n", debugstr_guid(riid));
        return E_NOINTERFACE;
    }
    IWindowsUpdateAgentInfo_AddRef(iface);
    return S_OK;
}

static HRESULT WINAPI agentinfo_GetTypeInfoCount(IWindowsUpdateAgentInfo *iface,
                    UINT *pctinfo )
{
    FIXME("\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI agentinfo_GetTypeInfo(IWindowsUpdateAgentInfo *iface,
                    UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo)
{
    FIXME("\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI agentinfo_GetIDsOfNames(IWindowsUpdateAgentInfo *iface,
                    REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid,
                    DISPID *rgDispId)
{
    FIXME("\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI agentinfo_Invoke(IWindowsUpdateAgentInfo *iface,
                    DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags,
                    DISPPARAMS *pDispParams, VARIANT *pVarResult,
                    EXCEPINFO *pExcepInfo, UINT *puArgErr )
{
    FIXME("\n");
    return E_NOTIMPL;
}

static HRESULT WINAPI agentinfo_GetInfo(IWindowsUpdateAgentInfo *iface,
                    VARIANT identifier, VARIANT *ret)
{
    FIXME("\n");
    return E_NOTIMPL;
}


static const struct IWindowsUpdateAgentInfoVtbl agentinfo_vtbl =
{
    agentinfo_QueryInterface,
    agentinfo_AddRef,
    agentinfo_Release,
    agentinfo_GetTypeInfoCount,
    agentinfo_GetTypeInfo,
    agentinfo_GetIDsOfNames,
    agentinfo_Invoke,
    agentinfo_GetInfo,
};

HRESULT AgentInformation_create(LPVOID *ppObj)
{
    agentinfo *info;

    TRACE("(%p)\n", ppObj);

    info = HeapAlloc(GetProcessHeap(), 0, sizeof(*info));
    if (!info)
        return E_OUTOFMEMORY;

    info->IWindowsUpdateAgentInfo_iface.lpVtbl = &agentinfo_vtbl;
    info->refs = 1;

    *ppObj = &info->IWindowsUpdateAgentInfo_iface;

    TRACE("returning iface %p\n", *ppObj);
    return S_OK;
}
