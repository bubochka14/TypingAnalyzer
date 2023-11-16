#pragma once
#include "KBSoundPlayerI.h"
class EmptyKBSoundPlayer : public KBSoundPlayerI
{
public:
	explicit EmptyKBSoundPlayer() = default;
	QList<Qt::Key> availableKeys() const override;
	//~KBSoundPlayerI() {}
	bool produceSound(const KeyEvent& e) override;
};