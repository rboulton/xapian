#include "StdAfx.h"
#include "SecondMapDictionary.h"

SecondMapDictionary::SecondMapDictionary(void)
{
}

SecondMapDictionary::~SecondMapDictionary(void)
{
}

SecondMapDictionary::SecondMapDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount)
{
	this->ascWords = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;
	this->totalCount = totalCount;
	createDictionary();
}

void SecondMapDictionary::createDictionary()
{
	int index = beginIndex;
	unsigned indexChar;
	string str;
	while(index < endIndex)
	{
		str = ascWords[index];
		indexChar = getCharIndex(str);
		subs.insert(pair<unsigned,string>(indexChar, str));
	}
}

unsigned SecondMapDictionary::getCharIndex(string str)
{	
	Utf8Iterator it(str);
	++it;
	++it;
	return *it;		
}

int SecondMapDictionary::getSize()
{
	return count;
}


void SecondMapDictionary::load()
{

}

bool SecondMapDictionary::search(string input)
{
	return true;
}