#include "StdAfx.h"
#include "FirstLevelDictionary.h"

FirstLevelDictionary::FirstLevelDictionary(void)
{
}

FirstLevelDictionary::~FirstLevelDictionary(void)
{
}

FirstLevelDictionary::FirstLevelDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount)
{
	maxlength = 0;
	string *two = new string[1000];
	string *three = new string[300];
	string *four = new string[100];
	string *mult = new string[100];
	//int begin = beginIndex;

	//int end = begin + 1;
	int index = beginIndex;
	int i = 0, j =0,m =0,n = 0;
	string str;
	int size;
	for(;index<endIndex;index++)
	{
		str = ascWords[index];
		size = sizeof(str) / 3;
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

	towWordDic  = createSubDictionary(two, i, 2);
	threeWordDic = createSubDictionary(three,j,3);
	fourWordDic = createSubDictionary(four, m, 4);
	multWordDic = createSubDictionary(mult,n,5);
}


int FirstLevelDictionary::max(int a, int b)
{
	if(a >= b)
		return a;
	if(a <b)
		return b;
}

dictionary *FirstLevelDictionary::createSubDictionary(std::string *ascWords, int count, int index)
{
	if(count < 16)
	{
		dictionary *dic = new BinaryDictionary(ascWords, count);
	}
	else
	{
		dictionary *dic = new SecondMapDictionary(ascWords, count);
	}

	return dic;
}

void FirstLevelDictionary::load()
{
	
}

int FirstLevelDictionary::size()
{
	return count;
}

bool FirstLevelDictionary::search(string input)
{
	return true;
}