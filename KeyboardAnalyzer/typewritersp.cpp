#include "typewritersp.h"
TypeWriterSP::TypeWriterSP()
	:_enterSound(new QSoundEffect)
	,_spaceSound(new QSoundEffect)
{
	for (size_t i = 1;; i++)
	{

		if (!QFile(":/sounds/" + QString::number(i) + ".wav").exists())
			break;
		QSoundEffect* ks = new QSoundEffect(this);
		ks->setSource(QUrl("qrc:/sounds/" + QString::number(i) + ".wav"));
		_keySounds.push_back(ks);
	}
	_spaceSound->setSource(QUrl("qrc:/sounds/space.wav"));
	_enterSound->setSource(QUrl("qrc:/sounds/enter.wav"));
}

QList<Qt::Key> TypeWriterSP::availableKeys() const
{
	return QList<Qt::Key>();
}
bool TypeWriterSP::produceSound(const KeyEvent& e)
{
	if(e.type == KeyEvent::Press)
	{
		switch (e.key)
		{
		case Qt::Key_Space:
			_spaceSound->play();
			break;
		case Qt::Key_Enter:
			_enterSound->play();
			break;
		default:
			if (_keySounds.length() != 0)
				_keySounds[QRandomGenerator::global()->generate() % _keySounds.length()]->play();
			break;
		}
	}
	return true;
}
