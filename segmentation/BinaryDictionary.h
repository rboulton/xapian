#pragma once
#include <string>
#include "dictionary.h"
#include "util.h"
using namespace std;

class BinaryDictionary :
	public dictionary
{
public:
	BinaryDictionary(string *ascWords, int count);
	BinaryDictionary(string *ascWords, int beginIndex, int endIndex, int totalCount);
	BinaryDictionary(charArray *ascWords, int beginIndex, int endIndex, int totalCount);
//private:
	
public:
	virtual ~BinaryDictionary();
	string *ascWords;
	charArray *ascInputs;
	int beginIndex;
	int endIndex;
	int count;
	bool hit;
	
	virtual int size();
	virtual int search(string input,int offset,int count, unsigned mapChar);
	
	virtual string getWord(int index);
	int search(string str);
	int compare(string str1,string str2);
};
