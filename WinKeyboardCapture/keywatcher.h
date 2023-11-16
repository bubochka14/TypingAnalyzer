#pragma once
#include <QObject>
#include <qkeysequence.h>
#include <Windows.h>
#include "keyevent.h"
class KeyWatcherPrivate;
class KeyWatcher : public QObject
{
	Q_OBJECT;
public:
	explicit KeyWatcher(QObject* parent = nullptr);
	virtual ~KeyWatcher();
public slots:
	void startWatching();
	void endWatching();
signals:
	void eventProduced(const KeyEvent& e);
private:
	QScopedPointer<KeyWatcherPrivate> _d_p;
};