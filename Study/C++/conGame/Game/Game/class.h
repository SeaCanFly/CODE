#pragma once
#include<string.h>
#define MAX 80
class Object
{
private:
	int mi_hp;
	int mi_pos;
	char mca_shape[5];
public:
	Object() :mi_pos(-1), mca_shape(""), mi_hp(1) {  }
	Object(int i_pos, char* pc_shape, int i_hp) :mi_pos(i_pos), mi_hp(i_hp) { strcpy(mca_shape, pc_shape); }
	void setHp(int i_hp) { mi_hp = i_hp; }
	void setPos(int i_pos) { mi_pos = i_pos; }
	void setShape(char* pc_shape) { strcpy(mca_shape, pc_shape); }
	int getHp() { return mi_hp; }
	int getPos() { return mi_pos; }
	char* getShape() { return mca_shape; }
	void setInScreen(char* pc_screen)
	{
		if (mi_pos >= 0 && mi_pos <= MAX)
		{
			strncpy(pc_screen + mi_pos, mca_shape, strlen(mca_shape));
		}
	}
	void movePos(int i_mpos) 
	{ 
		mi_pos += i_mpos; 
		if (mi_pos < 0)
		{
			mi_pos = 0;
		}
		if (mi_pos > MAX-1-strlen(mca_shape))
		{
			mi_pos = MAX -1- strlen(mca_shape);
		}
	}
};
class Character :public Object
{
private:
	Object a_bullet[MAX];
public:
	Character() :Object() {}
	Character(int i_pos, char* pc_shape, int i_hp) :Object(i_pos, pc_shape, i_hp) {}
	void setBullet(int i_num, Character& r_target,char* pc_screen)
	{
		int i_tpos = r_target.getPos();
		int	i_bpos = a_bullet[i_num].getPos();
		if (i_bpos == -1)return;
		if (i_bpos<0 || i_bpos>MAX)
		{
			a_bullet[i_num].setPos(-1);
			a_bullet[i_num].setShape("");
		}
		for (int i=0;i<MAX;i++)
		{
			if ((i_bpos == r_target.a_bullet[i].getPos())&&(r_target.a_bullet[i].getPos() !=-1))
			{
				a_bullet[i_num].setPos(-1);
				a_bullet[i_num].setShape("");
				r_target.a_bullet[i].setPos(-1);
				r_target.a_bullet[i].setShape("");
				return;
			}
		}
		if (i_bpos == i_tpos)
		{
			a_bullet[i_num].setPos(-1);
			a_bullet[i_num].setShape("");
			r_target.setHp(r_target.getHp() - 1);
			if (r_target.getHp() == 0)
			{
				r_target.setHp(10);
			}
			
		}
		else if (i_bpos > i_tpos)
		{
			a_bullet[i_num].setShape("<");	a_bullet[i_num].movePos(-1)	;
			a_bullet[i_num].setInScreen(pc_screen);
	
		}
		else if (i_bpos < i_tpos)
		{
			a_bullet[i_num].setShape(">");a_bullet[i_num].movePos(1);
			a_bullet[i_num].setInScreen(pc_screen);
			
		}
	}
	Object& getBullet(int i_num)
	{
		return a_bullet[i_num];
	}
};

