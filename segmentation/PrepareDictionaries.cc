#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "HashDictionary.h"
#include "PrepareDictionaries.h"
#include "HashDictionary.h"
#include "DoubleHashDictionary.h"
#include "unicode.h"



using namespace std;
using namespace Xapian;

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
	size_t inputLength = input.size();

	bool hit = false;
	

	int beginIndex = 0;
	int end = 0;
	int begin = 0;
	unsigned temp = 0;
	size_t leftLength;	
	Utf8Iterator it(input);
	
	
	while(offset < inputLength)  //characters before offset is already segmented
	{

		//looking for a begin for a Chinese substring
		while(it != Utf8Iterator()) 
		{
			temp = *it;
			
			if( temp >= 19968 && temp <= 40895) //0x4E00 = 19968 Ox9FBF = 40895
			{
				begin = inputLength - it.left();		
				break;
			}
			++it;
		}	
		
		output.push_back(input.substr(offset, begin - offset));
	
		//looking for a end for a Chinese substring
		while(it != Utf8Iterator()) 
		{
 			temp = *it;
			if(temp < 19968 || temp > 40895)
			{
				end = inputLength - it.left();		
				break;
			}
			++it;
		}

		if(it == Utf8Iterator())
			end = inputLength;


		while(begin < end)
		{
			int result = dict->search(input,begin,1,end);
			if(result == -1)
			{
				
				if(hit == true)
				{
					hit = false;
					beginIndex = begin;
				}		
				
				begin=begin+3;
			}
			else
			{
				
				if(hit == false)
				{
					hit = true;				
					collectNames(input, beginIndex, begin, output,end);				
				}

 				output.push_back(input.substr(begin,result));
			
				begin += result;
				
			}
		}
		if(hit == false)
		{
			hit = true;
			output.push_back(input.substr(beginIndex, end - beginIndex));
			
		}

		offset = end;
	}
	
	

}

void PrepareDictionaries::collectNames(string input, int beginIndex, int endIndex, vector<string> &output, int end)
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
			{
				output.push_back(input.substr(index, result));
				
			}

			//check whether it followed by a title
			int titleResult = titleDic->search(input, index + result, 1, 0);
			if(titleResult > 0) //if a family name followed by a title , it can be recognized be a name
			{
				output.push_back(input.substr(index, result + titleResult));				
				index += result + titleResult;
			}
			else
			{		
				// if there is a character between a family name and a title, then the character between them might be a first name
				titleResult = titleDic->search(input, index + result + 3, 1, 0);
				if(titleResult > 0)
				{
					output.push_back(input.substr(index, result + 3 ));
					output.push_back(input.substr(index, result + 3 + titleResult));
					index += result + 3 + titleResult;
				}else
				{
					//check whether there are two characters between a family name and a title.
					titleResult = titleDic->search(input, index +  result + 6, 1, 0);
					if(titleResult > 0)
					{
						output.push_back(input.substr(index,  result + 6 + titleResult));
						
						index +=  result + 6 + titleResult;
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
							int totalLeft = end - index - result;
							if(totalLeft >= 6)
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
