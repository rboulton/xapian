#pragma once
#include <string>
#include <vector>
#include <map>
#include "DoubleHashDictionary.h"
#include "dictionary.h"
#include "HashDictionary.h"
#include "BinaryDictionary.h"
#include "util.h"
#include "FrequencyWord.h"


using namespace std;


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
	HashDictionary *familyNameDic;
	HashDictionary *titleDic;
	BinaryDictionary *numberDic;
	FrequencyWord *freWords;

	bool hitFamily;
	int familyIndex;
	int totalNumber;
	void splitString(string input, vector<string> &list_string);
	void createHashDictionaries();
	void getFamilyNameDictionary();
	void getTitleDictionary();
	void getNumberDictionary();
	multimap<unsigned, Name> collectorNames;
	void collectNames(string &input, int beginIndex, int endIndex, vector<string> &output, int end);
	void collectChineseNumbers(string &input, int beginIndex, int endIndex, vector<string> &output, int end);
	void collectLatinWords(string &input, int beginIndex, int endIndex, vector<string> &output);
	bool isChineseDot(string &input, int offset);
	bool isLatinCharacter(char in);
	bool isNumber(char in);
	bool isPunctuate(char in);
	void collectNoFoundDictionary(string &input, int beginIndex, int endIndex);

};
