#pragma once
#include <string>
#include <list>
#include "Block.h"
using namespace std;


typedef struct Word{
	int begin;
	int end;
	string value;
	int frequency;

}Word;



class FrequencyWord
{
public:
	FrequencyWord(string &input);
	~FrequencyWord();
public:
	//int *frequency;
	string input;
	list<Block> blocks;
	list<Block> potentialBlocks;
	list<string> collectedWords;
	map<string, int> potentialWords;
	list<Block> results;
	void addBlock(int begin, int end);

	void collect();



	
};

