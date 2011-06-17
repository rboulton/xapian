#pragma once
#include "dictionary.h"

class BinaryDictionary :
	public dictionary
{
public:
	BinaryDictionary(string *ascWords, int count);
	BinaryDictionary(string *ascWords, int beginIndex, int endIndex);
//private:
	
public:
	~BinaryDictionary(void);
	string *ascWords;
	int beginIndex;
	int endIndex;
	int count;

	int size();
	void load();
	string getWord(int index);
	bool search(string input);
	int compare(string str1,string str2);
};
