#pragma once
#include"wordcounter.h"
#include<QTimer>
#include"KeyboardInterceptor.h"
#include<QQmlEngine>
struct TypingPerf
{
	Q_GADGET;
	QML_ELEMENT;
	Q_PROPERTY(QVector<int> wpmList MEMBER wpm);
	Q_PROPERTY(QVector<int> cpmList MEMBER cpm);
	Q_PROPERTY(int wordCount MEMBER wordCount);
	Q_PROPERTY(int avgCpm MEMBER avgCPM);
	Q_PROPERTY(int avgWpm MEMBER avgCPM);
	Q_PROPERTY(int charCount MEMBER charCount);
	
public:
	explicit TypingPerf();
protected:
	QVector<int> wpm, cpm;
	int avgWPM, avgCPM;
	int	wordCount, charCount;
};
class TypingAnalyzer :public QObject
{
	Q_OBJECT;
	QML_ELEMENT;
	Q_PROPERTY(bool isStarted READ isStarted NOTIFY isStartedChanged);
	Q_PROPERTY(int wpm READ wpm NOTIFY wpmChanged /*BINDABLE bindableWPM*/);
	Q_PROPERTY(int cpm READ cpm NOTIFY cpmChanged /*BINDABLE bindableCPM*/);
	Q_PROPERTY(int updatingInterval READ updatingInterval WRITE setUpdatingInterval NOTIFY updatingIntervalChanged /*BINDABLE bindableUpdatingInterval*/);
	Q_PROPERTY(int wordCount READ wordCount NOTIFY wordCountChanged /*BINDABLE bindableWordCount*/);
	Q_PROPERTY(int charCount READ charCount NOTIFY charCountChanged /*BINDABLE bindableCharCount*/);
	Q_PROPERTY(int avgWPM READ avgWPM NOTIFY avgWPMChanged BINDABLE bindableAvgWPM);
	Q_PROPERTY(int avgCPM READ avgCPM NOTIFY avgCPMChanged BINDABLE bindableAvgCPM);
	//Q_PROPERTY(KeyboardInterceptor*KeyboardInterceptorREADKeyboardInterceptorWRITEsetKeyboardInterceptorNOTIFYKeyboardInterceptorChanged);
public:
	//staticWordCounter*qmlAttachedProperties(QObject*object)
	//{
	//	/*WordCounter*counter=newWordCounter(object);
	//	QObject::connect
	//	returnnewWordCounter(object);*/
	//}
	//explicit TypingAnalyzer(AKeyBoardInterceptor* interceptor, QObject* parent = nullptr);
	explicit TypingAnalyzer(QObject* parent = nullptr);
	int wpm() const;
	int cpm() const;
	int updatingInterval() const;
	void setUpdatingInterval(int other);
	int wordCount() const;
	int charCount() const;
	int avgWPM() const;
	int avgCPM() const;
	bool isStarted() const;
	//KeyboardInterceptor*KeyboardInterceptor()const;
	//voidsetKeyboardInterceptor(AKeyBoardInterceptor*);

public slots:
	void start();
	void stop();
	void reset();

signals:

	void wpmChanged();
	void cpmChanged();
	void updatingIntervalChanged();
	void wordCountChanged();
	void charCountChanged();
	void avgWPMChanged();
	void avgCPMChanged();
	void isStartedChanged();
	//voidKeyboardInterceptorChanged();

protected slots:
	void handleKeyEvent(const KeyEvent&);
	void calculate();
protected:
	void updateWpm(int wpm);
	void updateCpm(int cpm);
	void updateAvgCpm(int aCpm);
	void updateAvgWpm(int aWpm);
	//QBindable<int>bindableWordCount();
	//QBindable<int>bindableCharCount();
	QBindable<int>bindableAvgWPM();
	QBindable<int>bindableAvgCPM();
	//QBindable<int>bindableUpdatingInterval();
	//QBindable<int>bindableWPM();
	//QBindable<int>bindableCPM();
private:
	int	_wpm, _cpm;
	QTimer* _intervalTimer;
	Q_OBJECT_BINDABLE_PROPERTY(TypingAnalyzer, int, _avgWPM, &TypingAnalyzer::avgWPMChanged);
	Q_OBJECT_BINDABLE_PROPERTY(TypingAnalyzer, int, _avgCPM, &TypingAnalyzer::avgCPMChanged);
	int _lastWordCount, _lastCharCount;
	int _updatingInterval;
	int		_calcCount;
	bool _isStarted;
	WordCounter* _wordCounter;
	QTimer* _calculationTimer;
	size_t			_prevWordsCount;
	AKeyBoardInterceptor* _KeyboardInterceptor;

};