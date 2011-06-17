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
	 int size() const ;
	 void load() const;
	//virtual Word get(int index) const=0;
	 bool search(string input); 
};
