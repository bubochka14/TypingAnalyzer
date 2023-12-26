#pragma once
#include <QObject>
#include <QQmlEngine>
#include "KeyboardInterceptor.h"

#include <QObjectBindableProperty>
//also a char counter
class WordCounter : public QObject
{
	Q_OBJECT;
	QML_UNCREATABLE("")
	//Q_PROPERTY(int wordCount READ wordCount WRITE setWordCount NOTIFY wordCountChanged BINDABLE bindableWordCount);
    //Q_PROPERTY(int charCount READ charCount WRITE setCharCount NOTIFY charCountChanged BINDABLE bindableCharCount);
public:
	enum State
	{
		LastIsLetter,
		LastIsSpace,
		RepeatingSpace
	};
	QProperty<int> wordCount;
	QProperty<int> charCount;
	explicit WordCounter(QObject *parent = nullptr);
	//virtual int charCount() const;
	//virtual int wordCount() const;

	//void setWordCount(int);
	//void setCharCount(int);
	//QBindable<int> bindableWordCount();
	//QBindable<int> bindableCharCount();
public slots:
	virtual void push_word(const QString&);
	virtual void push_char(const QChar&);
signals:
	void wordCountChanged();
	void charCountChanged();
private:
	State _state;
	//Q_OBJECT_BINDABLE_PROPERTY(WordCounter, int, _charCount, &WordCounter::charCountChanged);
	//Q_OBJECT_BINDABLE_PROPERTY(WordCounter, int, _wordCount, &WordCounter::wordCountChanged);
	QChar _lastChar;
};
