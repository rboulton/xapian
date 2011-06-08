#include "StdAfx.h"
#include "Node.h"

Node::Node(void)
{
	length = 1;
}

Node::~Node(void)
{
}

void Node::setValue(unsigned value){
	this->value = value;
}

unsigned Node::getValue(){
	return value;
}
