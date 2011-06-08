#pragma once
#include "unicode.h"
#include <map>
#include <string>
#include <vector>
using namespace std;

/*
typedef struct{
	string value;
	int flag;
}Word;
*/

class Node
{
public:
	Node(void);
public:
	~Node(void);
public:
	public:
	unsigned value;
	/*
	vector<Word> list2;
	vector<Word> list3;
	vector<Word> list4;
	vector<Word> list5;
	*/
	map<string, bool> list2;
	map<string, bool> list3;
	map<string, bool> list4;
	vector<string> list5;
	
	size_t length;
public:
	unsigned getValue();
	void setValue(unsigned value);
};
