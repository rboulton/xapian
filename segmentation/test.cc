// chinese.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include <algorithm>
#include <time.h>
#include "HashDictionary.h"
//#include "unordered_map.h"
//#include "unicode.h"
#include "Node.h"
#include "map"
#include "deque"
//#include "MapDictionary.h"
#include "sstream"
#include "fstream"

using namespace std;
using namespace Xapian;

/*
struct hashCWord{
	size_t operator()(const unicode_char_t& uchar) const
	{
		unsigned long_h = 0;
		
		
		return size_t(long_h);
	}
};

struct equalCWord{
	bool operator()(const Word& _word1, const Word& _word2)const
	{
//		return _word1.getValue() == _word2.getValue();
		return true;
	}
};
*/
const int MAXN = 10000000;
const int MAXS = 60*1024*1024;

void load();
void testDeque();
void loadWithNothing();
void testFread();
void loadTest();
void mmTest();
void loadHash();
void testStringStream();
void testIfstringstream();
void testMoveUtf();
void testStringCompare();

unsigned char* _unicode_to_char(unsigned &uchar,
                                           unsigned char *p);

int _tmain(int argc, _TCHAR* argv[])
{
	//load();
//	testDeque();
	//loadWithNothing();
	//loadTest();
//	testFread();
//	MapDictionary *map = new MapDictionary();
//	map->load();
	loadHash();
	//testStringStream();
	//testIfstringstream();
	//testMoveUtf();
//	testStringCompare();
	return 0;

}

void testStringCompare()
{
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	string str1, str2;
	infile>>str1;
	infile>>str2;
	
	int number = 1000*1000;
	
	clock_t start, finish;
	start = clock();
	while(number--)
	{ 
		 int a = 1;
		a--;
		str1.compare(a * 3, 3,  str2);
	}
		
	finish = clock();
	int i = finish - start;
	cout<<i;
}

void testMoveUtf()
{
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	string str;
	infile>>str;
	int number = 1000*1000;
	clock_t start, finish;
	start = clock();
	while(number--)
	{
		Utf8Iterator it(str);
		*it;
		++it;
	}
		
	finish = clock();
	int i = finish - start;
	cout<<i;
}

void testDeque(){
	deque<string> a;
	a.push_back("str");
	a.push_back("str1");
	a.push_back("str1");
	a.push_back("str1");
	a.push_back("str1");
//	a.erase(0,2);
	size_t i = a.size();
	cout<<i;

}



void testIfstringstream(){
	fstream ifstr( "t-base.dic" );  
  
string line ;  
while( !ifstr.eof() )  
{  
    stringstream lineStr;  
    getline( ifstr, line );  
    lineStr << line.data() ;  
       //use the lineStr   
}  
}

void testStringStream(){
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	clock_t start, finish;
	start = clock();
	string str;
	stringstream stream;
//	map<unsigned, Word> mapWords;
	vector<string> words;
	char a[30] = {0};
	while(infile>>str){
		//words.push_back(str);
		stream << str;
		stream >> a;
		//stream >> 

	}
	finish = clock();
	int i = finish - start;
	cout<<i;

}



void loadWithNothing(){
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	clock_t start, finish;
	start = clock();
	string str;
//	map<unsigned, Word> mapWords;
	vector<string> words;
	while(infile>>str){
		//words.push_back(str);
	}
	finish = clock();
	int i = finish - start;
	cout<<i;


}

void loadTest(){
		
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	clock_t start, finish;
	start = clock();
	char*p = new char[50];
	int i = 0;
	size_t ilength1 = 0, ilength2 = 0;
	size_t ilength = 0;
	size_t wordLength = 0;
//	unsigned first;
	//map<unsigned, Node> mapNodes;
	
	string str1, str2;
	infile>>str1;
	
	while(infile>>str2)
	{		
	//	Utf8Iterator it(str1);
	//	ilength = it.left();
	//	first = *it;
	//	wordLength = ilength / 3;
		
	
		
	//	Node node = mapNodes[first];
		//Word word;
		//word.value = str1;
	//	bool flag = false;
	//	if(str2.compare(0,ilength , str1) == 0)
	//		flag = true;
		
		/*	

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
		*/
	}
	
	finish = clock();
	i = finish - start;
	cout<<i;
}

void mmTest(){
	int numbers[MAXN];
	char buf[MAXS];

//	int fd = open("t-base.dic",O_RDONLY);
//	int len = lseek(fd,0,SEEK_END);
//	char *mbuf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);	
//	analyse(mbuf,len);


}

void testFread(){
	//int numbers[200000];
	char *buf = new char[MAXS];
	memset(buf, 0, sizeof(buf));

	clock_t start, finish;
	start = clock();
//	freopen("x-confucian-family-name.dic","r",stdin);
	//freopen("a.txt","r",stdin);
	freopen("t-base.dic","r",stdin);
	int len = fread(buf,1,MAXS,stdin);
	buf[len]=0;
	cout<<len<<endl;
	//cout<<buf;
//	string *words = new string[23];
	char word[100]={0};
	int n;
	int i = 1;
	//i = sscanf(buf,"%s%n",word,&n);
	int j = 0;
	//string str;
	while( i > 0){
		i  = sscanf(buf,"%s%n",word,&n);
		buf+=n;		
		j++;
	//	cout<<i;
	}

	//int = sizeof
	
//	string a;
//	int num = 10;
//	long j = 0;
//	while(cin>>a){
	//	j++;
//	}
//	cout<<j<<endl;
	/*
	while(num > 0)
	{	cout<<num;
		cin>>a;
		cout<<a<<endl;
		num--;
	}
	*/
//	while(getline(cin,line)){
	//}
//	int len = fread(buf,1,MAXS,stdin);

//	buf[len] = '\0';
	//analyse(buf,len);
	finish = clock();
	 i = finish - start;
	cout<<i<<endl;
//	cout<<buf;
	
}

void loadHash(){
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	clock_t start, finish;
	start = clock();
	string str;
	string *words = new string[230000];
	vector<string> test;
	int i = 0;
	int len;
	while(infile>>str){
		words[i++] = str;
		len = str.length();
		if(len % 3 != 0)
		{
			cout<<i<<endl;
		}
		//test.push_back(str);
	}
	//HashDictionary *hash = new HashDictionary(words, 0, words.);
	int number= sizeof(&words);
	cout<<number<<endl;
	finish = clock();
	i = finish - start;
	cout<<i<<endl;
	
}



void load(){

	/*
	ifstream infile("t-base.dic");
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}
	clock_t start, finish;
	start = clock();
	map<unsigned, Word> mapWords;
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
		int aaa = str2.length();
		char *buff;
		//to_utf8(first, buff);
		//*char *p = static_cast<unsigned char>(first);
		//_unicode_to_char(first, p);
		
		Word word = mapWords[first];
		Wordlist l;
		l.value = str1;
		if(str2.compare(0,ilength , str1) == 0)
			l.flag = 1;
		else
			l.flag = 0;

		word.setValue(first);
		if(wordLength == 2){
			word.p2.push_back(l);
			
		}if(wordLength == 3){
			word.p3.push_back(l);
			
		}if(wordLength == 4){
			word.p4.push_back(l);
			
		}if(wordLength >= 5){
			word.p5.push_back(l);
			
		}
		if(word.length < wordLength){
			word.length = wordLength;
		}
		str1 = str2;
	}
*/


}


