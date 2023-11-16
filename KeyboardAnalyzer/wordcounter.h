#pragma once
#include <QObject>
class WordCounter : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(size_t wordCount READ wordCount NOTIFY wordCountChanged);
	Q_PROPERTY(size_t charCount READ charCount NOTIFY charCountChanged);
	size_t _wordCount;
	size_t _charCount;
	QChar _lastChar;
public:
	explicit WordCounter(QObject *parent = nullptr);
	size_t charCount() const;
	size_t wordCount() const;
public slots:
	void push_word(const QString&);
	void push_char(const QChar&);
signals:
	void wordCountChanged();
	void charCountChanged();
};