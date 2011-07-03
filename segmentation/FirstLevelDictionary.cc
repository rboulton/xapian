#define NOMINMAX

#include "stdafx.h"

#include "FirstLevelDictionary.h"
#include "BinaryDictionary.h"
#include "SecondMapDictionary.h"
#include "unicode.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "dictionary.h"
using namespace std;
using namespace Xapian;

FirstLevelDictionary::FirstLevelDictionary()
{
}

FirstLevelDictionary::~FirstLevelDictionary()
{
}

FirstLevelDictionary::FirstLevelDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount)
{
	
	maxlength = 0; //maxlength means the length of the longest word leading by the same character
	
	//int begin = beginIndex;

	//int end = begin + 1;
	
	int index = beginIndex;
	string str;
	int size;
	/*
		put words in different subdictionary, distinguished by the length of each word.
	*/
	//two character words
	
	int begin = index;
	for(;index<endIndex;index++)
	{
		//str = ascWords[index].size;
		size = ascWords[index].size();  //divided by 3 because the general chinese character in UTF-8 contains 3 byte;
		if(size != 6)
		{
			createSubDictionary(ascWords, begin, index,2);
			break;
		}
			
	}
	if((index - begin) > 1)
		maxlength = 2;
	
//three character words
	begin = index;
	for(;index<endIndex;index++)
	{
		//str = ascWords[index];
		size =  ascWords[index].size();  //divided by 3 because the general chinese character in UTF-8 contains 3 byte;
		if(size != 9)
		{
			createSubDictionary(ascWords, begin, index,3);
			break;
		}
			
	}
	if((index - begin) > 1)
		maxlength = 3;

	//four character words
	begin = index;
	for(;index<endIndex;index++)
	{
	//	str = ascWords[index];
		size = ascWords[index].size() ;  //divided by 3 because the general chinese character in UTF-8 contains 3 byte;
		if(size != 12)
		{
			createSubDictionary(ascWords, begin, index,3);
			break;
		}
			
	}
	if((index - begin) > 1)
		maxlength = 4;


	//mult character words
	begin = index;
	for(;index<endIndex;index++)
	{
	///	str = ascWords[index];
		size =  ascWords[index].size() / 3;  //divided by 3 because the general chinese character in UTF-8 contains 3 byte;

		maxlength = max(maxlength, size);			
	}
	createSubDictionary(ascWords, begin, index,5);
	

}


void FirstLevelDictionary::compileDictionary()
{
	
}



dictionary *FirstLevelDictionary::createSubDictionary(std::string *ascWords, int beginIndex, int endIndex, int length)
{
	dictionary *dic;
	int count = endIndex - beginIndex;
	
	
	if(count < 128) //if the number of words is less than 16, it is more likely using binary search is quicker, so , it using binary search.
	{
		dic = new BinaryDictionary(ascWords, beginIndex, endIndex, totalCount);
	}
	else    
	{
		dic = new SecondMapDictionary(ascWords, beginIndex,endIndex,count,length);
	}

	return dic;
}



int FirstLevelDictionary::size()
{
	return totalCount;
}



int FirstLevelDictionary::search(string input,int offset)
{
	unsigned mapChar = getMapChar(input, offset);  //if the subDictionary is sorted in map, the key word will be the unicode value of second Chinese character

	int length;

	if((length = multWordDic->search(input, offset,maxlength, mapChar) )!= -1)
		return length;
	if((length = fourWordDic->search(input,offset,4,mapChar)) != -1)
		return length;
	if((length= threeWordDic->search(input,offset,3,mapChar)) != -1)
		return length;
	if((length = twoWordDic->search(input,offset,2,mapChar)) != -1)
		return length;
	
	return -1;
}

int FirstLevelDictionary::maxValue(int i, int j, int m, int n)
{
	int temp1 = max(i,j);
	int temp2 = max(m, n);
	return max(temp1, temp2);
}

unsigned FirstLevelDictionary::getMapChar(string input,int offset) //get the unicode value of the second Chinese character of the rest input string
{
	string str = input.substr(offset + 3, 3);
	Utf8Iterator it(str);
	return *it;	
}