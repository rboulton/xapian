#pragma once
#include <string>
#include <vector>
#include "DoubleHashDictionary.h"
#include "dictionary.h"

class PrepareDictionaries
{
public:
	PrepareDictionaries();
public:
	~PrepareDictionaries();

	void loadDictionares();
	void search(string input, vector<string> &output);
	string *ascWords;
	DoubleHashDictionary *dic;
	int totalNumber;

};
