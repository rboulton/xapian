#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "HashDictionary.h"
#include "PrepareDictionaries.h"
#include "HashDictionary.h"
#include "DoubleHashDictionary.h"
using namespace std;

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
		ascWords[totalNumber++] = string(aa, strlen(aa) - 1);
	}	
	dic = new DoubleHashDictionary(ascWords, totalNumber);
		
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
		ascWords[totalNumber++] = string(aa, strlen(aa) - 1);
	}	

	dict = new HashDictionary(ascWords, totalNumber);	
	
	getFamilyNameDictionary();
	getTitleDictionary();
		
}

void PrepareDictionaries::getFamilyNameDictionary()
{
	string str;

		
	string *familyNames = new string[500];
	FILE *fp;
	if((fp=fopen("x-confucian-family-name.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int iFamily = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		familyNames[iFamily++] = string(aa, strlen(aa) - 1);
	}	

	familyNameDic = new HashDictionary(familyNames, iFamily);

}

void PrepareDictionaries::getTitleDictionary()
{
	string str;		
	string *titleWords = new string[500];
	FILE *fp;
	if((fp=fopen("title.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int index = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		titleWords[index++] = string(aa, strlen(aa) - 1);
	}	

	titleDic = new HashDictionary(titleWords, index);

}

void PrepareDictionaries:: searchDoubleHash(string input, vector<string> &output)
{
	dic->search(input, output);
}

void PrepareDictionaries::searchHash(string input, vector<string> &output)
{
	
	int offset = 0, index = 0;
	unsigned inputLength = input.size();

	bool hit = false;
	

	int beginIndex = 0;

	while(offset < inputLength)  //characters before offset is already segmented
	{
		int result = dict->search(input,offset,1,0);
		if(result == -1)
		{
			
			if(hit == true)
			{
				hit = false;
				beginIndex = offset;
			}		
			
			offset=offset+3;
		}
		else
		{
			
			if(hit == false)
			{
				hit = true;				
				collectNames(input, beginIndex, offset, output);				
			}

			output.push_back(input.substr(offset,result));
			offset += result;
			
		}
	}
	
	

}

void PrepareDictionaries::collectNames(string input, int beginIndex, int endIndex, vector<string> &output)
{
	bool hit = false;
	int index = beginIndex;
	while(index < endIndex)
	{
		int result = familyNameDic->search(input, index, 1, 0);
		if(result == -1)
		{
			if(hit == true)
			{
				hit = false;
				beginIndex = index;
			}
			index += 3;
		}
		else 
		{
			if(hit == false)
			{
				hit = true;
				output.push_back(input.substr(beginIndex, index - beginIndex));
			}

			if(result == 6) 
				output.push_back(input.substr(index, result));

			//check whether it followed by a title
			int titleResult = titleDic->search(input, index + result, 1, 0);
			if(titleResult > 0) //if a family name followed by a title , it can be recognized be a name
			{
				output.push_back(input.substr(index, 3 + titleResult));
				index += 3 + titleResult;
			}
			else
			{		
				// if there is a character between a family name and a title, then the character between them might be a first name
				titleResult = titleDic->search(input, index + result + 3, 1, 0);
				if(titleResult > 0)
				{
					output.push_back(input.substr(index, 6 + titleResult));
					index += 6 + titleResult;
				}else
				{
					//check whether there are two characters between a family name and a title.
					titleResult = titleDic->search(input, index + + result + 6, 1, 0);
					if(titleResult > 0)
					{
						output.push_back(input.substr(index, 9 + titleResult));
						index += 9 + titleResult;
					}
					else
					{
						//if there is not a title found			
						int left = endIndex - index - result; 
						if(left > 6)
						{
							output.push_back(input.substr(index, result + 3));
							output.push_back(input.substr(index, result + 6));
						}
						if(left ==  0)
						{
							output.push_back(input.substr(index, result + 6));
							return;
						}else if(left == 3)
						{
							output.push_back(input.substr(index, result + 3));
							return;
						}
						else if(left == 6)
						{
							output.push_back(input.substr(index, result + 3));
							output.push_back(input.substr(index, result + 6));
							output.push_back(input.substr(index + result, 6));
							return;
						}else{
							index += result;
						}
					}

				}

			}
				
		}
	}
	if(hit == false)
	{
		output.push_back(input.substr(beginIndex, index - beginIndex));
	}
	
}



void PrepareDictionaries::splitString(string input, vector<string> &list_string)
{


}


void PrepareDictionaries::createHashDictionaries()
{

	//dic  = new HashDictionary(ascWords, totalNumber);
	
}

void PrepareDictionaries::createDoubleHashDictionries()
{
}
