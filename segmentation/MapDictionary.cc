#include "StdAfx.h"
#include "MapDictionary.h"
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
#include <deque>
using namespace std;
using namespace Xapian;
using namespace Unicode;
using namespace Internal;

MapDictionary::MapDictionary(void)
{
}

MapDictionary::~MapDictionary(void)
{
}


int MapDictionary::size(){
	return 0;
}

void MapDictionary::load(){
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	
	char*p = new char[50];
	int i = 0;
	size_t ilength1 = 0, ilength2 = 0;
	size_t ilength = 0;
	size_t wordLength = 0;
	unsigned first;
	
	string str1, str2;
	infile>>str1;
	while(infile>>str2)
	{		
		Utf8Iterator it(str1);
		ilength = it.left();
		first = *it;
		wordLength = 1;
		while(++it != Utf8Iterator() ){
			wordLength++;
		}
	
		
		Node node = mapNodes[first];
		//Word word;
		//word.value = str1;
		bool flag = false;
		if(str2.compare(0,ilength , str1) == 0)
			flag = true;
		
			

		node.setValue(first);
		if(wordLength == 2){
		//	node.list2.push_back(word);
			node.list2[str1] = flag;
			
		}if(wordLength == 3){
			node.list3[str1] = flag;
			
		}if(wordLength == 4){
			node.list4[str1] = flag;
			
		}if(wordLength >= 5){
			node.list5.push_back(str1);
			
		}
		if(node.length < wordLength){
			node.length = wordLength;
		}
		str1 = str2;
	}
}

void MapDictionary::search(string input){
	Utf8Iterator in_utf(input);
	unsigned first, temp;
	string strTemp = "";
	int flag = 0; // whether strTemp contains a unsegmented string
	int X2= 0, X3 = 0,X4 = 0;
	Node node;
	bool successor;
	deque<unsigned> process;
	process.empty();
	size_t maxWordLength;
	string str1, str2,str3,str4;
	while(in_utf != Utf8Iterator() || process.size() != 0){
		X2= X3=X4=0;
		strTemp = str1=str2=str3=str4="";

		//get the first character in the string waiting processing
		if(process.size() != 0){
			first = process.front();
		}else{
			first = *in_utf;
			process.push_back(first);
			++in_utf;
		}

		//check whether this character is in dictionary
		map<unsigned, Node>::iterator first_it =  mapNodes.find(first);
		if(first_it == mapNodes.end()){//if the character is not in the dictionary
			append_utf8(strTemp, first);
			output.push_back(strTemp);
			process.pop_front();
			continue;
		}

		// if the character is in the dictionary
		node = (*first_it).second; //get the info from dictionary
		maxWordLength = node.length;
		if(maxWordLength == 1){//if the largest word beginning with 'first' is a single word, push back to output
			append_utf8(strTemp, first);
			output.push_back(strTemp);
			process.pop_front();
			continue;
		}

		//check whether there is enough character in the process zone
		while(process.size() < maxWordLength && in_utf != Utf8Iterator()){
			temp = *in_utf;
			process.push_back(temp);
			++in_utf;
		}

		if(process.size() < 2){// if it is the end of input
			append_utf8(strTemp, first);
			output.push_back(strTemp);
			process.empty();
			break;
		}
			
		//formed a two-character word
		temp = process.at(1);
		append_utf8(strTemp, first);
		str1 = strTemp;
		append_utf8(strTemp, temp); 
		str2 = strTemp;
		

		//check whether this word exists
		map<string, bool>::iterator second_it = node.list2.find(strTemp);
		if(second_it != node.list2.end()){ 
			successor = (*second_it).second;
			if(successor == false){//if this two-character word is in the dictionary and it has no successor, it confomed a seg
				output.push_back(strTemp);
				process.pop_front();
				process.pop_front();
				break;
			}
			X2 = 1;
		}
			
		if(maxWordLength == 2) //if the max-length word lead by first character is 2, then failed to find the word
		{
			strTemp = "";
			output.push_back(str1);
			process.pop_front();
			continue;
		}

				

		//get the third character, formed a three-character word, check whether it is in dictionary, 
		//and whether it has successor
		if(process.size() < 3){// if it is the end of input
			if(X2 == 1){
				output.push_back(strTemp);
				process.empty();
			}else{
				output.push_back(str1);
				strTemp = "";
				append_utf8(strTemp, first);
				output.push_back(strTemp);	
				process.empty();
			}
			break;
		}
		temp = process.at(2); //get the third character
		append_utf8(strTemp, temp);
		str3 = strTemp;
		//check whether this word exists
		map<string, bool>::iterator third_it = node.list3.find(strTemp);
		if(third_it != node.list3.end()){ 
			successor = (*third_it).second;
			if(successor == false){//if this three-character word is in the dictionary and it has no successor, it confomed a seg
				output.push_back(strTemp);
			//	process.erase(0,2);
				process.erase(process.begin(), process.begin() + 3);
				break;
			}
			X3 = 1;
		}

		if(maxWordLength == 3) //if the max-length word lead by first character is 3, then failed to find the word
		{
			if(X2 == 1){
				output.push_back(str2);
				process.pop_front();
				process.pop_front();
				continue;
			}else{
				output.push_back(str1);
				process.pop_front();
				continue;
			}
		}

		if(process.size() < 4){
			if(X3 == 1){
				output.push_back(strTemp);
				process.empty();
				break;
			}else if(X2 == 1){
				output.push_back(str2);
				strTemp = "";
				append_utf8(strTemp, temp);
				output.push_back(strTemp);
				break;
			}else{
				output.push_back(str1);
				process.pop_front();
				continue;
			}
		}

		temp = process.at(3);// get the fourth number
		append_utf8(strTemp, temp);
		str4 = strTemp;
		//check whether this word exists
		map<string, bool>::iterator fourth_it = node.list4.find(strTemp);
		if(fourth_it != node.list4.end()){
			successor = (*fourth_it).second;
			if(successor == false){//if this four-letter word is in the dictionary, and no successor,
				output.push_back(strTemp);
				process.erase(process.begin(), process.begin() + 4);
				break;
			}
			X4 = 1;
		}

		if(maxWordLength == 4){//if the max-length word lead by first character is 4, then failed to find the word
			if(X3 == 1){
				output.push_back(str3);
				process.erase(process.begin(), process.begin() + 3);
				continue;
			}else if(X2 == 1){
				output.push_back(str2);
				process.pop_front();
				process.pop_front();
				continue;
			}else{
				output.push_back(str1);
				process.pop_front();
				continue;
			}
		}
		
		if(process.size() == 4){
			if(X4 == 1){
				output.push_back(strTemp);
				process.empty();
				break;
			}else if(X3 == 1){
				output.push_back(str3);
				process.erase(process.begin(), process.begin() + 3);
				append_utf8(strTemp, temp);
				output.push_back(strTemp);
				break;				
			}else if(X2 == 1){
				output.push_back(str2);
				process.pop_front();
				process.pop_front();
				continue;
			}else{
				output.push_back(str1);
				process.pop_front();
				continue;
			}
		}

		//deal with word > 4
		for(int i = 4; i < process.size();i++){
			append_utf8(strTemp, process.at(i));
		}
		vector<string> v = node.list5;
		for(int j = 0; j < v.size(); j++){
			
		}		

	}
	
	
}