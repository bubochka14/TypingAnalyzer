#pragma once
#include <QString>
struct KeyEvent
{
	enum  Type
	{
		Press,
		Release
	} type;
	Qt::Key key;
	Qt::KeyboardModifiers modifiers;
	QString text;
	bool isRepeating;
};