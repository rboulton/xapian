#pragma once
#include <string>
#include <vector>
#include "DoubleHashDictionary.h"
#include "dictionary.h"
#include "HashDictionary.h"


class PrepareDictionaries
{
public:
	PrepareDictionaries();
public:
	~PrepareDictionaries();

	void loadDictionares();
	void loadHashDictionares();
	void createDoubleHashDictionries();
	void searchHash(string input, vector<string> &output);
	void searchDoubleHash(string input, vector<string> &output);
	string *ascWords;
	DoubleHashDictionary *dic;
	HashDictionary *dict;
	int totalNumber;
	void splitString(string input, vector<string> &list_string);
	void createHashDictionaries();
};
