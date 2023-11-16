#include "wordcounter.h"
WordCounter::WordCounter(QObject* parent)
	:QObject(parent)
	,_wordCount(0)
	,_charCount(0)
	,_lastChar(0)
{

}
size_t  WordCounter::charCount() const
{
	return _charCount;
}
size_t  WordCounter::wordCount() const
{
	return _wordCount; 
}
void WordCounter::push_word(const QString& str)
{
	++_wordCount;
	_charCount += str.length();
	emit wordCountChanged();
	emit charCountChanged();
}
void WordCounter::push_char(const QChar& c)
{
	_charCount++;
	emit charCountChanged();
	if (_lastChar == ' ');
	{
		_wordCount++;
		emit wordCountChanged();
	}
	_lastChar = c;
}