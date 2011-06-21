#define NOMINMAX

#include "StdAfx.h"
#include "FirstLevelDictionary.h"
#include "BinaryDictionary.h"
#include "SecondMapDictionary.h"
#include "unicode.h"
#include <algorithm>
using namespace Xapian;

FirstLevelDictionary::FirstLevelDictionary()
{
}

FirstLevelDictionary::~FirstLevelDictionary()
{
}

FirstLevelDictionary::FirstLevelDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount)
{
	maxlength = 0;
	string *two = new string[2000];
	string *three = new string[1000];
	string *four = new string[1000];
	string *mult = new string[1000];
	//int begin = beginIndex;

	//int end = begin + 1;
	int index = beginIndex;
	int i = 0, j =0,m =0,n = 0;
	string str;
	int size;
	/*
		put words in different subdictionary, distinguished by the length of each word.
	*/
	for(;index<endIndex;index++)
	{
		str = ascWords[index];
		size = str.size() / 3;  //divided by 3 because the general chinese character in UTF-8 contains 3 byte;
		if(size == 2)
		{
			two[i++] = str;
		}else if(size == 3)
		{
			three[j++] = str;
		}else if(size == 4)
		{
			four[m++] = str;
		}else
		{
			mult[n++] = str;
		}

		maxlength = max(maxlength, size);
	}

	twoWordDic  = createSubDictionary(two, i, 2);
	threeWordDic = createSubDictionary(three,j,3);
	fourWordDic = createSubDictionary(four, m, 4);
	multWordDic = createSubDictionary(mult,n,5);
}




dictionary *FirstLevelDictionary::createSubDictionary(std::string *ascWords, int count, int length)
{
	dictionary *dic;
	if(count < 16) //if the number of words is less than 16, it is more likely using binary search is quicker, so , it using binary search.
	{
		dic = new BinaryDictionary(ascWords, count);
	}
	else
	{
		dic = new SecondMapDictionary(ascWords, 0,count,count,length);
	}

	return dic;
}



int FirstLevelDictionary::size()
{
	return totalCount;
}



int FirstLevelDictionary::search(string input,int offset)
{
	unsigned mapChar = getMapChar(input, offset);

	int two = twoWordDic->search(input,offset,2,mapChar);
	int three = threeWordDic->search(input,offset,3,mapChar);
	int four = fourWordDic->search(input,offset,4,mapChar);
	int mult = multWordDic->search(input, offset,maxlength, mapChar);
	return maxValue(two, three, four, mult);

}

int FirstLevelDictionary::maxValue(int i, int j, int m, int n)
{
	int temp1 = max(i,j);
	int temp2 = max(m, n);
	return max(temp1, temp2);
}

unsigned FirstLevelDictionary::getMapChar(string input,int offset)
{
	string str = input.substr(offset,9);
	Utf8Iterator it(str);
	++it;
	++it;
	return *it;	
}