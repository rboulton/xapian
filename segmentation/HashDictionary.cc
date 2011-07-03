#include "stdafx.h"
#include "HashDictionary.h"
#include "BinaryDictionary.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "unicode.h"
#include "map"
//#include <hash>
#include <tchar.h>
using namespace std;
using namespace Xapian;


HashDictionary::HashDictionary()
{
	//dictionaryPath = "e://dic//t-base.dic";
}

HashDictionary::HashDictionary(string *ascWords, int totalCount)
{
	this->ascWords = ascWords;
	this->start = 0;
	this->end = totalCount;
	this->count = totalCount;
	this->totalCount = totalCount;
	this->mapIndex = 1;
	this->hit = false;
	createSubDictionary();
}

HashDictionary::HashDictionary(string *ascWords, int start, int end, int totalCount,int mapIndex)
{
	this->ascWords = ascWords;
	this->start = start;
	this->end = end;
	this->count = end - start;
	this->totalCount = totalCount;
	this->mapIndex = mapIndex;
	this->hit = false;
	createSubDictionary();
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
	

	int offset = (mapIndex - 1) * 3;
	string beginMapChar = ascWords[start].substr(offset, 3);
	unsigned ubeginMapChar = getIndexChar(beginMapChar);
	unsigned endMapChar;
	for(; endIndex < end; endIndex++)
	{
		//endMapChar = getIndexChar(ascWords[endIndex],mapIndex);
		if(ascWords[endIndex].compare(offset,3,beginMapChar) != 0)
		{
			
			addSubDictionary(ubeginMapChar, beginIndex, endIndex);
			beginIndex = endIndex;
			beginMapChar = ascWords[endIndex].substr(offset, 3);
			ubeginMapChar = getIndexChar(beginMapChar);
		}
	}
	addSubDictionary(ubeginMapChar, beginIndex, end);	
}



bool HashDictionary::isSameIndex(int index, string beginMapChar)
{
	return true;
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

unsigned HashDictionary::getIndexChar(string str)
{
	Utf8Iterator it(str);
	return *it;
	//return 11213;
}

unsigned HashDictionary::getIndexChar(string str, int index) //get the index'th number of chinese character
{	
	
	int length = str.size();
	if(length < (index * 3)) //if the length of the string is no more than index,return 0;
		return 0;

	//get unicode value of the index'th chinese character
	Utf8Iterator it(str);	
	
	for(int i = 1; i < index && it != Utf8Iterator(); i++) //
	{
		++it;
	}
	

	return *it;


}



int HashDictionary::search(string input,int offset,int count, unsigned mapChar)
{
 	offset = offset + (mapIndex - 1)*3;
	unsigned index = getIndexChar(input.substr(offset,3));
  	map<unsigned, dictionary*>::iterator it = subDictionarys.find(index);
	if(it == subDictionarys.end())
	{
		return -1;
	}
	else 
	{
		int res = -1;
		int maxlength = -1;
		dictionary *subdic = it->second;
		string str = subdic->getWord(0);
		if(str.size() == mapIndex * 3 + 1)
		{
			hit = true;
			maxlength = mapIndex * 3;
		}
		
		res = subdic->search(input, offset,count + 1,0);

		if(hit == true)
			return max(mapIndex * 3, res);
		else
			return res;
	}	
	
	return -1;
}


string HashDictionary::getWord(int index)
{
	return ascWords[start + index];
}

