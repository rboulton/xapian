#pragma once
#include "Node.h"
#include "string"
using namespace std;

class dictionary
{
public:
	dictionary(void);
public:
	~dictionary(void);
public:
	virtual int size() const = 0;
	virtual void load() const = 0;
	//virtual Word get(int index) const=0;
	virtual void search(string input) const=0; 
};
