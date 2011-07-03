#pragma once
#include "dictionary.h"

class DBinaryDictionary :
	public dictionary
{
public:
	DBinaryDictionary(string *ascWords, int count);
	DBinaryDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount);
public:
	~DBinaryDictionary(void);

	public:
	
	string *ascWords;
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
