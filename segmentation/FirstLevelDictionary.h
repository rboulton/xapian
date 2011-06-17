#pragma once
#include "dictionary.h"



class FirstLevelDictionary :
	public dictionary
{
public:
	FirstLevelDictionary(void);
	FirstLevelDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount);
public:
	~FirstLevelDictionary(void);
	dictionary *twoWordDic;
	dictionary *threeWordDic;
	dictionary *fourWordDic;
	dictionary *MultWordDic;
	int maxlength;
	
	int size() const ;
	void load() const;
	//virtual Word get(int index) const=0;
	bool search(string input); 
	dictionary* createSubDictionary(string* ascWords, int count, int index);
	int max(int a,int b);
};
