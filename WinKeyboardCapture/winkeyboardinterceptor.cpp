#include "winkeyboardinterceptor.h"
WinKeyboardInterceptor* WinKeyboardInterceptor::_pInst = nullptr;
WinKeyboardInterceptor* WinKeyboardInterceptor::instance()
{
	if (!_pInst)
	{
		_pInst = new WinKeyboardInterceptor();
		std::atexit([]() {delete _pInst; });
	}
	return _pInst;
}
typedef std::basic_string<TCHAR> tstring;

tstring VirtualKeyCodeToString(UCHAR virtualKey)
{
	UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

	TCHAR szName[128];
	int result = 0;
	switch (virtualKey)
	{
	case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
	case VK_RCONTROL: case VK_RMENU:
	case VK_LWIN: case VK_RWIN: case VK_APPS:
	case VK_PRIOR: case VK_NEXT:
	case VK_END: case VK_HOME:
	case VK_INSERT: case VK_DELETE:
	case VK_DIVIDE:
	case VK_NUMLOCK:
		scanCode |= KF_EXTENDED;
	default:
		result = GetKeyNameText(scanCode << 16, szName, 128);
	}
	if (result == 0)
		throw std::system_error(std::error_code(GetLastError(), std::system_category()),
			"WinAPI Error occured.");
	return szName;
}
void WinKeyboardInterceptor::handleKey(int ccode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* pLLHKey = (KBDLLHOOKSTRUCT*)lParam;
	DWORD VKey = pLLHKey->vkCode;
	static WCHAR name[32] = L"";
	static BYTE kbState[256] = { 0 };
	static WCHAR Text[64] = { 0 };
	DWORD idThread;
	GetKeyState(VK_SHIFT);
	GetKeyState(VK_MENU);
	GetKeyboardState(kbState);

	idThread = GetWindowThreadProcessId(GetForegroundWindow(), nullptr);
	long code = MapVirtualKeyExW(VKey, MAPVK_VK_TO_VSC,
		GetKeyboardLayout(idThread)) << 16;
	size_t count = ToUnicodeEx(VKey, MapVirtualKey(VKey, MAPVK_VK_TO_VSC), kbState, name,
		32, 0, GetKeyboardLayout(idThread));
	qDebug() << count << "bytes" <<QString::fromWCharArray(name,count) << "1char" << pLLHKey->vkCode << "vkcode" << pLLHKey->scanCode << "scan";
	GetKeyNameText(pLLHKey->scanCode << 16, Text, 64);
	switch (wParam)
	{
	case WM_KEYDOWN:
		emit keyPressed(pLLHKey->vkCode,Text, false);
		break;
	case WM_KEYUP:
		emit keyReleased(pLLHKey->vkCode, Text, false);
		break;
	default:
		break;
	}	
}

LRESULT CALLBACK LLKBHookProc(int code, WPARAM wParam, LPARAM lParam) {
	if (code < 0)
		return CallNextHookEx(0, code,
			wParam, lParam);
	WinKeyboardInterceptor::instance()->handleKey(code, wParam, lParam);
	return CallNextHookEx(0, code, wParam, lParam);

}
WinKeyboardInterceptor::WinKeyboardInterceptor(WinKeyboardInterceptor::CaptureFlags fl)
{
	installHook();
	// _injHinst = LoadLibrary(L"winKeyboardCapture.dll");
	//if (_injHinst == NULL)
	//{
	//	throw "WinKeyboardCapture.dll not found";
	//}

	//_installF = (Install)GetProcAddress(_injHinst, "install");
	//_uninstallF = (Uninstall)GetProcAddress(_injHinst, "uninstall");
	//_subF = (Subscribe)GetProcAddress(_injHinst, "subscribe");
	//int* a = (int*)GetProcAddress(hinst, "b");
	//printf("%d", * a);
	//_installF();
	//_subF(wire);
}
void  WinKeyboardInterceptor::installHook()
{

	_hhk = SetWindowsHookEx(WH_KEYBOARD_LL, LLKBHookProc, NULL, NULL);
}
void  WinKeyboardInterceptor::uninstallHook()
{
	UnhookWindowsHookEx(_hhk);
}

WinKeyboardInterceptor::~WinKeyboardInterceptor()
{
	uninstallHook();
}