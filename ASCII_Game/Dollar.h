#include "MovableObject.h"

#pragma once
class Dollar : public MovableObject
{
public:
	Dollar(const int& _xPos, const int& _yPos, const char& _moveDir);
	~Dollar();
	void moveObject() override;

};

