#pragma once
#include<cstring>
#define MAX 25
class NodeManager;
class Node
{
private:
	int mi_x, mi_y;
	int mi_direct;
	int mi_speed;
	bool mb_exist;
	NodeManager* mp_next;
	char mc_shape;
public:
	   Node();
	   Node(int i_x, int i_y);
	void setPosition(int i_x, int i_y);
	void movePosition(int i_mx, int i_my);
	void setShape(char c_shape);
	void setDirect(int i_direct);
	void setExist(bool b_exist);
	void setSpeed(int i_speed);
	int getSpeed();
	bool getExist();
	char getShape();
	int getDirect();
	int getX();
	int getY();
	void setPNext(NodeManager* p_next);
	NodeManager* getPNext();
	bool getCheck(int i_x, int i_y);
	void addNode(NodeManager& food);
};
