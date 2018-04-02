#include"NodeManager.h"
NodeManager::NodeManager() { /*m_node = new Node();*/ }
NodeManager::NodeManager(int i_x, int i_y)
{
	m_node = new Node(i_x, i_y);
}
Node* NodeManager::getNode()
{
	return m_node;
}
NodeManager::~NodeManager()
{
	delete m_node;
}