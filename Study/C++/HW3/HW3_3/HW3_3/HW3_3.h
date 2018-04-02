#pragma once
class Random
{
private:
	int num;
public:
	Random();
	int next();
	int nextInRange(int, int);
};