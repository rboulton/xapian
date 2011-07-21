#pragma once

class Block
{
public:
	Block();
	Block(int begin,int end);
	~Block();
public:
	int begin;
	int end;
};
