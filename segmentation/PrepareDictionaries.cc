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
#include "BinaryDictionary.h"
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
	getNumberDictionary();
		
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
void PrepareDictionaries::getNumberDictionary()
{
	string str;		
	string *numbers = new string[30];
	FILE *fp;
	if((fp=fopen("number.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int index = 0;
	char aa[10];
	
	while(fgets(aa, 10, fp) != NULL)
	{
		numbers[index++] = string(aa, strlen(aa) - 1);
	}	

	numberDic = new BinaryDictionary(numbers, index);
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
		
		//output.push_back(input.substr(offset, begin - offset));
		//deal with none Chinese characters
		collectLatinWords(input, offset, begin, output);

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

		beginIndex = begin;
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
					//collectNames(input, beginIndex, begin, output,end);	
					collectChineseNumbers(input, beginIndex, begin, output, end);
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



void PrepareDictionaries::collectNames(string &input, int beginIndex, int endIndex, vector<string> &output, int end)
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

void PrepareDictionaries::collectChineseNumbers(string &input, int beginIndex, int endIndex, vector<string> &output, int end)
{
	bool hit = false;
	
	int index = beginIndex;
	bool result;
	int begin = beginIndex;
	int falseBegin = beginIndex;
	unsigned temp;
	bool dot = false; //one Chinese number should only contain only one dot
	string str;
	while(index < endIndex)
	{
		result = numberDic->search(input, index); //check whether the next character is a Chinese-number character
		if(result) // if it is a Chinese character
		{
			if(hit == false)
			{
				hit = true;
				begin = index;
				if(begin > falseBegin)
				{
					output.push_back(input.substr(falseBegin, begin - falseBegin));
					falseBegin= index;
				}
			}
			index += 3;
		}else
		{
			if(dot)
			{
				hit = false;
				index += 3;
			}

			if(hit)
			{
				dot = isChineseDot(input, index);
				if (dot) 
				{
					result = numberDic->search(input, index + 3);
					if(result == true)
						index += 6;
					else
					{
						
							if(begin == beginIndex) // if the numbers are in first location, then check the characters before it
							{
								while(hit)
								{
									begin -= 3;
									result = numberDic->search(input, begin);
									if(!result)
									{
										if(dot)
										{
											hit = false;
										}
										else
										{
											dot = isChineseDot(input, begin);
											if(!dot)
												hit = false;

										}

									}
								}
							}
						
						output.push_back(input.substr(begin, index - begin));
						hit = false;
						falseBegin = index;
						index += 6;
					}
				}
				else
				{
					output.push_back(input.substr(begin, index - begin));
					hit = false;
					falseBegin = index;
					index += 3;
				}
			}
			else
				index += 3;
		}

	}


	if(hit == true){ // if the string which is not found in dictionary is finished, then search the string followed
					//because some numbers will be in dictionary as other meaning, and it will be segement before collect numbers
					// so we have to search the followed characters.

		while(hit)
		{
			result = numberDic->search(input, index);
			if(!result)
			{
				if(dot)
					hit = false;
				else{
					dot = isChineseDot(input, index);
					if(!dot)
						hit = false;

				}
			}
			index += 3;
		}

		
		index -= 6;
		result = numberDic->search(input, index);

		if(result)
			index += 3;



		hit = true;
		
		if(begin == beginIndex) // if the numbers are in first location, then check the characters before it
		{
			while(hit)
			{
				begin -= 3;
				result = numberDic->search(input, begin);
				if(!result)
				{
					if(dot)
					{
						hit = false;
					}
					else
					{
						dot = isChineseDot(input, begin);
						if(!dot)
							hit = false;
					}
				}
			}
		}
		
		begin += 3;


		output.push_back(input.substr(begin, index - begin));
	}
	else
	{
		output.push_back(input.substr(falseBegin, endIndex - falseBegin));
	}

}

bool PrepareDictionaries::isChineseDot(string &input, int offset)
{
	string str = input.substr(offset, 3);
	Utf8Iterator it(str);
	unsigned temp = *it;
	if(temp == 28857)
		return true;
	else
		return false;
}

void PrepareDictionaries::collectLatinWords(string &input, int beginIndex, int endIndex, vector<string> &output)
{
	char temp;
	int index = beginIndex;
	bool hit = false;
	int dot = -1;
	int begin = beginIndex;
	int falseBegin = beginIndex;
	while(index < endIndex)
	{
		temp = input[index];
		if(isLatinCharacter(temp))
		{
			begin = index;
			if(!hit)
				output.push_back(input.substr(falseBegin,index  - falseBegin));
			hit = true;
			while(hit)
			{
				index++;
				temp = input[index];
				if(!isLatinCharacter(temp))
					hit = false;
			}
			output.push_back(input.substr(begin, index  - begin));
			hit = true;
		}
		else if(isNumber(temp))
		{
			begin = index;
			if(!hit)
				output.push_back(input.substr(falseBegin,index - falseBegin));
			hit = true;
			index++;
			while(hit)
			{
				temp = input[index];
				
				if(numberDic->search(input, index))
				{
					index += 3;
				}else if(isChineseDot(input, index) && (dot < begin))
				{
					dot = index;
					index += 3;

				}
				else if(isNumber(temp)||isPunctuate(temp))
				{
					index++;
				}
				else 
				{
					hit = false;
				}

					
			}

			if(dot == (index - 3))// this means the last character is Chinese dot
				index -= 3;
			
			output.push_back(input.substr(begin, index - begin));
			hit = true;
		}else
		{
			if(hit)
			{
				hit = false;
				falseBegin = index;
			}
			index++;
		}
	}
	
	
}


bool PrepareDictionaries::isPunctuate(char in)
{
	if(in == '-' || in == '/' || in== ',' || in == '.') // these are the possible character in Numbers
		return true;
	else
		return false;
}
bool PrepareDictionaries::isNumber(char in)
{
	if(in >= '0' && in <= '9')
		return true;
	else
		return false;
}
	
bool PrepareDictionaries::isLatinCharacter(char in)
{
	if((in >= 'a' && in <= 'z')
		|| (in >= 'A' && in <= 'Z'))
		return true;
	else
		return false;
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
