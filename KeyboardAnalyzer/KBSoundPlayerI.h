#pragma once
#include <QObject>
#include <keyevent.h>
class KBSoundPlayerI
{
public:

	virtual QList<Qt::Key> availableKeys() const = 0;
	virtual ~KBSoundPlayerI() {}
	virtual bool produceSound(const KeyEvent&) = 0;
};
//class EmptyKBSoundPlayer : public QObject
//{
//	Q_OBJECT;
//	virtual QList<Qt::Key> availableKeys() const;
//
//public slots:
//	virtual bool produceSound(Qt::Key);
//};