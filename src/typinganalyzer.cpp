#include "TypingAnalyzer.h"
TypingPerf::TypingPerf()
	: wpm(0), cpm(0)
	,avgWPM(0), avgCPM(0)
	,wordCount(0), charCount(0)
	
{}

TypingAnalyzer::TypingAnalyzer(QObject* parent)
	:QObject(parent)
	, _calculationTimer(new QTimer(this))
	, _updatingInterval(1000), _cpm(0), _wpm(0)
	, _wordCounter(new WordCounter(this))
	, _intervalTimer(new QTimer(this))
	, _isStarted(false)
	,_KeyboardInterceptor(new KeyboardInterceptor(this))
	, _lastWordCount(0), _lastCharCount(0)
	,_calcCount(0)
{
	/*bindableAvgCPM().setBinding([this] {return _wordCounter->charCount / (_secCount + 1) * 60; });
	bindableAvgWPM().setBinding([this] {return _wordCounter->wordCount / (_secCount + 1) *60; });*/
	//bindableWPM().setBinding([this] {return _wordCounter->wordCount() / _secCount *60; });//!
	//bindableCPM().setBinding([this] {return _wordCounter->wordCount() / _secCount *60; });//!
	connect(_intervalTimer, &QTimer::timeout, this, &TypingAnalyzer::calculate);
	connect(_KeyboardInterceptor, &KeyboardInterceptor::keyInteracted, this, &TypingAnalyzer::handleKeyEvent);
}
void TypingAnalyzer::calculate()
{
	updateWpm((_wordCounter->wordCount - _lastWordCount) * 60000 / _updatingInterval);
	updateCpm((_wordCounter->charCount - _lastCharCount) * 60000 / _updatingInterval);
	updateAvgCpm((_avgCPM + _cpm) / ++_calcCount);
	updateAvgCpm((_avgWPM + _wpm) / _calcCount);

	_lastCharCount = _wordCounter->charCount;
	_lastWordCount = _wordCounter->wordCount;

}
//TypingAnalyzer::TypingAnalyzer(QObject* parent)
//	:TypingAnalyzer(new KeyboardInterceptor(this), parent)
//{}
//KeyboardInterceptor* TypingAnalyzer::KeyboardInterceptor() const
//{
//	return _KeyboardInterceptor;
//}
void  TypingAnalyzer::handleKeyEvent(const KeyEvent& e)
{
	if (e.type != KeyEvent::Press)
		return;
	if(e.key == Qt::Key_Space)
		_wordCounter->push_char(' ');
	else
		_wordCounter->push_char(e.text[0]);
}
int TypingAnalyzer::wpm() const { return _wpm; }
int TypingAnalyzer::cpm() const { return _cpm; }
int TypingAnalyzer::updatingInterval() const { return _updatingInterval; }
bool TypingAnalyzer::isStarted() const { return _isStarted; }
void TypingAnalyzer::setUpdatingInterval(int other) { _updatingInterval = other; }
int TypingAnalyzer::wordCount() const { return _wordCounter->wordCount; }
int TypingAnalyzer::charCount() const { return _wordCounter->charCount; }
int TypingAnalyzer::avgWPM() const { return _avgWPM; }
int TypingAnalyzer::avgCPM() const { return _avgCPM; }
//QBindable<int> TypingAnalyzer::bindableWordCount() { return /*_wordCounter->bindableWordCount();*/ QBindable<int>(&_updatingInterval);}
//QBindable<int> TypingAnalyzer::bindableCharCount(){ return /*_wordCounter->bindableCharCount();*/QBindable<int>(&_updatingInterval); }
QBindable<int> TypingAnalyzer::bindableAvgWPM() { return QBindable<int>(&_avgWPM); }
QBindable<int> TypingAnalyzer::bindableAvgCPM(){ return QBindable<int>(&_avgCPM); }
//QBindable<int> TypingAnalyzer::bindableUpdatingInterval(){ return QBindable<int>(&_updatingInterval); }
//QBindable<int> TypingAnalyzer::bindableWPM() { return QBindable<int>(&_wpm); }
//QBindable<int> TypingAnalyzer::bindableCPM() { return QBindable<int>(&_cpm	); }
void  TypingAnalyzer::updateCpm(int cpm)
{
	if (_cpm != cpm)
	{
		_cpm = cpm;
		emit cpmChanged();
	}
}
void  TypingAnalyzer::updateWpm(int wpm)
{
	if (_wpm != wpm)
	{
		_wpm = wpm;
		emit wpmChanged();
	}
}
void TypingAnalyzer::updateAvgCpm(int aCpm)
{
	if (_avgCPM != aCpm)
	{
		_avgCPM = aCpm;
		emit avgCPMChanged();
	}
}
void TypingAnalyzer::updateAvgWpm(int aWpm)
{
	if (_avgCPM != aWpm)
	{
		_avgWPM = aWpm;
		emit avgWPMChanged();
	}
}
void TypingAnalyzer::start() {
	if (_isStarted)
		return;
	_isStarted = true;
	_intervalTimer->start(_updatingInterval); 
}
void TypingAnalyzer::stop(){
	if (!_isStarted)
		return;
	_isStarted = false;
	_intervalTimer->stop();
}
void TypingAnalyzer::reset(){

	updateCpm(0);
	updateWpm(0);
	_lastWordCount = 0; _lastCharCount = 0;
	_calcCount = 0;
	_wordCounter->wordCount = 0;
	_wordCounter->charCount = 0;

}