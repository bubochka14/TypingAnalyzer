#include "EmptyKBSoundPlayer.h"
QList<Qt::Key> EmptyKBSoundPlayer::availableKeys() const
{
	return QList<Qt::Key>();
}
bool EmptyKBSoundPlayer::produceSound(const KeyEvent&)
{
	return true;
}