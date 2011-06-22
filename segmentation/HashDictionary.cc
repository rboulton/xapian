
#include "stdafx.h"
#include "HashDictionary.h"
#include "BinaryDictionary.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "unordered_map.h"
#include "unicode.h"
#include "init.h"
#include "map"
using namespace std;
using namespace Xapian;

HashDictionary::HashDictionary()
{
	//dictionaryPath = "e://dic//t-base.dic";
}

HashDictionary::HashDictionary(string strPath)
{

}

HashDictionary::HashDictionary(string *ascWords, int start, int end, int totalCount,int mapIndex)
{
	this->ascWords = ascWords;
	this->start = start;
	this->end = end;
	this->count = end - start;
	this->totalCount = totalCount;
	this->mapIndex = mapIndex;
}

HashDictionary::~HashDictionary()
{
}

int HashDictionary::size()
{
	return 0;
}


void HashDictionary::createSubDictionary()
{
	if(start >= totalCount){
		return;
	}

	//identify the words starting with same character
	int beginIndex = start;
	int endIndex = start + 1;	
	unsigned beginMapChar = getIndexChar(ascWords[start], mapIndex);
	unsigned endMapChar;
	for(; endIndex < end; endIndex++)
	{
		endMapChar = getIndexChar(ascWords[endIndex],mapIndex);
		if(endMapChar != beginMapChar)
		{
			addSubDictionary(beginMapChar, beginIndex, endIndex);
			beginIndex = endIndex;
			beginMapChar = endMapChar;
		}
	}
	addSubDictionary(beginMapChar, beginIndex, end);	
}


void HashDictionary::addSubDictionary(unsigned hashChar, int beginIndex, int endIndex)
{
	dictionary *subDic = createSubDictionary(ascWords,beginIndex, endIndex);
	subDictionarys.insert(pair<unsigned, dictionary*>(hashChar, subDic));
}

dictionary* HashDictionary::createSubDictionary(string *ascWords, int beginIndex, int endIndex)
{
	if((endIndex - beginIndex) < 16)
	{
		dictionary *dic = new BinaryDictionary(ascWords, beginIndex, endIndex,count);
		return dic;
	}
	else 
	{
		dictionary *dic = new HashDictionary(ascWords, beginIndex, endIndex, totalCount, mapIndex + 1);
		return dic;
	}	
}



unsigned HashDictionary::getIndexChar(string str, int index)
{	
	Utf8Iterator it(str);
	for(int i = 0; i < index && it != Utf8Iterator(); i++)
	{
		++it;
	}
	if(it == Utf8Iterator())
	{
		return -1;
	}
	return *it;

}



int HashDictionary::search(std::string input, int offset)
{
	return true;
}