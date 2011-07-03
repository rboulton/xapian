#define NOMINMAX
#include "StdAfx.h"
#include <algorithm>
#include "SecondMapDictionary.h"
#include "unicode.h"
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
	if (wordLength == 2)  //if word length is 2, then each second charater is different, so using the unicode value of the second Chinese character as keyword
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

		vector<string> words;
		string strTemp;
		string strIndex = ascWords[index].substr(3,3); 
		indexChar = getCharValue(strIndex);
		while(index < endIndex)		{
			
			strTemp = ascWords[index];
			if(isSameIndex(strTemp,indexChar))
			{
				//dictionary *=
				
				string strIndex = ascWords[index].substr(3,3); 
				indexChar = getCharValue(strIndex);		
			}
			index++;
		}		
		
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
	string strTemp = input.substr(offset, count*3);			
	unsigned index = mapChar;
	if(count == 2)
	{
		map<unsigned, string>::iterator it = twoWordSubs.find(index);
		if( it != twoWordSubs.end())
		{
			return 2 * 3; //indicate that two word is existed;
		}else
		{
			return -1; //indicate that two word is not existed
		}
	}
	else 
	{
		//if check words whose length is more than 2,
		map<unsigned, vector<string> >::iterator it = subs.find(index);
		if(it == subs.end())
		{
			return -1;
		}else
		{
			vector<string> words = it->second;
			if(count == 3 || count == 4)
			{
				vector<string>::iterator result = find(words.begin(),words.end(),input.substr(offset, count*3));
				if(result == words.end())
					return -1;
				else
					return count * 3;
			}else //if  it more than five,check every words to find out whether it is in the input string
			{
				string word;
				int maxlength = -1;
				int size;
				for(vector<string>::iterator iter = words.begin(); iter != words.end();iter++)
				{
					word = *iter;
					if(input.compare(offset,word.size(),word) == 0)
					{
						size = word.size();
						maxlength = max(maxlength, size);
					}

				}

				return maxlength;
			}
		}
	}
	
}