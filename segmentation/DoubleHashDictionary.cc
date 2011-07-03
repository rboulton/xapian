#include "stdafx.h"
#include "DoubleHashDictionary.h"

#include "FirstLevelDictionary.h"
#include "BinaryDictionary.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "unicode.h"
#include "map"

using namespace std;
using namespace Xapian;
using namespace Unicode;



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

DoubleHashDictionary::~DoubleHashDictionary()
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
	unsigned beginMapChar = getIndexChar(ascWords[begin]); //get the first chinese character from beginning word, 
	string strBeginChar = ascWords[begin].substr(0,3);
	

	 // words starts with same character is put into a dictionary
	// dictionary is already sorted
	clock_t start = clock();
	for(; end < endIndex; end++)
	{

		if(!isSameIndex(strBeginChar, ascWords[end])) // if the first character is not same , then the words before that is in a sub dictionary
		{
			addSubDictionary(beginMapChar, begin, end); 
			begin = end;
			beginMapChar = getIndexChar(ascWords[end]);
			strBeginChar = ascWords[begin].substr(0,3);
		}
	}
	addSubDictionary(beginMapChar, begin, endIndex);	
	clock_t next = clock();
	int time = next - start;
	cout<<"add dictionary time:";
	cout<<time<<endl;
}


void DoubleHashDictionary::addSubDictionary(unsigned hashChar, int beginIndex, int endIndex)
{
	FirstLevelDictionary *subDic = createSubDictionary(ascWords,beginIndex, endIndex);
	subDictionaries.insert(pair<unsigned, FirstLevelDictionary*>(hashChar, subDic));

}

FirstLevelDictionary* DoubleHashDictionary::createSubDictionary(string *ascWords, int startIndex, int endIndex)
{
	FirstLevelDictionary *subDic = new FirstLevelDictionary(ascWords, startIndex, endIndex, totalCount);
	return subDic;

}

unsigned DoubleHashDictionary::getIndexChar(string str)
{	
	Utf8Iterator it(str);
	return *it;

}


unsigned DoubleHashDictionary::getIndexChar(string str, int offset)
{
	string strTemp = str.substr(offset, 3);
	Utf8Iterator it(strTemp);
	return *it;
	
}


bool DoubleHashDictionary::isSameIndex(string strIndex, string str)
{
	if(str.compare(0,3,strIndex) == 0)
		return true;
	else 
		return false;
	
}

int DoubleHashDictionary::size()
{
	return count;
}



void DoubleHashDictionary::search(string input, vector<string> &output)
{
	int offset = 0, index = 0;
	unsigned inputLength = input.size();
	FirstLevelDictionary *dic;
	
	while(offset < inputLength)  //characters before offset is already segmented
	{
		unsigned mapCode = getIndexChar(input, offset); //get the unicode of first Chinese character from the rest of input.
		map<unsigned, FirstLevelDictionary*>::iterator it = subDictionaries.find(mapCode); //get the dictionary according the first Chinese character's unicode value
		
		if(it != subDictionaries.end())  //if the Chinese character is in the dictionary
		{
			dic = it->second;
			index = dic->search(input, offset); //search the possible word from subDictionary
			if(index > 0)
			{
				output.push_back( input.substr(offset, index)); //if there exists word, just put it in the output, and move to the rest of input string
				offset += index;
			}else
			{
				output.push_back(input.substr(offset, 3));//if there is no such word, just move to next character.
				offset += 3;
			}
		}else
		{
			output.push_back(input.substr(offset,3)); //if there is no word leading by this Chinese character
			offset += 3;
		}
		
	}

}