#pragma once
#include"Node.h"
class NodeManager
{
private:
	
public:Node* m_node;
	NodeManager();
	NodeManager(int i_x, int i_y);
	Node* getNode();
	~NodeManager();

};