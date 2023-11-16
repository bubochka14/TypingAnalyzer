#pragma once
#include "KBSoundPlayerI.h"
#include <QSoundEffect>
#include <QFile>
#include <qrandom.h>
#include <QDebug>
class TypeWriterSP :public QObject, KBSoundPlayerI
{
	QVector<QSoundEffect*> _keySounds;
	QSoundEffect*          _spaceSound;
	QSoundEffect*          _enterSound;

public:
	explicit TypeWriterSP();
	QList<Qt::Key> availableKeys() const override;
	bool produceSound(const KeyEvent&) override;
};