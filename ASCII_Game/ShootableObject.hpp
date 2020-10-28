#pragma once
#include "Object.hpp"
#include"Board.hpp"
#include <functional>
class ShootableObject : public Object
{
private:
	char reprBullet{'o'};
	char shootDir;
	int shootDelay;

public:
	ShootableObject(char _shootDir, int _xPos, int _yPos, int _shootDelay, char _reprVer, char _reprHor, bool _isVer) : Object{ _xPos, _yPos, _reprVer, _reprHor, _isVer }, shootDelay{_shootDelay}, shootDir{ _shootDir } {}
	virtual ~ShootableObject() {}

	void handleBullet(long long mcr, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		if (this->shootDir == 'D' && this->shootDelay == mcr) {
			moveBulletVertically(0, 1, board, checkIfCollision);
		}
		else if (this->shootDir == 'U' && this->shootDelay == mcr) {
			moveBulletVertically(0, -1, board, checkIfCollision);
		}
		else if (this->shootDir == 'R' && this->shootDelay == mcr) {
			moveBulletHorizontally(1, 0, board, checkIfCollision);
		}
		else if (this->shootDir == 'L' && this->shootDelay == mcr) {
			moveBulletHorizontally(-1, 0, board, checkIfCollision);
		}
	}

	void initBullet(int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		if (checkIfCollision(this->xPos + deltaX, this->yPos + deltaY, 'o') == CollisionState::EMPTY_FIELD) {
			board->modifyBoardASCII(this->xPos + deltaX, this->yPos + deltaY, 'o');
		}
	}

	void moveBulletVertically(int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		int y;
		for (y = this->getYPos() + deltaY; board->getBoardASCII().at(y).at(this->getXPos()) != 'o'; y += deltaY) {
			if (board->getBoardASCII().at(y).at(this->getXPos()) == '#') {
				this->initBullet(deltaX, deltaY, board, checkIfCollision);
				return;
			}
		}

		handleCollision(this->getXPos(), y, deltaX, deltaY, board, checkIfCollision);
	}

	void moveBulletHorizontally(int deltaX, int deltaY, Board* board, std::function<CollisionState(int, int, char)> checkIfCollision) {
		int x = this->getXPos() + deltaX;
		while (board->getBoardASCII().at(this->getYPos()).at(x) != 'o') {
			if (board->getBoardASCII().at(this->getYPos()).at(x) == '#') {
				this->initBullet(deltaX, deltaY, board, checkIfCollision);
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
			this->initBullet(deltaX, deltaY, board, checkIfCollision);

			this->drawBullet(this->xPos + deltaX, this->yPos + deltaY);
		}
	}

	
	void drawBullet(int xPos, int yPos) {
		this->changeColor(RED);
		this->gotoxy(xPos, yPos);

		cout << this->reprBullet;
		this->changeColor(WHITE);
	}

	void drawBullet() { cout << this->reprBullet;  }
	char getReprBullet() { return this->reprBullet; }
	char getShootDir() { return this->shootDir;  }

	int getShootDelay() { return this->shootDelay;  }
};

