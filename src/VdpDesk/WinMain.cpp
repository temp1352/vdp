#include "stdafx.h"
#include "RpcShell.h"

#include <xdump.h>
#include "Application.h"
#include "MainFrame.h"

XTL::AppDump _appDump(true);

void _MsgBox(HRESULT hr, LPCWSTR path)
{
	WCHAR msg[MAX_PATH * 2];
	swprintf_s(msg, L"hr : %08x, path : %ws", hr, path);
	MessageBox(nullptr, msg, L"Test", MB_OK);
}

void _Test()
{
	WCHAR path[MAX_PATH] = L"";
	HRESULT hr = SHGetFolderPath(nullptr, CSIDL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, path);
	_MsgBox(hr, path);

	hr = SHGetFolderPath(nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, path);
	_MsgBox(hr, path);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	_SetLocalResourceInstance(_AtlBaseModule.GetModuleInstance());

	HRESULT hRes = RE_OleInitialize();

	ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	//AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	//_Test();

	Application app;
	MainFrame mainFrame;
	int ret = app.Start(lpstrCmdLine, &mainFrame);

	_AtlWinModule.m_rgWindowClassAtoms.RemoveAll();

	RE_OleUninitialize();

	return ret;
}
