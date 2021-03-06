#include "Object.hpp"

#pragma once
class MovableObject : public Object
{
protected:
	int xDir;
	int yDir;

public:
	MovableObject(char _moveDir, int _xPos, int _yPos, char _reprVer, char _reprHor, bool _isVer) : Object{ _xPos, _yPos, _reprVer, _reprHor, _isVer } {
		if (_moveDir == 'L') { this->xDir = -1; this->yDir = 0; }
		else if (_moveDir == 'R') {
			this->xDir = 1;
			this->yDir = 0;
		}
		else if (_moveDir == 'U') {
			this->xDir = 0;
			this->yDir = -1;
		}
		else if (_moveDir == 'D') {
			this->xDir = 0;
			this->yDir = 1;
		}
		else {
			this->xDir = 0;
			this->yDir = 0;
		}
		
	}
	virtual ~MovableObject() {}
	virtual void moveObject() = 0;

	int getXDir() { return this->xDir; }
	void setXDir(int _xDir) { this->xDir = _xDir; }
	int getYDir() { return this->yDir; }
	void setYDir(int _yDir) { this->yDir = _yDir; }
};

