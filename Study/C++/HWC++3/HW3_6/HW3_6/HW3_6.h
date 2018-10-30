#pragma once
class Integer
{
private:
	int n;
public:

	Integer(int num)
	{
		n = num;
	}
	Integer(const char* s)
	{
		while (*s != '\0')
		{
			char* temp = (char*)s;
			if ((*temp - '0' < 0) && (*temp - '9' > 0))
			{
				s++;
			}
			else
			{
				int i = 0, sum = 0;
				while ((*temp - '0' >= 0) && (*temp - '9' <= 0))
				{
					i++;
					temp++;
				}
				while ((*s - '0' >= 0) && (*s - '9' <= 0))
				{
					int t = i-1,mul = 1;
					while (t)
					{
						mul = mul * 10;
						t--;
					}
					sum = sum + (*s - '0')*mul;
					i--;
					s++;
				}
				n = sum;
			}
		}
	}
	bool isEven()
	{
		return (n % 2 == 0) ? true : false;
	}
	void set(int num)
	{
		n = num;
	}
	int get()
	{
		return n;
	}
};
