#pragma once
#include <soundinterfaces.h>
#include <QSoundEffect>
#include <QFile>
#include <qrandom.h>
#include <QDebug>
#include <qqmlengine.h>
class TypeWriterSP : public QObject, public IKBSoundProducer
{
	QML_ELEMENT;
	Q_OBJECT;
	QVector<QSoundEffect*> _keySounds;
	QSoundEffect*          _spaceSound;
	QSoundEffect*          _enterSound;

public:
	explicit TypeWriterSP(QObject* parent= nullptr);
    QList<Qt::Key> availableKeys() const override;
	bool produceSound(const KeyEvent&) override;

};