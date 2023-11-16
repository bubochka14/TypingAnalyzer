#include "keywatcher.h"
#include "keywatcher_private.h"
//KeyEvent::KeyEvent(Type t, Qt::Key k, Qt::KeyboardModifier m,
//	QString tt, bool r)
//	:key(k)
//	,type(t)
//	,modifiers(m)
//	,text(tt)
//	,isRepeating(r)
//{
//}
KeyWatcher::KeyWatcher(QObject* parent)
	:QObject(parent)
	,_d_p(new KeyWatcherPrivate(this))
{
}
void KeyWatcher::startWatching()
{

}
void KeyWatcher::endWatching()
{

}
KeyWatcher::~KeyWatcher()
{

}