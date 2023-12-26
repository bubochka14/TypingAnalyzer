#include "TypingAnalyzer.h"
typingRate::typingRate()
{
	reset();
}
void typingRate::reset()
{
	
	wpm = 0; cpm = 0; avgWPM = 0; avgCPM = 0; wordCount = 0; charCount = 0;
}

TypingAnalyzer::TypingAnalyzer(QObject* parent)
	:QObject(parent)
	, _calculationTimer(new QTimer(this))
	, _updatingInterval(30000)
	, _wordCounter(new WordCounter(this))
	, _updatingTimer(new QTimer(this))
	, _isStarted(false)
	,_KeyboardInterceptor(new KeyboardInterceptor(this))
{
	connect(_updatingTimer, &QTimer::timeout, this, &TypingAnalyzer::calcStatistics);
	connect(_KeyboardInterceptor, &KeyboardInterceptor::keyInteracted, this, &TypingAnalyzer::handleKeyEvent);
}
void TypingAnalyzer::calcStatistics()
{
	typingRate newRate;
	newRate.wpm = ((_wordCounter->wordCount - _rate.wordCount) * 60000 / _updatingInterval);
	newRate.cpm = ((_wordCounter->charCount - _rate.charCount) * 60000 / _updatingInterval);
	newRate.wordCount = (int)_wordCounter->wordCount;
	newRate.charCount = (int)_wordCounter->charCount;
	newRate.time = QDateTime::currentDateTime().toMSecsSinceEpoch();
	_rate = newRate;
	emit rateChanged();
}
void  TypingAnalyzer::handleKeyEvent(const KeyEvent& e)
{
	if (e.type != KeyEvent::Press)
		return;
	if(e.key == Qt::Key_Space)
		_wordCounter->push_char(' ');
	else
		_wordCounter->push_char(e.text[0]);
}
int TypingAnalyzer::updatingInterval() const { return _updatingInterval; }

bool TypingAnalyzer::isStarted() const { return _isStarted; }

void TypingAnalyzer::setUpdatingInterval(int other) 
{
	if(other >0 && other != _updatingInterval)
	{
		_updatingInterval = other;
		emit updatingIntervalChanged();
	}
}
void TypingAnalyzer::start() {
	if (_isStarted)
		return;
	_isStarted = true;
	_updatingTimer->start(_updatingInterval); 
}
void TypingAnalyzer::stop(){
	if (!_isStarted)
		return;
	_isStarted = false;
	_updatingTimer->stop();
}
void TypingAnalyzer::reset(){

	_rate.reset();
	emit rateChanged();

}
typingRate TypingAnalyzer::rate() const
{
	return _rate;
}
