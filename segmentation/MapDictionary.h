#pragma once
#include "dictionary.h"
#include <map>
#include "Node.h"
#include <vector>

class MapDictionary :
	public dictionary
{
public:
	MapDictionary(void);
	MapDictionary(string *ascWords);

public:
	~MapDictionary(void);
	map<unsigned, Node> mapNodes;
	vector<string> acsWords;
	int size();
	void load();
	//virtual Word get(int index) const=0;
	bool search(string input); 
	vector<string> output;
};
