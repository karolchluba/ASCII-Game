#pragma once
#include "Object.hpp"
#include"Board.hpp"
#include <functional>
class ShootableObject : public Object
{
private:
	bool _isBulletRespawning;
	char _reprBullet{'o'};
	char _shootDir;
	int _shootDelay;

public:
	ShootableObject(char _shootDir, int _xPos, int _yPos, int _shootDelay, char _reprVer, char _reprHor, bool _isVer, bool isBulletRespawning) : Object{ _xPos, _yPos, _reprVer, _reprHor, _isVer }, 
		_shootDelay{ _shootDelay }, _shootDir{ _shootDir }, _isBulletRespawning{isBulletRespawning} {
	
	}

	virtual ~ShootableObject() {}

	void handleBullet(Board* board, std::function<CollisionState (int, int, char)> checkIfCollision) {
		
		
		if (this->_shootDir == 'D') {
			moveBulletVertically(0, 1, board, checkIfCollision);
		}
		else if (this->_shootDir == 'U') {
			moveBulletVertically(0, -1, board, checkIfCollision);
		}
		else if (this->_shootDir == 'R') {
			moveBulletHorizontally(1, 0, board, checkIfCollision);
		}
		else if (this->_shootDir == 'L') {
			moveBulletHorizontally(-1, 0, board, checkIfCollision);
		}
	}

	void initBullet(int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		if (checkIfCollision(this->xPos + deltaX, this->yPos + deltaY, 'o') == CollisionState::EMPTY_FIELD) {
			board->modifyBoardASCII(this->xPos + deltaX, this->yPos + deltaY, 'o');
		}
	}



	void moveBulletVertically(int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		int y = this->getYPos() + deltaY;
		while (board->getBoardASCII().at(y).at(this->getXPos()) != 'o') {
			if (board->getBoardASCII().at(y).at(this->getXPos()) == '#' && this->_isBulletRespawning) {
				this->initBullet(deltaX, deltaY, board, checkIfCollision);
				return;
			}
			else if (board->getBoardASCII().at(y).at(this->getXPos()) == '#' && !this->_isBulletRespawning) {
				return;
			}
			y += deltaY;
		}

		handleCollision(this->getXPos(), y, deltaX, deltaY, board, checkIfCollision);
	}

	void moveBulletHorizontally(int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		int x = this->getXPos() + deltaX;
		while (board->getBoardASCII().at(this->getYPos()).at(x) != 'o') {
			if (board->getBoardASCII().at(this->getYPos()).at(x) == '#' && this->_isBulletRespawning) {
				this->initBullet(deltaX, deltaY, board, checkIfCollision);
				return;
			}
			else if (board->getBoardASCII().at(this->getYPos()).at(x) == '#' && !this->_isBulletRespawning) {
				return;
			}

			x += deltaX;
		}

		handleCollision(x, this->getYPos(), deltaX, deltaY, board, checkIfCollision);
	}

	void handleCollision(int xToHandle, int yToHandle, int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		auto modifyBoardAndScreen = [&]() mutable {
			board->modifyBoardASCII(xToHandle, yToHandle, ' ');
			board->modifyBoardASCII(xToHandle + deltaX, yToHandle + deltaY, 'o');

			this->clearCell(xToHandle, yToHandle);
			this->drawBullet(xToHandle + deltaX, yToHandle + deltaY);
		};

		if (checkIfCollision(xToHandle + deltaX, yToHandle + deltaY, 'o') == CollisionState::EMPTY_FIELD) {
			modifyBoardAndScreen();
		}
		else if (checkIfCollision(xToHandle + deltaX, yToHandle + deltaY, 'o') == CollisionState::DEATH) {
			modifyBoardAndScreen();
		}
		else if ((checkIfCollision(xToHandle + deltaX, yToHandle + deltaY, 'o') == CollisionState::WALL ||
			checkIfCollision(xToHandle + deltaX, yToHandle + deltaY, 'o') == CollisionState::AT)) {

			board->modifyBoardASCII(xToHandle, yToHandle, ' ');
			this->clearCell(xToHandle, yToHandle);

			this->drawBullet(this->xPos + deltaX, this->yPos + deltaY);
		}
	}

	
	void drawBullet(int xPos, int yPos) {
		this->changeColor(RED);
		this->gotoxy(xPos, yPos);

		cout << this->_reprBullet;
		this->changeColor(WHITE);
	}

	void drawBullet() { cout << this->_reprBullet;  }
	char getReprBullet() const { return this->_reprBullet; }

	char getShootDir() const { return this->_shootDir;  }
	void setShootDir(char shootDir) { this->_shootDir = shootDir; }
	int getShootDelay() const { return this->_shootDelay;  }
};

