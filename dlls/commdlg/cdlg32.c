/*
 *  Common Dialog Boxes interface (32 bit)
 *  Find/Replace
 *
 * Copyright 1999 Bertho A. Stultiens
 */

#include "winbase.h"
#include "wine/winbase16.h"
#include "commdlg.h"
#include "cderr.h"
#include "debugtools.h"

DEFAULT_DEBUG_CHANNEL(commdlg);

#include "cdlg.h"


HINSTANCE	COMDLG32_hInstance = 0;
HINSTANCE16	COMDLG32_hInstance16 = 0;

static DWORD	COMDLG32_TlsIndex;

HINSTANCE	SHELL32_hInstance = 0;
HINSTANCE	SHFOLDER_hInstance = 0;

/* ITEMIDLIST */
LPITEMIDLIST WINAPI (*COMDLG32_PIDL_ILClone) (LPCITEMIDLIST);
LPITEMIDLIST WINAPI (*COMDLG32_PIDL_ILCombine)(LPCITEMIDLIST,LPCITEMIDLIST);
LPITEMIDLIST WINAPI (*COMDLG32_PIDL_ILGetNext)(LPITEMIDLIST);
BOOL WINAPI (*COMDLG32_PIDL_ILRemoveLastID)(LPCITEMIDLIST);
BOOL WINAPI (*COMDLG32_PIDL_ILIsEqual)(LPCITEMIDLIST, LPCITEMIDLIST);

/* SHELL */
LPVOID WINAPI (*COMDLG32_SHAlloc)(DWORD);
DWORD WINAPI (*COMDLG32_SHFree)(LPVOID);
BOOL WINAPI (*COMDLG32_SHGetFolderPathA)(HWND,int,HANDLE,DWORD,LPSTR);

/***********************************************************************
 *	COMDLG32_DllEntryPoint			(COMDLG32.init)
 *
 *    Initialization code for the COMDLG32 DLL
 *
 * RETURNS:
 *	FALSE if sibling could not be loaded or instantiated twice, TRUE
 *	otherwise.
 */
static char * GPA_string = "Failed to get entry point %s for hinst = 0x%08x\n";
#define GPA(dest, hinst, name) \
	if(!(dest = (void*)GetProcAddress(hinst,name)))\
	{ \
	  ERR(GPA_string, debugres_a(name), hinst); \
	  return FALSE; \
	}

BOOL WINAPI COMDLG32_DllEntryPoint(HINSTANCE hInstance, DWORD Reason, LPVOID Reserved)
{
	TRACE("(%08x, %08lx, %p)\n", hInstance, Reason, Reserved);

	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		COMDLG32_hInstance = hInstance;
		DisableThreadLibraryCalls(hInstance);

		if(!COMDLG32_hInstance16)
		{
			if(!(COMDLG32_hInstance16 = LoadLibrary16("commdlg.dll")))
			{
				ERR("Could not load sibling commdlg.dll\n");
				return FALSE;
			}
		}

		COMDLG32_TlsIndex = 0xffffffff;

		SHELL32_hInstance = GetModuleHandleA("SHELL32.DLL");
		
		if (!SHELL32_hInstance)
		{
			ERR("loading of shell32 failed\n");
			return FALSE;
		}

		/* ITEMIDLIST */
		GPA(COMDLG32_PIDL_ILIsEqual, SHELL32_hInstance, (LPCSTR)21L);
		GPA(COMDLG32_PIDL_ILCombine, SHELL32_hInstance, (LPCSTR)25L);
		GPA(COMDLG32_PIDL_ILGetNext, SHELL32_hInstance, (LPCSTR)153L);
		GPA(COMDLG32_PIDL_ILClone, SHELL32_hInstance, (LPCSTR)18L);
		GPA(COMDLG32_PIDL_ILRemoveLastID, SHELL32_hInstance, (LPCSTR)17L);
		
		/* SHELL */
		
		GPA(COMDLG32_SHAlloc, SHELL32_hInstance, (LPCSTR)196L);
		GPA(COMDLG32_SHFree, SHELL32_hInstance, (LPCSTR)195L);
		/* for the first versions of shell32 SHGetFolderPathA is in SHFOLDER.DLL */
		COMDLG32_SHGetFolderPathA = (void*)GetProcAddress(SHELL32_hInstance,"SHGetFolderPathA");
		if (!COMDLG32_SHGetFolderPathA)
		{
		  SHFOLDER_hInstance = LoadLibraryA("SHFOLDER.DLL");
		  GPA(COMDLG32_SHGetFolderPathA, SHFOLDER_hInstance,"SHGetFolderPathA");
		}

		break;

	case DLL_PROCESS_DETACH:
            if (COMDLG32_TlsIndex != 0xffffffff) TlsFree(COMDLG32_TlsIndex);
            COMDLG32_TlsIndex = 0xffffffff;
            COMDLG32_hInstance = 0;
            if(COMDLG32_hInstance16) FreeLibrary16(COMDLG32_hInstance16);
            if(SHFOLDER_hInstance) FreeLibrary(SHFOLDER_hInstance);
            break;
	}
	return TRUE;
}
#undef GPA

/***********************************************************************
 *	COMDLG32_AllocMem 			(internal)
 * Get memory for internal datastructure plus stringspace etc.
 *	RETURNS
 *		Pointer to a heap block: Succes
 *		NULL: Failure
 */
LPVOID COMDLG32_AllocMem(
	int size	/* [in] Block size to allocate */
) {
        LPVOID ptr = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        if(!ptr)
        {
        	COMDLG32_SetCommDlgExtendedError(CDERR_MEMALLOCFAILURE);
                return NULL;
        }
        return ptr;
}


/***********************************************************************
 *	COMDLG32_SetCommDlgExtendedError	(internal)
 *
 * Used to set the thread's local error value if a comdlg32 function fails.
 */
void COMDLG32_SetCommDlgExtendedError(DWORD err)
{
	TRACE("(%08lx)\n", err);
        if (COMDLG32_TlsIndex == 0xffffffff)
	  COMDLG32_TlsIndex = TlsAlloc();
	if (COMDLG32_TlsIndex != 0xffffffff)
	  TlsSetValue(COMDLG32_TlsIndex, (void *)err);
	else
	  FIXME("No Tls Space\n");
}


/***********************************************************************
 *	CommDlgExtendedError			(COMMDLG.26)
 *	CommDlgExtendedError			(COMDLG32.@)
 *
 * Get the thread's local error value if a comdlg32 function fails.
 *	RETURNS
 *		Current error value which might not be valid
 *		if a previous call succeeded.
 */
DWORD WINAPI CommDlgExtendedError(void)
{
        if (COMDLG32_TlsIndex != 0xffffffff) 
	  return (DWORD)TlsGetValue(COMDLG32_TlsIndex);
	else
	  return 0; /* we never set an error, so there isn't one */
}
