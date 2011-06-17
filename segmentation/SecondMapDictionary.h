#pragma once
#include "dictionary.h"
#include <string>
#include <map>

class SecondMapDictionary :
	public dictionary
{
public:
	SecondMapDictionary(void);
	SecondMapDictionary(string * ascWords, int beginIndex, int endIndex, int totalCount);
public:
	~SecondMapDictionary(void);

	map<unsigned, string> subs;
	string* ascWords;
	int beginIndex;
	int endIndex;
	int count;
	int totalCount;

	int getSize();
	void load();
	bool search(string input);
	void createDictionary();
	unsigned getCharIndex(string str);

};
