#include "StdAfx.h"
#include "DoubleHashDictionary.h"
#include "stdafx.h"
//#include "HashDictionary.h"
#include "BinaryDictionary.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "unordered_map.h"
#include "unicode.h"
#include "Node.h"
#include "map"

using namespace std;
using namespace Xapian;
using namespace Unicode;
using namespace Internal;


DoubleHashDictionary::DoubleHashDictionary(string* ascWords, int totalCount)
{
	//this(ascWords, 0, totalCount, totalCount);
	this->ascWords = ascWords;
	this->beginIndex = 0;
	this->endIndex = totalCount;
	this->count = totalCount;
	this->totalCount = totalCount;
	createSubDictionaries();
}

DoubleHashDictionary::~DoubleHashDictionary(void)
{
}

DoubleHashDictionary::DoubleHashDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount)
{
	this->ascWords = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;
	this->totalCount = totalCount;
	createSubDictionaries();
}

void DoubleHashDictionary::createSubDictionaries()
{
	if(beginIndex >= totalCount){
		return;
	}

	//identify the words starting with same character
	int begin = beginIndex;
	int end = begin + 1;
	unsigned beginMapChar = getIndexChar(ascWords[begin]);
	unsigned endMapChar;
	string strBeginChar="";
	append_utf8(strBeginChar, beginMapChar);
	for(; end < endIndex; end++)
	{
				
		if(!isSameIndex(strBeginChar, ascWords[end]))
		{
			addSubDictionary(beginMapChar, begin, end);
			begin = end;
			beginMapChar = getIndexChar(ascWords[end]);
			strBeginChar = "";
			append_utf8(strBegin, beginMapChar);
		}
	}
	addSubDictionary(beginMapChar, begin, endIndex);	
}


void DoubleHashDictionary::addSubDictionary(unsigned hashChar, int beginIndex, int endIndex)
{
	dictionary *subDic = createSubDictionary(ascWords,beginIndex, endIndex);
	subDictionarys.insert(pair<unsigned, dictionary*>(hashChar, subDic));

}

dictionary* DoubleHashDictionary::createSubDictionary(string *ascWords, int startIndex, int endIndex)
{
	if((endIndex - beginIndex) < 16)
	{
		dictionary *subDic = new BinaryDictionary(ascWords, startIndex, endIndex, totalCount);
		return subDic;
	}else
	{
		dictionary *subDic = new FirstLevelDictionary(ascWords, startIndex, endIndex, totalCount);
		return subDic;
	}
}

unsigned DoubleHashDictionary::getIndexChar(string str)
{	
	Utf8Iterator it(str);
	++it;
	return *it;

}


bool DoubleHashDictionary::isSameIndex(string strBeginIndex, string strEnd)
{
	return	strBeginIndex.compare(ascWords);
}