#pragma once
#include <QObject>
#include <keyboardinterceptor.h>
#include <keyevent.h>
class AKBSoundPlayer : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
public:
	virtual QList<Qt::Key> availableKeys() const = 0;
	virtual ~AKBSoundPlayer() {}

	void setEnabled(bool);
	bool enabled() const;
public slots:
	virtual bool produceSound(const KeyEvent&);
signals:
	void enabledChanged();
protected:
	explicit AKBSoundPlayer(QObject* parent = nullptr);
//	explicit AKBSoundPlayer(AKeyBoardInterceptor* kb, QObject* parent = nullptr);
private:
	AKeyBoardInterceptor* _inter;
	bool _enabled;
};
//class EmptyKBSoundPlayer : public QObject
//{
//	Q_OBJECT;
//	virtual QList<Qt::Key> availableKeys() const;
//
//public slots:
//	virtual bool produceSound(Qt::Key);
//};