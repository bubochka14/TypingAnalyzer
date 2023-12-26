#pragma once
#include"wordcounter.h"
#include<QTimer>
#include"KeyboardInterceptor.h"
#include <algorithm>
#include<QQmlEngine>
#include <time.h> 
struct typingRate
{
	explicit typingRate();
	void reset();
	int wpm, cpm;
	int avgWPM, avgCPM;
	int	wordCount, charCount;
	long long time;
private:
	Q_GADGET;
	QML_ELEMENT;
	Q_PROPERTY(int wpm MEMBER wpm);
	Q_PROPERTY(int cpm MEMBER cpm);
	Q_PROPERTY(int wordCount MEMBER wordCount);
	Q_PROPERTY(int avgCpm MEMBER avgCPM);
	Q_PROPERTY(int avgWpm MEMBER avgCPM);
	Q_PROPERTY(int charCount MEMBER charCount);
	Q_PROPERTY(long long time MEMBER time);
};
using RatesList = QList<typingRate>;
Q_DECLARE_METATYPE(RatesList);
class TypingAnalyzer :public QObject
{
	Q_OBJECT;
	QML_ELEMENT;
	Q_PROPERTY(bool isStarted READ isStarted NOTIFY isStartedChanged);
	Q_PROPERTY(int updatxingInterval READ updatingInterval WRITE setUpdatingInterval NOTIFY updatingIntervalChanged);
	Q_PROPERTY(typingRate rate READ rate NOTIFY rateChanged);
public:
	explicit TypingAnalyzer(QObject* parent = nullptr);
	int updatingInterval() const;
	void setUpdatingInterval(int other);
	bool isStarted() const;
	typingRate rate() const;
public slots:	
	void start();
	void stop();
	void reset();
signals:
	void updatingIntervalChanged();
	void isStartedChanged();
	void rateChanged();
protected slots:
	void handleKeyEvent(const KeyEvent&);
	void calcStatistics();
private:
	//RatesList _rates;
	QTimer* _updatingTimer;
	typingRate _rate;
	int _updatingInterval;
	bool _isStarted;
	WordCounter* _wordCounter;
	QTimer* _calculationTimer;
	AKeyBoardInterceptor* _KeyboardInterceptor;

};