#pragma once
#include "AKBSoundPlayer.h"
class EmptyKBSoundPlayer : public AKBSoundPlayer
{
public:
	explicit EmptyKBSoundPlayer() = default;
	QList<Qt::Key> availableKeys() const override;
public slots:
	bool produceSound(const KeyEvent& e) override;
};
