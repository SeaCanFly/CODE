#pragma once
class AbstractGate
{
protected:
	bool x, y;
public:
	void set(bool x, bool y) { this->x = x; this->y = y; }
	virtual bool operation() = 0;
};
class ANDGate : public AbstractGate
{
public:
	bool operation()
	{
		if (x == 1 && y == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};
class ORGate :public AbstractGate
{
public:
	bool operation()
	{
		if (x == 1 || y == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
};
class XORGate :public AbstractGate
{
public:
	bool operation()
	{
		if (((x == 1) && (y == 1)) || ((x == 0)&&(y == 0)))
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
};