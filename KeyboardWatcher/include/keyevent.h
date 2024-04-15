#pragma once
#include <QString>
#include <QObject>
#include "keyboardwatcher_include.h"
//keyevent - struct for describing interaction with the keyboard; QKeyEvent is not suitable, because it cannot pass by value
class KeyInfo;
struct KW_EXPORT KeyEvent
{
	Q_GADGET;
	Q_PROPERTY(Qt::Key key MEMBER key);
	Q_PROPERTY(Qt::KeyboardModifiers modifiers MEMBER modifiers);
	Q_PROPERTY(QString text MEMBER text);
	Q_PROPERTY(bool isRepeating MEMBER isRepeating);
public:

	enum  InteractionType
	{
		Press,
		Release
	} type; Q_ENUM(InteractionType);
	Qt::Key key;
	Qt::KeyboardModifiers modifiers;
	QString text;
	bool isRepeating;
	//operator KeyInfo() const {
	//	KeyInfo n;
	//	n.key = key;
	//	n.modifiers = modifiers;
	//	return n;
	//}
};
