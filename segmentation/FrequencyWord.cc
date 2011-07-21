#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "FrequencyWord.h"
#include "unicode.h"
#include "BinaryDictionary.h"


using namespace std;
using namespace Xapian;

int frequency[22000];

FrequencyWord::FrequencyWord(string &input)
{
	this->input = input;
}

FrequencyWord::~FrequencyWord(void)
{

}

void FrequencyWord::addBlock(int begin, int end)
{
	Block block(begin, end);
	blocks.push_back(block);
	
	string temp = input.substr(begin, end-begin);
	Utf8Iterator it(temp);
	int character;
	while(it !=Utf8Iterator())
	{

		character = *it;
		if(character <= 40895 && character >= 19968)
		{
			frequency[character - 19968]++;
		}
		++it;
	}
}


bool comp(const string& str1, const string& str2)
{
	return str1.compare(str2) < 0;
}



void FrequencyWord::collect()
{
	map<int, int> frequencyCharacters;

	for(int i = 0; i < 22000; i++)
	{
		if(frequency[i] > 2)
			frequencyCharacters.insert(pair<int,int>(i + 19968,frequency[i]));
	}

	list<Block>::iterator it;
	
	Block tempBlock;
	string output;

	for (it=blocks.begin();   it!=blocks.end();   ++it) 
	{ 
		tempBlock = *it;
		string strTemp = input.substr(tempBlock.begin, tempBlock.end - tempBlock.begin);
		Utf8Iterator utf(strTemp);
		int beginIndex = tempBlock.begin;
		int index = beginIndex;
		unsigned character;
		bool hit = false;
	
		while(utf !=Utf8Iterator())
		{

			character = *utf;
			std::map<int,int>::iterator m = frequencyCharacters.find(character);
			if(m != frequencyCharacters.end())
			{
				hit = true;
			}
			beginIndex = index;
			++utf;
			index+= 3;

			while(hit &&utf !=Utf8Iterator())
			{
			
				character = *utf;
			
				std::map<int,int>::iterator m = frequencyCharacters.find(character);
				if(m != frequencyCharacters.end())
				{
					hit = true;
				}
				else
				{
					hit = false;
				}
				++utf;
				index+= 3;

			}

			if(index - beginIndex >= 6)
			{
				Block block(beginIndex, index); 
				potentialBlocks.push_back(block);
				collectedWords.push_back(input.substr(beginIndex, index - beginIndex));	
			
			}
		
		}
	}

	collectedWords.sort(comp);
	vector<string> tempWords;
	string temp, potentialWord;
	int count = 0;
	for(list<string>::const_iterator citer = collectedWords.begin(); citer != collectedWords.end(); ++citer)//looking for potential words;
	{
		count = 0;
		potentialWord = temp = *citer;
		while(temp.compare(potentialWord) == 0 &&citer != collectedWords.end())
		{
			count++;
			++citer;
			temp = *citer;
		}
		if(count>2)
			tempWords.push_back(potentialWord);

	}
	
	int size = tempWords.size();
	string *tempDictionary = new string[size];
	copy(tempWords.begin(), tempWords.end(), tempDictionary);

	//make binaryDictionary
	BinaryDictionary *binaryDictionary = new BinaryDictionary(tempDictionary, size);

	

	//segment the string using word not in dictionary
	Block block;
	for(it=potentialBlocks.begin();   it!=potentialBlocks.end();   ++it) 
	{
		block = *it;
		int begin = block.begin;
		int index = block.begin;
		while(index < block.end)
		{
			int result = binaryDictionary->search(input, index, 1, 0);
			if(result > 0)
			{
				Block tempBlock(index, index + result);
				results.push_back(tempBlock);
				index += result;
			}else
			{
				index += 3;
			}
			
		}
		
	}
	



/*
	for(list<string>::const_iterator citer = collectedWords.begin(); citer != collectedWords.end(); ++citer)
	{
		output += *citer;
		output+="....";
	
	}		

*/			
   

	  ofstream fout("5.txt");
    if(!fout)
    {
        fout << "Cannot open output file\n";
        return ;
    } 

	fout<<output;
	fout.close();

	 size = potentialWords.size();
	cout<<"size"<<size<<endl;

}
