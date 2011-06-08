#pragma once
#include "dictionary.h"
#include <map>
#include "Node.h"


class HashDictionary :
	public dictionary
{
public:
	HashDictionary(void);
public:
	~HashDictionary(void);

public:
	string dictionaryPath;
	map<unsigned, Node> mapNodes;
	int size();
	void load();
	void search(string input);

};
