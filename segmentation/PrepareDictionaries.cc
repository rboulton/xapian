#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "unicode.h"
#include "HashDictionary.h"
#include "PrepareDictionaries.h"
#include "HashDictionary.h"
#include "DoubleHashDictionary.h"
using namespace std;
using namespace Xapian;
using namespace Unicode;
using namespace Internal;

PrepareDictionaries::PrepareDictionaries()
{
}

PrepareDictionaries::~PrepareDictionaries()
{
}


void PrepareDictionaries::loadDictionares()
{
	string str;

		
	ascWords = new string[230000];
	FILE *fp;
	if((fp=fopen("compiled-base.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	totalNumber = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		ascWords[totalNumber++] = aa;
	}	
		
}


void PrepareDictionaries::loadHashDictionares()
{
	string str;

		
	ascWords = new string[230000];
	FILE *fp;
	if((fp=fopen("t-base.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	totalNumber = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		ascWords[totalNumber++] = aa;
	}	
		
}

void PrepareDictionaries:: searchDoubleHash(string input, vector<string> &output)
{
	dic->search(input, output);
}

void PrepareDictionaries::searchHash(string input, vector<string> &output)
{
	
	int offset = 0, index = 0;
	unsigned inputLength = input.size();

	
	while(offset < inputLength)  //characters before offset is already segmented
	{
		int result = dict->search(input,offset,1,0);
		if(result == -1)
		{
			output.push_back(input.substr(offset,3));
			offset=offset+3;
		}
		else
		{
			output.push_back(input.substr(offset,result));
			offset += result;
		}
	}
	
	

}

void PrepareDictionaries::splitString(string input, vector<string> &list_string)
{


}


void PrepareDictionaries::createHashDictionaries()
{

	//dic  = new HashDictionary(ascWords, totalNumber);
	dict = new HashDictionary(ascWords, totalNumber);	
}

void PrepareDictionaries::createDoubleHashDictionries()
{

	clock_t start = clock();
	dic = new DoubleHashDictionary(ascWords, totalNumber);
	clock_t next = clock();
	int time = next - start;
	cout<<"map time:";
	cout<<time<<endl;

}