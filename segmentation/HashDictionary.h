#pragma once
#include "dictionary.h"
#include <map>
#include <string>
#include <vector>
#include "dictionary.h"
using namespace std;


class HashDictionary :
	public dictionary
{
public:
	HashDictionary();
	HashDictionary(string dicPath);
	HashDictionary(string *ascWords, int start, int end, int totalCount,int mapIndex);
public:
	~HashDictionary();
private:
	map<unsigned, dictionary*> subDictionarys;

public:
	int start;
	int end;
	int count;
	int totalCount;
	int mapIndex;
	string *ascWords;
	string dictionaryPath;
	//map<unsigned, Node> mapNodes;
	int size();
	virtual int search(string input,int offset);
	//bool compareIndexChar(string, );
	void createSubDictionary();

	dictionary *createSubDictionary(string *ascWords, int startIndex, int endIndex);
	unsigned getIndexChar(string str, int index);
	void addSubDictionary(unsigned hashChar, int beginIndex, int endIndex);

};
