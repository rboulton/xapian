#include "StdAfx.h"
#include "BinaryDictionary.h"

BinaryDictionary::BinaryDictionary(string *ascWords, int count)
{
//	this(ascWords, 0, count);
	this->ascWords = ascWords;
	this->beginIndex = 0;
	this->endIndex = count;
	this->count = count;
}

BinaryDictionary::~BinaryDictionary(void)
{
}


BinaryDictionary::BinaryDictionary(std::string *ascWords, int beginIndex, int endIndex)
{
	this->ascWords = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;

}

string BinaryDictionary::getWord(int index)
{
	return ascWords[index];
}



int BinaryDictionary::size()
{
	return 0;
}

void BinaryDictionary::load()
{
}

bool BinaryDictionary::search(string input)
{ 
	int begin = beginIndex;
	int end = endIndex;
	int result;
	int middle;
	while(begin < end)
	{
		middle = (begin + end) / 2;
		result = compare(input, ascWords[middle]);
		if(result == 0)
		{
			return true;
		}
		else if(result > 0)
		{
			begin =middle;
		}else
		{
			end = middle;
		}
		
	}

	return false;
}

int BinaryDictionary::compare(std::string str1, std::string str2)
{
	return str1.compare(str2);
	
}