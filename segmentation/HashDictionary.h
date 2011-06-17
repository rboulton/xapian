#pragma once
#include "dictionary.h"
#include <map>
#include "Node.h"
#include <string>
#include <vector>
#include "dictionary.h"
using namespace std;


class HashDictionary :
	public dictionary
{
public:
	HashDictionary(void);
	HashDictionary(string dicPath);
	HashDictionary(string *ascWords, int start, int end, int totalCount,int mapIndex);
public:
	~HashDictionary(void);
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
	map<unsigned, Node> mapNodes;
	int size();
	void load();
	bool search(string input);
	//bool compareIndexChar(string, );
	void createSubDictionary();

	dictionary *createSubDictionary(string *ascWords, int startIndex, int endIndex);
	unsigned getIndexChar(string str, int index);
	void addSubDictionary(unsigned hashChar, int beginIndex, int endIndex);

};
