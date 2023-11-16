#pragma once
#include <functional>
#include <qobject.h>
//Interface for platform-specific keyboard capture classes
class IKeyBoardInterceptor : public QObject
{
	Q_OBJECT
public:
	//using subCallBack = std::function<void>(int/*keycode*/, double/*flags*/);
	//virtual void OnClicked(subCallBack)  = 0;
	//virtual void OnReleased(subCallBack) = 0;
	virtual ~IKeyBoardInterceptor() {}
signals:
	void keyPressed(ulong code,std::wstring text, bool isRepeating);
	void keyReleased(ulong code, std::wstring text, bool isRepeating);
};