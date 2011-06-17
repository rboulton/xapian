#pragma once
#include "unicode.h"
#include <map>
#include <string>
#include <vector>
//#include <>
using namespace std;


class Node
{
public:
	Node(void);
public:
	~Node(void);
public:
	public:
	unsigned value;
	
	map<string, bool> list2;
	map<string, bool> list3;
	map<string, bool> list4;
	vector<string> list5;
	
	size_t length;
public:
	unsigned getValue();
	void setValue(unsigned value);
};
