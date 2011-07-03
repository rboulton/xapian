#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "PrepareDictionaries.h"

using namespace std;

void test1();

int operation;
int classNumber;

int _tmain(int argc, _TCHAR* argv[])
{
	operation = 0;
	classNumber = 0;
	test1();
	cout<<"map numbers:"<<endl;
	cout<<operation<<endl;
	cout<<"class number"<<endl;
	cout<<classNumber<<endl;
}


void test1()
{
	
	ifstream infile("chinese1.txt");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}

	string str;
	string input;
	while(infile>>str){
		input += str;
	}

	PrepareDictionaries * pre = new PrepareDictionaries(); 
	pre->createHashDictionaries();
	//pre->createDoubleHashDictionries();
	vector<string> output;
	pre->searchHash(input, output);
	//pre->searchDoubleHash(input,output);

	vector<string>::iterator iter;
	string strOutput;
	for(iter = output.begin(); iter != output.end(); iter++)
	{
		strOutput += *iter;
		strOutput += "//";
	}

	ofstream fout("3.txt");
    if(!fout)
    {
        fout << "Cannot open output file\n";
        return ;
    } 

	fout<<strOutput;
	fout.close();

	

}


void testHashDictionary()
{

}