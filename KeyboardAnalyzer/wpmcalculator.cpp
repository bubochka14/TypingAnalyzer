#include "wpmcalculator.h"

WPMCalculator::WPMCalculator(WordCounter* wc)
	:_wordCounter(wc)
	,_minTimer(new QTimer(this))
{
	connect(_minTimer, &QTimer::timeout, this, &WPMCalculator::calculateWPM);
}
void WPMCalculator::setWordCounter(WordCounter* wc)
{
	if (_wordCounter != wc)
	{
		_wordCounter = wc;
	}
}
void  WPMCalculator::calculateWPM()
{
	size_t dist = _prevWordsCount - _wordCounter->wordCount();
	_wpmArray.append(dist / 60);
	_prevWordsCount = _wordCounter->wordCount();
	emit wpmChanged();
}
QVector<ulong>  WPMCalculator::wpm() const
{
	return _wpmArray;
}
WordCounter* WPMCalculator::wordCounter() const
{
	return _wordCounter;
}
void WPMCalculator::start()
{
	_prevWordsCount = _wordCounter->wordCount();
	_minTimer->start(60000);
}
void  WPMCalculator::stop()
{

}
void  WPMCalculator::end()
{

}