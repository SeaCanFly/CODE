#pragma once
#pragma once
#include<string>
using namespace std;
class Object
{
private:
	int m_ipos;
	string m_sshape;
public:
	Object() :m_ipos(-1), m_sshape("") {}
	Object(int pos, string shape) :m_ipos(pos), m_sshape(shape) {}
	void setPosition(int pos, string& rbattle_line)
	{
		this->m_ipos = pos;
		rbattle_line.replace(pos, m_sshape.size(), m_sshape);
	}
	void setShape(string sshape) { this->m_sshape = sshape; }
	int getPos() { return m_ipos; }
	string getShape() { return m_sshape; }
	void setPos(int ipos)
	{
		m_ipos = ipos;
		if (m_ipos == -1)
		{
			m_sshape = "";
		}
	}
	void movePos(int ipos)
	{
		m_ipos += ipos;
		if (m_ipos < 0)
		{
			m_ipos = 0;
		}
		if (m_ipos > 77)
		{
			m_ipos = 77;
		}
	}
};
