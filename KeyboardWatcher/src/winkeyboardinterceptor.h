#pragma once
#include <windows.h>
#include <stdio.h>
#include "AKeyBoardInterceptor.h"
#include <list>
#include <qobject.h>
#include <qdebug.h>
#include <qkeysequence.h>
#include "keyboardwatcher_include.h"
//Wrapper-class over WH_KEYBOARD_LL hook, must be a static singleton because 
//additional arguments cannot be passed to the hook proc through SetWindowsHookEx 
//to identify an instance of the class. After the first instance() call emits 
//keyPressed and keyReleased events of parent class when key pressed and released respectively.
class KW_EXPORT WinKeyboardInterceptor : public AKeyBoardInterceptor
{
public:
	enum CaptureFlags
	{
		REGULAR_BUTTONS = 0x01,
		SYS_BUTTONS     = 0x02
	};
	static WinKeyboardInterceptor* instance();
	~WinKeyboardInterceptor() override;
protected:
	KeyEvent converToKeyEvent(KeyEvent::InteractionType,uint code, std::wstring text, bool isRepeating);
private:
	friend LRESULT CALLBACK LLKBHookProc(int code, WPARAM wParam, LPARAM lParam);
	void handleKey(int code, WPARAM wParam, LPARAM lParam);
	//HINSTANCE _injHinst;
	HHOOK _hhk;
	CaptureFlags _flags;
	static WinKeyboardInterceptor* _pInst;
	explicit WinKeyboardInterceptor(CaptureFlags fl = REGULAR_BUTTONS);
	void installHook();
	void uninstallHook();
};