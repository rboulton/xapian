#pragma once
#include <string>
#include <vector>
using namespace std;

class dictionary
{
public:
	dictionary();
public:
	virtual ~dictionary();
public:
	virtual int size();
	virtual int search(string input,int offset,int count, unsigned mapChar);
	// void search(string input, vector<string> &output);
};
