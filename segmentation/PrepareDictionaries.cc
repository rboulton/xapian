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
	loadDictionares();
}

PrepareDictionaries::~PrepareDictionaries()
{
}


void PrepareDictionaries::loadDictionares()
{
	string str;

	clock_t start, finish;
	start = clock();	
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
	finish = clock();
	int time = finish - start;
	cout<<"read file time: ";
	cout<<time<<endl;
		
}

void PrepareDictionaries:: searchDoubleHash(string input, vector<string> &output)
{
	clock_t start, finish;
	start = clock();

	dic->search(input, output);
	
	finish = clock();
	int time = finish - start;
	cout<<"search time: ";
	cout<<time<<endl;
}

void PrepareDictionaries::searchHash(string input, vector<string> &output)
{
	clock_t start, finish;
	start = clock();
	int i = 1000;
	while(i--)
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
	finish = clock();
	int time = finish - start;

	cout<<"search time: ";
	cout<<time<<endl;
	

}

void PrepareDictionaries::splitString(string input, vector<string> &list_string)
{


}


void PrepareDictionaries::createHashDictionaries()
{
	clock_t finish = clock();
	
	//dic  = new HashDictionary(ascWords, totalNumber);
	dict = new HashDictionary(ascWords, totalNumber);


	clock_t next = clock();
	int time = next - finish;
	cout<<"create hash time:";
	cout<<time<<endl;
}

void PrepareDictionaries::createDoubleHashDictionries()
{
	clock_t finish = clock();
	
	//dic  = new HashDictionary(ascWords, totalNumber);
	dic = new DoubleHashDictionary(ascWords, totalNumber);


	clock_t next = clock();
	int time = next - finish;
	cout<<"dcitionry time:";
	cout<<time<<endl;
}