#pragma once
class BaseMemory
{
	char* mpc_mem;
protected:
	BaseMemory(int i_size):mpc_mem(new char[i_size]){}
public:
	~BaseMemory()
	{
		delete[]mpc_mem;
	}
	char* getMem() { return mpc_mem; }
	char fRead(int i_index) { return mpc_mem[i_index]; }
};
class ROM :public BaseMemory
{
	int mi_num;
public:
	ROM(int i_size, char* pc_h, int i_num) :BaseMemory(i_size),mi_num(i_num)
	{
		for (int i = 0; i < i_num; i++)
		{
			getMem()[i] = pc_h[i];
		}
	}
};
class RAM :public BaseMemory
{
	int mi_size;
public:
	RAM(int i_size):BaseMemory(i_size),mi_size(i_size){}
	void fWrite(int i_index, char c_val)
	{
		getMem()[i_index] = c_val;
	}
};