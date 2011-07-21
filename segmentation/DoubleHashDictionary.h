#pragma once
#include <string>
#include <map>
#include <vector>
#include "dictionary.h"
#include "FirstLevelDictionary.h"

class DoubleHashDictionary 
{
public:
	DoubleHashDictionary(string* ascWords, int totalCount);
	DoubleHashDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount);
public:
	~DoubleHashDictionary();

public:
	int getSize();
	string *ascWords;
	int beginIndex;
	int endIndex;
	int count;
	int totalCount;
	map<unsigned, FirstLevelDictionary*> subDictionaries;

	int size();
	string getWord(int index);
	void createSubDictionaries();
	unsigned getIndexChar(string str);
	unsigned getIndexChar(string str, int offset);
	bool isSameIndex(string strBeginIndex, string str);
	void addSubDictionary(unsigned hashChar, int beginIndex, int endIndex);
	FirstLevelDictionary *createSubDictionary(string *ascWords, int startIndex, int endIndex);
	void search(string input, vector<string> &output);
};
