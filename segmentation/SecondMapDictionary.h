#pragma once
#include "dictionary.h"
#include <string>
#include <map>
#include <vector>

class SecondMapDictionary :
	public dictionary
{
public:
	SecondMapDictionary();
	SecondMapDictionary(string * ascWords, int beginIndex, int endIndex, int totalCount,int length);
public:
	~SecondMapDictionary();

	map<unsigned, vector<string>> subs;
	map<unsigned, string> twoWordSubs;
	string* ascWords;
	int beginIndex;
	int endIndex;
	int count;
	int totalCount;
	int wordLength;

	int getSize();
	virtual int search(string input,int offset,int count, unsigned mapChar);
	void createDictionary();
	bool isSameIndex(string str, unsigned index);
	unsigned getCharIndex(string str);
	unsigned getCharValue(string str);
};
