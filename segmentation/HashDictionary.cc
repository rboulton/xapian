
#include "stdafx.h"
#include "HashDictionary.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "unordered_map.h"
#include "unicode.h"
#include "Node.h"
#include "map"
using namespace std;
using namespace Xapian;

HashDictionary::HashDictionary(void)
{
	dictionaryPath = "e://dic//t-base.dic";
}

HashDictionary::~HashDictionary(void)
{
}

int HashDictionary::size(){
	return 0;
}

void HashDictionary::load(){	

	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	
	string str;
	char*p = new char[50];
	int i = 0;
	size_t ilength = 0;
	unsigned first;
	unsigned temp;
	/*
	
	while(infile>>str)
	{		
		Utf8Iterator it(str);
		ilength = it.left();
		first = *it;
		Word word = mapWords[first];
		word.setValue(first);
		if(ilength == 2){
			word.p2.words.push_back(str);
			word.p2.length++;
		}if(ilength == 3){
			word.p3.words.push_back(str);
			word.p3.length++;
		}if(ilength == 4){
			word.p4.words.push_back(str);
			word.p4.length++;
		}if(ilength >= 5){
			word.p5.words.push_back(str);
			word.p5.length++;
		}
		word.length++;
	}
	*/
}




/*
Word HashDictionary::get(int index){
	Word word = new Word();
	return new Word();
}
*/

void HashDictionary::search(string input){
	
}