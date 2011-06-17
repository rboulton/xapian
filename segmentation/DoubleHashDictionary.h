#pragma once
#include "dictionary.h"
#include <string>
#include <map>

class DoubleHashDictionary :
	public dictionary
{
public:
	DoubleHashDictionary(string* ascWords, int totalCount);
	DoubleHashDictionary(string* ascWords, int beginIndex, int endIndex, int totalCount);
public:
	~DoubleHashDictionary(void);

public:
	int getSize();
	string *ascWords;
	int beginIndex;
	int endIndex;
	int count;
	int totalCount;
	map<unsigned, dictionary*> subDictionarys;

	int size();
	void load();
	string getWord(int index);
	void createSubDictionaries();
	bool search(string input);
	//int compare(string str1,string str2);
	unsigned getIndexChar(string str);
	bool isSameIndex(unsigned start, string str);
	void addSubDictionary(unsigned hashChar, int beginIndex, int endIndex);
	dictionary *createSubDictionary(string *ascWords, int startIndex, int endIndex);
};
