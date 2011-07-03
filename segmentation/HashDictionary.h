#pragma once
#include "stdafx.h"
#include <map>
#include <string>
#include <vector>
#include <hash_map>
#include "dictionary.h"
using namespace std;
using namespace stdext;


class HashDictionary :
	public dictionary
{
public:
	HashDictionary();
	HashDictionary(string *ascWords, int totalCount);
	HashDictionary(string *ascWords, int start, int end, int totalCount,int mapIndex);
public:
	~HashDictionary();
private:
	map <unsigned, dictionary*> subDictionarys;
	map<unsigned, string> subs;

public:
	int start;
	int end;
	int count;
	int totalCount;
	int mapIndex;
	bool hit;
	string *ascWords;
	string dictionaryPath;
//	map<unsigned, Node> mapNodes;
	int size();
	string getWord(int index);
	virtual int search(string input,int offset,int count, unsigned mapChar);
	//bool compareIndexChar(string, );
	void createSubDictionary();
	bool isSameIndex(int index, string beginMapChar);
	dictionary *createSubDictionary(string *ascWords, int startIndex, int endIndex);
	unsigned getIndexChar(string str, int index);
	unsigned getIndexChar(string str);
	void addSubDictionary(unsigned hashChar, int beginIndex, int endIndex);

};

