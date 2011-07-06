#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <map>
#include "compiledic.h"
#include "unicode.h"


using namespace std;
using namespace Xapian;
using namespace Unicode;


compiledic::compiledic()
{
}

compiledic::~compiledic()
{
}


void compiledic::load()
{
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	
	string str;
	
	
	int i = 0;
	int len;
	ascWords = new string[230000];
	output = new string[230000];
	offset = 0;
	while(infile>>str){
		ascWords[i++] = str;
	}
	totalNumber = i;
}

void compiledic::init()
{
	
	//identify the words starting with same character
	int begin = 0;
	int end = begin + 1;
	unsigned beginMapChar = getIndexChar(ascWords[begin]); //get the first chinese character from beginning word, 
	//unsigned endMapChar;
	string strBeginChar;
	append_utf8(strBeginChar, beginMapChar);

	 // words starts with same character is put into a dictionary
	// dictionary is already sorted
	for(; end < totalNumber; end++)
	{

		if(!isSameIndex(strBeginChar, ascWords[end])) // if the first character is not same , then the words before that is in a sub dictionary
		{
			addSubDictionary(beginMapChar, begin, end); 
			begin = end;
			beginMapChar = getIndexChar(ascWords[end]);
			strBeginChar.clear();
			append_utf8(strBeginChar, beginMapChar);
		}
	}
	addSubDictionary(beginMapChar, begin, totalNumber);
	
}

bool compiledic::isSameIndex(string strIndex, string str)
{
	if(str.compare(0,3,strIndex) == 0)
		return true;
	else 
		return false;
	
}

unsigned compiledic::getIndexChar(string str)
{
	Utf8Iterator it(str);
	return *it;
}

void compiledic::addSubDictionary(unsigned tindex,int beginIndex,int endIndex)
{
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
			two[i++] = str;   //words contains two Chinese character
		}else if(size == 3)
		{
			three[j++] = str; //words contains three Chinese character
		}else if(size == 4)
		{
			four[m++] = str; //words contains four Chinese character
		}else
		{
			mult[n++] = str; //words contains more than four Chinese character
		}

	//	maxlength = max(maxlength, size); 
	} 

	int point;
	for(point = 0; point < i; point++)
	{
		output[offset++] = two[point];
	}
	for(point = 0; point < j; point++)
	{
		output[offset++] =three[point];
	}
	for(point = 0; point < m; point++)
	{
		output[offset++] =four[point];
	}
	for(point = 0; point < n; point++)
	{
		output[offset++] =mult[point];
	}
}

void compiledic::outputDic()
{
	ofstream fout("compiled.txt");
	int i = 0;
	while(i < offset)
	{
		fout<<output[i]<<endl;
		i++;
	}
	fout.close();
}