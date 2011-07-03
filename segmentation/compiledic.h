#pragma once
#include <string>
#include "iostream"
#include "fstream"

using namespace std;

class compiledic
{
public:
	compiledic();
public:
	~compiledic();
	
	string *ascWords;
	string *output;
	int offset;
	int totalNumber;
	void addSubDictionary(unsigned tindex,int beginIndex,int endIndex);
	void load();
	void init();
	void outputDic();
	unsigned getIndexChar(string str);
	bool isSameIndex(string strIndex, string str);
};
