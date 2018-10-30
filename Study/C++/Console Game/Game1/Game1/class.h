#pragma once
#include<cstring>
#define MAX 80
class Object
{
private:
	int mi_hp;
	int mi_pos;
	char mca_shape[5];
public:
	Object() :mi_pos(-1), mca_shape(""), mi_hp(1) {}
	Object(int i_pos, char* pc_shape, int i_hp)
	{
		mi_pos = i_pos;
		mi_hp = i_hp;
		strcpy(mca_shape, pc_shape);
	}
	void setHp(int i_hp) { mi_hp = i_hp; }
	int getHp()const { return mi_hp; }
	void setPos(int i_pos) { mi_pos = i_pos; }
	int getPos()const { return mi_pos; }
	void setShape(char* p_shape) { strcpy(mca_shape, p_shape); }
	char* getShape()const { return (char*)mca_shape; }
	void setInScreen(char* p_screen)
	{
		if (mi_pos >= 0 && mi_pos < MAX)
		{
			strncpy(p_screen + mi_pos, mca_shape, strlen(mca_shape));
		}
	}
};