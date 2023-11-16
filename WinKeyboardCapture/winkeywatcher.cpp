#include "winkeywatcher.h"
WinKeyWatcher::WinKeyWatcher(QObject* parent)
	:QObject(parent)
{
	HINSTANCE hinst = LoadLibrary(L"keyboardCapture.dll");
	if (hinst == NULL)
	{
		throw("KeyboardCapture.dll not founded");
	}

	//install = (Install)GetProcAddress(hinst, "install");
	//uninstall = (Uninstall)GetProcAddress(hinst, "uninstall");
}
void WinKeyWatcher::startWatching()
{
//	install();
}
void WinKeyWatcher::endWatching()
{
//	uninstall();
}
WinKeyWatcher::~WinKeyWatcher()
{
	endWatching();
}
