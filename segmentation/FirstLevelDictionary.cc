#define NOMINMAX

#include "stdafx.h"
#include "unicode.h"
#include <algorithm>
#include <iostream>
#include <string>
#include "dictionary.h"
#include "FirstLevelDictionary.h"
#include "DBinaryDictionary.h"
#include "SecondMapDictionary.h"
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
	
	int index = beginIndex;
	string str;
	int size;

	//because the dictionary is already compiled, so it is possible to continue this
	//two character words
	
	int begin = index;
	for(;index<endIndex;index++)
	{
		size = ascWords[index].size();  
		if(size != 6)  //the length of two character chinese word is 6 because the general chinese character in UTF-8 contains 3 byte;
		{
			
			break;
		}
			
	}
	twoWordDic = createSubDictionary(ascWords, begin, index,6);

	if((index - begin) > 1) // maxlength = 2 means the longest word so far contans two characters 
		maxlength = 6;
	
	//three character words
	begin = index;
	for(;index<endIndex;index++)
	{
		//str = ascWords[index];
		size =  ascWords[index].size();  
		if(size != 9)  //the length of three character chinese word is 9 
		{			
			break;
		}
			
	}
	threeWordDic = createSubDictionary(ascWords, begin, index,9);
	if((index - begin) > 1)
		maxlength = 9;

	//four character words
	begin = index;
	for(;index<endIndex;index++)
	{
	
		size = ascWords[index].size() ;  
		if(size != 12)  //the length of four character chinese word is 12
		{			
			break;
		}
			
	}
	fourWordDic = createSubDictionary(ascWords, begin, index,12);
	if((index - begin) > 1)
		maxlength = 12;


	//mult character words
	begin = index;
	for(;index<endIndex;index++)
	{
		size = ascWords[index].size(); 
		maxlength = max(maxlength, size);			
	}
	multWordDic = createSubDictionary(ascWords, begin, index,15);

}


dictionary *FirstLevelDictionary::createSubDictionary(std::string *ascWords, int beginIndex, int endIndex, int length)
{
	dictionary *dic;
	int count = endIndex - beginIndex;
	
	
	if(count < 16) //if the number of words is less than 16, it is more likely using binary search is quicker, so , it using binary search.
	{
		dic = new DBinaryDictionary(ascWords, beginIndex, endIndex, totalCount);
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
	if((length = fourWordDic->search(input,offset,12,mapChar)) != -1) 
		return length;
	if((length= threeWordDic->search(input,offset,9,mapChar)) != -1)
		return length;
	if((length = twoWordDic->search(input,offset,6,mapChar)) != -1)
		return length;
	
	return -1;
}


unsigned FirstLevelDictionary::getMapChar(string input,int offset) //get the unicode value of the second Chinese character of the rest input string
{
	string str = input.substr(offset + 3, 3);
	Utf8Iterator it(str);
	return *it;	
}
