#pragma once
#include "Node.h"
#include <string>
#include <vector>
using namespace std;

class dictionary
{
public:
	dictionary();
public:
	~dictionary();
public:
	 int size() const ;
	 virtual int search(string input,int offset,int count, unsigned mapChar);
	// void search(string input, vector<string> &output);
};
