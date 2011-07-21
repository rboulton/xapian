#include "StdAfx.h"
#include "Block.h"

Block::Block()
{
}

Block::Block(int begin,int end)
{
	this->begin = begin;
	this->end = end;
}

Block::~Block(void)
{
}
