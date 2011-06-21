#define NOMINMAX
#include "StdAfx.h"
#include <algorithm>
#include "BinaryDictionary.h"


BinaryDictionary::BinaryDictionary(string *ascWords, int count)
{
	this->ascWords = ascWords;
	this->beginIndex = 0;
	this->endIndex = count;
	this->count = count;
}

BinaryDictionary::~BinaryDictionary()
{
}


BinaryDictionary::BinaryDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount)
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
	return count;
}



int BinaryDictionary::search(string input,int offset,int count, unsigned mapChar){ 
	if(count <= 4)
	{
		string temp = input.substr(offset, count * 3);
		if(true == search(temp))
		{
			return count * 3;
		}
		else
		{
			return -1;
		}
	}else
	{
		int index = beginIndex;
		string temp;
		int maxlength = -1;
		int size;
		for(;index<endIndex;index++)
		{
			temp = ascWords[index];
			if(input.compare(offset, temp.size(), temp) == 0)
			{
				size = temp.size();

				maxlength = max(maxlength, size);			
			}
		}

		return maxlength;
		
	}
	
}



bool BinaryDictionary::search(string str)
{
	int begin = beginIndex;
	int end = endIndex;
	int result;
	int middle;
	while(begin < end)
	{
		middle = (begin + end) / 2;
		result = compare(str, ascWords[middle]);
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