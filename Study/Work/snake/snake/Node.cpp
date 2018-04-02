#include"Node.h"
#include"NodeManager.h"
Node::Node() :mi_x(-1), mi_y(-1), mp_next(0), mc_shape(' '), mi_direct(0), mb_exist(0) {}
Node::Node(int i_x, int i_y) :mi_x(i_x), mi_y(i_y), mb_exist(0), mi_direct(0), mp_next(0), mc_shape('*') { }
void Node::setPosition(int i_x, int i_y) { mi_x = i_x; mi_y = i_y; }
void Node::movePosition(int i_mx, int i_my) { mi_x += i_mx; mi_y += i_my; }
void Node::setShape(char c_shape) { mc_shape = c_shape; }
void Node::setDirect(int i_direct) { mi_direct = i_direct; }
void Node::setExist(bool b_exist) { mb_exist = b_exist; }
void Node::setSpeed(int i_speed) { mi_speed = i_speed; }
int Node::getSpeed() { return mi_speed; }
bool Node::getExist() { return mb_exist; }
char Node::getShape() { return mc_shape; }
int Node::getDirect() { return mi_direct; }
int Node::getX() { return mi_x; }
int Node::getY() { return mi_y; }
void Node::setPNext(NodeManager* p_next) { mp_next = p_next; }
NodeManager* Node::getPNext() { return mp_next; }
bool Node::getCheck(int i_x, int i_y)
{
	if (mi_x == i_x&&mi_y == i_y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Node::addNode(NodeManager& food)
{
	NodeManager* temp = mp_next;
	food.getNode()->setShape('*');
	food.getNode()->setExist(1);
	NodeManager nt = food;
	food.getNode()->setPosition(mi_x, mi_y);
	food.getNode()->setPNext(temp);
	mp_next = &food;
	mi_x = nt.getNode()->getX();
	mi_y = nt.getNode()->getY();
}