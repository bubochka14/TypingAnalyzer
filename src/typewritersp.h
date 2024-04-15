#pragma once
#include <soundinterfaces.h>
#include <QSoundEffect>
#include <QFile>
#include <qrandom.h>
#include <QDebug>
#include <qqmlengine.h>
class TypeWriterSP : public QObject, IKBSoundProducer
{
	QML_ELEMENT;
	Q_OBJECT;
	Q_INTERFACES(IKBSoundProducer);
	QVector<QSoundEffect*> _keySounds;
	QSoundEffect*          _spaceSound;
	QSoundEffect*          _enterSound;

public:
	explicit TypeWriterSP(QObject* parent= nullptr);
 //   QList<Qt::Key> availableKeys() const override;
public slots:
	bool produceSound(const KeyEvent&) override;

};