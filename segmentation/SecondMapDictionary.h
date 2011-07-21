#pragma once
#include <string>
#include <map>
#include <vector>
#include "dictionary.h"
#include "DBinaryDictionary.h"

class SecondMapDictionary :
	public dictionary
{
public:
	SecondMapDictionary();
	SecondMapDictionary(string * ascWords, int beginIndex, int endIndex, int totalCount,int length);
public:
	virtual ~SecondMapDictionary();

	map<unsigned,DBinaryDictionary* > subs;
	map<unsigned, string> twoWordSubs;
	string* ascWords;
	int beginIndex;
	int endIndex;
	int count;
	int totalCount;
	int wordLength;

	virtual int size();
	virtual int search(string input,int offset,int count, unsigned mapChar);
	void createDictionary();
	bool isSameIndex(string str, unsigned index);
	unsigned getCharIndex(string str);
	unsigned getCharValue(string str);
};
