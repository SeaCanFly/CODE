#pragma once
class BaseArray
{
private:
	int mi_capacity;
	int* mpi_mem;
protected:
	BaseArray(int i_capacity = 100) :mi_capacity(i_capacity), mpi_mem(new int[mi_capacity]){}
	~BaseArray()
	{
		delete[]mpi_mem;
	}
	void fPut(int i_index, int i_val) { mpi_mem[i_index] = i_val; }
	int fGet(int i_index) { return mpi_mem[i_index]; }
	int getCapacity() { return mi_capacity; }
};
class MyQueue:public BaseArray
{
	int mi_length;
	int mi_curpos;
public:
	MyQueue(int i_capacity) :BaseArray(i_capacity), mi_length(0),mi_curpos(0) {}
	void fEnqueue(int i_val) 
	{ 
		fPut(mi_length, i_val); 
		mi_length++; 
	}
	int fCapacity() { return getCapacity(); }
	int fLength() { return mi_length; }
	int fDequeue()
	{
		int i_temp = fGet(mi_curpos);
		fPut(mi_curpos, 0);
		mi_curpos++;
		mi_length--;
		return i_temp;
	}
};