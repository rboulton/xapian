#include "StdAfx.h"
#include "PrepareDictionaries.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "HashDictionary.h"
#include "DoubleHashDictionary.h"
#include "map"
#include "fstream"

using namespace std;
using namespace Xapian;
using namespace Unicode;
using namespace Internal;

PrepareDictionaries::PrepareDictionaries()
{
	loadDictionares();
}

PrepareDictionaries::~PrepareDictionaries()
{
}


void PrepareDictionaries::loadDictionares()
{
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	
	string str;
	
	
	int i = 0;
	int len;
	ascWords = new string[230000];
	while(infile>>str){
		ascWords[i++] = str;
	}
	totalNumber = i;
	dic  = new DoubleHashDictionary(ascWords, totalNumber);
	//DoubleHashDictionary *dhdic = new DoubleHashDictionary(ascWords, totalNumber);
}

void PrepareDictionaries::search(string input, vector<string> &output)
{
	
	dic->search(input, output);
}