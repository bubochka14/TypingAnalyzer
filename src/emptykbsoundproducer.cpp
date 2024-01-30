#include "emptykbsoundproducer.h"
EmptyKBSoundPlayer::EmptyKBSoundPlayer(QObject* parent)
	:QObject(parent)
{
}
QList<Qt::Key> EmptyKBSoundPlayer::availableKeys() const
{
	return QList<Qt::Key>();
}
bool EmptyKBSoundPlayer::produceSound(const KeyEvent&)
{
	return true;
}