#include "stdafx.h"
#include "PrepareDictionaries.h"
#include <vector>
#include "iostream"
#include "fstream"
#include "string"
using namespace std;

void test1();

#ifndef __WIN32__
int main(int argc, char* argv[])
#else
int _tmain(int argc, _TCHAR* argv[])
#endif
{
	test1();
}


void test1()
{
	ifstream infile("chinese2.txt");
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
	vector<string> output;
	pre->search(input, output);

	

}