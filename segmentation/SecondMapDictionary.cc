#define NOMINMAX
#include "stdafx.h"
#include <algorithm>

#include "SecondMapDictionary.h"
#include "unicode.h"
#include "DBinaryDictionary.h"
using namespace Xapian;



SecondMapDictionary::SecondMapDictionary()
{
}

SecondMapDictionary::~SecondMapDictionary()
{
}

SecondMapDictionary::SecondMapDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount, int length)
{
	this->ascWords = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;
	this->totalCount = totalCount;
	this->wordLength = length;
	createDictionary();
}

void SecondMapDictionary::createDictionary()
{	
	int index = beginIndex;
	unsigned indexChar;
	string str;
	if (wordLength == 6)  //if word length is 6, then each second charater is different, so using the unicode value of the second Chinese character as keyword
						//each keyword indicate unique string
	{
		while(index < endIndex)
		{
			str = ascWords[index];
			indexChar = getCharIndex(str);
			twoWordSubs.insert(pair<unsigned,string>(indexChar, str));
			index++;
		}
	}
	else
	{	//if word length is more than 2, then there may exist words which have same second Chinese character
		//so, still choosing the unicode value of the second Chinese character as keyword
		//but,each unicode indicate a vector<string>

		string strTemp;
		string strIndex = ascWords[index].substr(3,3); 
		indexChar = getCharValue(strIndex);
		int beginIndex = index;
		
		for(;index<endIndex;index++)
		{
			strTemp = ascWords[index];
			if(!isSameIndex(strTemp,indexChar) ) //if the keyword is not same, insert pair<unsigned, DBinaryDictionary*>,clear the vector and compute next keyword
			{
				DBinaryDictionary * dic = new DBinaryDictionary(ascWords, beginIndex, index, 0);
				subs.insert(pair<unsigned,DBinaryDictionary* >(indexChar,dic));
				beginIndex = index;
				string strIndex = ascWords[index].substr(3,3); 
				indexChar = getCharValue(strIndex);		
			}
			
		}
		DBinaryDictionary * dic = new DBinaryDictionary(ascWords, beginIndex, index, 0);
		subs.insert(pair<unsigned,DBinaryDictionary* >(indexChar,dic));
		
	}	

}



bool SecondMapDictionary::isSameIndex(string str, unsigned index)  //the second chinese word as hash code
{	
	unsigned it = getCharValue(str.substr(3,3));
	return it == index;
}

unsigned SecondMapDictionary::getCharValue(string str) // get the unicode value of a chinese word;
{		
	Utf8Iterator it(str);	
	return *it;		
}

unsigned SecondMapDictionary::getCharIndex(string str) // pick the second chinese word as index
{	
	Utf8Iterator it(str);
	++it;
	return *it;		
}

int SecondMapDictionary::size()
{
	return count;
}


int SecondMapDictionary::search(string input,int offset,int count, unsigned mapChar)
{
	string strTemp = input.substr(offset, count);	

	unsigned index = mapChar;
	if(count == 6)
	{
		map<unsigned, string>::iterator it = twoWordSubs.find(index);
		if( it != twoWordSubs.end())
		{
			return count; //indicate that two word is existed;
		}else
		{
			return -1; //indicate that two word is not existed
		}
	}
	else 
	{
		//if check words whose length is more than 2,
		map<unsigned, DBinaryDictionary* >::iterator it = subs.find(index);
		if(it == subs.end())
		{
			return -1;
		}else
		{
			DBinaryDictionary *dic = it->second;
			return dic->search(input, offset, count, mapChar);
			
		}
	}
	
}