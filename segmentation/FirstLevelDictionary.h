#pragma once
#include "dictionary.h"



class FirstLevelDictionary //:
	//public dictionary
{
public:
	FirstLevelDictionary();
	FirstLevelDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount);
public:
	~FirstLevelDictionary();
	dictionary *twoWordDic;
	dictionary *threeWordDic;
	dictionary *fourWordDic;
	dictionary *multWordDic;
	int maxlength;
	int totalCount;
	
	int size()  ;
	int search(string input,int offset);
	unsigned getMapChar(string input,int offset);
	dictionary* createSubDictionary(string* ascWords, int count, int index);
	int maxValue(int i, int j, int m, int n);
	
};
