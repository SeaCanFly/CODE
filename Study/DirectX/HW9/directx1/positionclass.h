////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);
	void GetMove(float&,float&,float&);
	void SetFrameTime(float);
	
	void TurnLeft(bool keyDown);
	void TurnRight(bool keyDown);
	void LookUpward(bool keyDown);
	void LookDownward(bool keyDown);
	
	void MoveForward();
	void MoveBackward();
	void MoveUpward();
	void MoveDownward();
	void MoveLeft();
	void MoveRight();
	float m_rotationX, m_rotationY, m_rotationZ;
private:
	float m_positionX, m_positionY, m_positionZ;
	

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_left, m_right;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
};

#endif
