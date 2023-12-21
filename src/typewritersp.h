#pragma once
#include "AKBSoundPlayer.h"
#include <QSoundEffect>
#include <QFile>
#include <qrandom.h>
#include <QDebug>
#include <qqmlengine.h>
class TypeWriterSP :public AKBSoundPlayer
{
	QML_ELEMENT;
	Q_OBJECT;
	QVector<QSoundEffect*> _keySounds;
	QSoundEffect*          _spaceSound;
	QSoundEffect*          _enterSound;

public:
	explicit TypeWriterSP(QObject* parent= nullptr);
	Q_INVOKABLE QList<Qt::Key> availableKeys() const override;
public slots:
	bool produceSound(const KeyEvent&) override;
};