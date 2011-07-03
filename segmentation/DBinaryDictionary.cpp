#define NOMINMAX
#include "StdAfx.h"
#include <algorithm>
#include "DBinaryDictionary.h"


DBinaryDictionary::DBinaryDictionary(string *ascWords, int count)
{
	this->ascWords = ascWords;
	this->beginIndex = 0;
	this->endIndex = count;
	this->count = count;
	this->hit = false;
}

DBinaryDictionary::~DBinaryDictionary()
{
}


DBinaryDictionary::DBinaryDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount)
{
	this->ascWords = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;
	this->hit = false;

}

string DBinaryDictionary::getWord(int index)
{
	return ascWords[beginIndex + index];
}



int DBinaryDictionary::size()
{
	return count;
}



int DBinaryDictionary::search(string input,int offset,int count, unsigned mapChar){ 
	/*
	if(count <= 4)  //if the chinese word is no more than 4, just check whether it is in dictionay 
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
	}else //if checking five or more leading words, just check every word in dictionay to find out whether it is in the input string, pick the longes one 
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

	*/
	hit = false;
	string temp = input.substr(offset, count * 3);
	int searchResult = search(temp);
	int index = searchResult;
	int resultlength = -1;
	if(hit == true)
	{
		index++;
		resultlength = count * 3;
		
	}
	size_t maxLength = count * 3;
	
	for(;index<endIndex;index++)
	{
		size_t length = ascWords[index].size();
		if( length < maxLength)
			break;
		if((input.size() - offset) < length)
			break;
		maxLength = length;
		if(input.compare(offset,length, ascWords[index]) == 0)
		{
			hit = true;
			resultlength = length;			
		}	
	}
	return resultlength;
	
}



int DBinaryDictionary::search(string str) //check whether str in the array,using binary search
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

int DBinaryDictionary::compare(std::string str1, std::string str2)
{
	return str1.compare(str2);
	
}