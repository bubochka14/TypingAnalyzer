#pragma once
#include "soundinterfaces.h"
class EmptyKBSoundPlayer :public QObject, public IKBSoundProducer
{
	Q_OBJECT;
public:
	explicit EmptyKBSoundPlayer(QObject* parent = nullptr);
	bool produceSound(const const KeyEvent& e) override;
	QList<Qt::Key> availableKeys() const override;

};