#pragma once
#include "wordcounter.h"
#include <QTimer>
class WPMCalculator : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(QVector<ulong> wpm READ wpm NOTIFY wpmChanged);
	QVector<ulong> _wpmArray;
	WordCounter* _wordCounter;
	QTimer* _minTimer;
	size_t _prevWordsCount;
	
public:
	explicit WPMCalculator(WordCounter*);
	void setWordCounter(WordCounter*);
	WordCounter* wordCounter() const;
	QVector<ulong> wpm() const;
protected slots:
	void calculateWPM();

public slots:
	void start();
	void stop();
	void end();

signals:
	void wpmChanged();
};