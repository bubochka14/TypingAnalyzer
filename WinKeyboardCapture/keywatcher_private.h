#pragma once 
#include <QObject>
#include <cstdlib>
#include "keywatcher.h"
#include "winkeyboardinterceptor.h"
#include "ikeyboardinterceptor.h"
class KeyWatcherPrivate :public QObject
{
	Q_OBJECT;
public:
	explicit KeyWatcherPrivate(KeyWatcher* q)
		:_api_ptr(q)
		,_isWatching(false)
		,_interceptor (createInterceptor())
	{
		QObject::connect(_interceptor, &IKeyBoardInterceptor::keyPressed, this, &KeyWatcherPrivate::handlePress);
		QObject::connect(_interceptor, &IKeyBoardInterceptor::keyReleased, this, &KeyWatcherPrivate::handleRelease);

	}

	KeyWatcher* _api_ptr;
	bool _isWatching;
	IKeyBoardInterceptor* _interceptor;
	/*static void destroyInterceptor()
	{
		delete _interceptor;
		_interceptor = nullptr;
	}*/
	[[nodiscard]] IKeyBoardInterceptor* createInterceptor()
	{
#ifdef WIN32    
		//std::atexit(destroyInterceptor);
	return  WinKeyboardInterceptor::instance();
#else
#error "Keyboard interceptor not support current system"
#endif
	}
public slots:
	void handlePress(uint code, std::wstring text, bool isRepeating) {

     	QString keyText = QString::fromStdWString(text);
		QKeySequence sq(keyText);
		if (sq.count() < 1)
			return;
		KeyEvent ev = { KeyEvent::Press, sq[0].key(), sq[0].keyboardModifiers(), keyText, isRepeating };
		emit _api_ptr->eventProduced(ev);
		

	}
	void handleRelease(uint code, std::wstring text, bool isRepeating)
	{
		QString keyText = QString::fromStdWString(text);
		QKeySequence sq(keyText);
		if (sq.count() < 1)
			return;
		KeyEvent ev = {KeyEvent::Type::Release, sq[0].key(), sq[0].keyboardModifiers(), keyText, isRepeating};
		emit _api_ptr->eventProduced(ev);
	}

};