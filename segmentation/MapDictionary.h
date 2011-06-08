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

public:
	~MapDictionary(void);
	map<unsigned, Node> mapNodes;
	int size();
	void load();
	//virtual Word get(int index) const=0;
	void search(string input); 
	vector<string> output;
};
