#define NOMINMAX
#include "stdafx.h"
#include <algorithm>
#include "BinaryDictionary.h"


BinaryDictionary::BinaryDictionary(string *ascWords, int count)
{
	this->ascWords = ascWords;
	this->beginIndex = 0;
	this->endIndex = count;
	this->count = count;
	this->hit = false;
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
	this->hit = false;

}


string BinaryDictionary::getWord(int index)
{
	return ascWords[beginIndex + index];
}



int BinaryDictionary::size()
{
	return count;
}



int BinaryDictionary::search(string input,int offset,int count, unsigned mapChar){ 
	
	hit = false;
	string temp = input.substr(offset, count * 3);
	temp +='\n';
	int searchResult = search(temp);
	int index = searchResult;
	int resultlength = -1;
	index++;
	if(hit == true)
	{		
		resultlength = count * 3;
		
	}
	size_t maxLength = count * 3;
	
	for(;index<endIndex;index++)
	{
		size_t length = ascWords[index].size() - 1;//because word in ascWords all contains '\n' in the end
		if( length < maxLength)
			break;
		if((input.size() - offset) < length)
			break;
		maxLength = length;
		string temp = input.substr(offset, length);
		temp += '\n';
		//if(input.compare(offset,length, ascWords[index]) == 0)
		if(temp.compare(ascWords[index]) == 0)
		{
			hit = true;
			resultlength = length;			
		}	
	}
	return resultlength;
	
}



int BinaryDictionary::search(string str) //check whether str in the array,using binary search
{
	int begin = beginIndex;
	int end = endIndex;
	int result;
	int middle;
	while(begin <= end)
	{
		middle = (begin + end) / 2;
		string temp = ascWords[middle];
		result = compare(str, ascWords[middle]);
		if(result == 0)
		{
			hit = true;
			return middle;
		}
		else if(result > 0)
		{
			begin =middle + 1;
		}else
		{
			end = middle - 1;
		}
		
	}
	return end;
}

int BinaryDictionary::compare(std::string str1, std::string str2)
{
	return str1.compare(str2);
	
}