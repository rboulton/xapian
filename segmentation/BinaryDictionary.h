#pragma once
#include "dictionary.h"

class BinaryDictionary :
	public dictionary
{
public:
	BinaryDictionary(string *ascWords, int count);
	BinaryDictionary(string *ascWords, int beginIndex, int endIndex, int totalCount);
//private:
	
public:
	virtual ~BinaryDictionary();
	string *ascWords;
	int beginIndex;
	int endIndex;
	int count;
	
	virtual int size();
	string getWord(int index);

	virtual int search(string input,int offset,int count, unsigned mapChar);
	bool search(string str);
	int compare(string str1,string str2);
};
