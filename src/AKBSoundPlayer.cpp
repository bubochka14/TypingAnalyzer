#include "AKBSoundPlayer.h"
AKBSoundPlayer::AKBSoundPlayer(QObject* parent)
	:QObject(parent)
	, _inter(new KeyboardInterceptor(this))
	,_enabled(false)
{
	connect(_inter, &AKeyBoardInterceptor::keyInteracted, this, [=](const KeyEvent& e) { if (_enabled) produceSound(e); });

}
//AKBSoundPlayer::AKBSoundPlayer(AKeyBoardInterceptor* kb, QObject* parent)
//	:_inter(kb)
//{
//}
bool AKBSoundPlayer::produceSound(const KeyEvent&)
{
	return true;
}
QList<Qt::Key> AKBSoundPlayer::availableKeys() const
{
	return QList<Qt::Key>();
}
void AKBSoundPlayer::setEnabled(bool st) 
{
	if(_enabled!=st)
	{
		_enabled = st;
		emit enabledChanged();
	}
}
bool AKBSoundPlayer::enabled() const
{
	return _enabled;
}