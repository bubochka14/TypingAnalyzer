#include "wordcounter.h"
WordCounter::WordCounter(QObject* parent)
	:QObject(parent)
	,wordCount(0)
	,charCount(0)
	,_state(LastIsSpace)
{

}
//QBindable<int> WordCounter::bindableWordCount() { return QBindable<int>(&_wordCount); }
//QBindable<int> WordCounter::bindableCharCount() { return QBindable<int>(&_charCount); }

//int  WordCounter::charCount() const
//{
//	return _charCount;
//}
//int  WordCounter::wordCount() const
//{
//	return _wordCount; 
//}
//void WordCounter::setWordCount(int other)
//{
//	_wordCount = other;
//}
//void WordCounter::setCharCount(int other)
//{
//	_charCount = other;
//}
void WordCounter::push_word(const QString& str)
{
	wordCount = wordCount + 1;
	charCount = charCount + str.length();
}
void WordCounter::push_char(const QChar& c)
{
	charCount = charCount + 1;
	switch (_state)
	{
	case WordCounter::LastIsLetter:
		if (c.isSpace())
			_state = LastIsSpace;
		break;
	case WordCounter::LastIsSpace:
		if (!c.isSpace())
		{
			_state = LastIsLetter;
			//setWordCount(wordCount() + 1);
			wordCount = wordCount + 1;
		}
		break;
	default:
		break;

	}
}