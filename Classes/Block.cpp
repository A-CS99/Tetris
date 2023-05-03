#include "Block.h"

using cocos2d::log;

int Block::NOO = 0;

Block::Block() {
	this->pos = Pos{ 4, 21 };
	this->type = I;
	this->dir = Up;
	this->color = new Color3B(0, 255, 255);
	Block::NOO++;
}

Block::Block(int _type) {
	this->dir = Up;
	this->type = _type;
	switch (_type) {
	case I:
		this->pos = Pos{ 3, 20 };
		this->color = new Color3B(0, 255, 255);
		break;
	case O:
		this->pos = Pos{ 4, 20 };
		this->color = new Color3B(Color3B::YELLOW);
		break;
	case J:
		this->pos = Pos{ 3, 20 };
		this->color = new Color3B(Color3B::BLUE);
		break;
	case L:
		this->pos = Pos{ 3, 20 };
		this->color = new Color3B(Color3B::ORANGE);
		break;
	case S:
		this->pos = Pos{ 3, 20 };
		this->color = new Color3B(Color3B::GREEN);
		break;
	case T:
		this->pos = Pos{ 3, 20 };
		this->color = new Color3B(128, 0, 128);
		break;
	case Z:
		this->pos = Pos{ 3, 20 };
		this->color = new Color3B(Color3B::RED);
		break;
	}
	Block::NOO++;
}

Block::Block(double x, double y, int _type) {
	this->pos = Pos{ x, y };
	this->type = _type;
	this->dir = Up;
	switch (_type) {
	case I:
		this->color = new Color3B(0, 255, 255);
		break;
	case O:
		this->color = new Color3B(Color3B::YELLOW);
		break;
	case J:
		this->color = new Color3B(Color3B::BLUE);
		break;
	case L:
		this->color = new Color3B(Color3B::ORANGE);
		break;
	case S:
		this->color = new Color3B(Color3B::GREEN);
		break;
	case T:
		this->color = new Color3B(128, 0, 128);
		break;
	case Z:
		this->color = new Color3B(Color3B::RED);
		break;
	}
	Block::NOO++;
}

Block::Block(const Block& b) {
	this->pos = b.pos;
	this->type = b.type;
	this->color = new Color3B(255, 255, 255);
	*(this->color) = *(b.color);
	this->dir = b.dir;
	Block::NOO++;
}

void Block::setPos(int _x, int _y) {
	this->pos.x = _x;
	this->pos.y = _y;
}

Pos Block::getPos() {
	return this->pos;
}

void Block::setType(int _type) {
	this->type = _type;
	switch (type) {
	case I:
		this->color = new Color3B(0, 255, 255);
		break;
	case O:
		this->color = new Color3B(Color3B::YELLOW);
		break;
	case J:
		this->color = new Color3B(Color3B::BLUE);
		break;
	case L:
		this->color = new Color3B(Color3B::ORANGE);
		break;
	case S:
		this->color = new Color3B(Color3B::GREEN);
		break;
	case T:
		this->color = new Color3B(128, 0, 128);
		break;
	case Z:
		this->color = new Color3B(Color3B::RED);
		break;
	}
}

int Block::getType() {
	return this->type;
}

void Block::setColor(Color3B _color) {
	*(this->color) = _color;
}

Color3B Block::getColor() {
	return *(this->color);
}

void Block::setDir(int _dir) {
	this->dir = _dir;
}

int Block::getDir() {
	return this->dir;
}

int Block::getNOO() {
	return Block::NOO;
}

void Block::fall(double speed) {
	if (this->pos.y > -3.0)
		this->pos.y -= speed;
}

void Block::rotate() {
	this->dir = (this->dir + 1) % 4;
}

Block::~Block() {
	delete this->color;
	Block::NOO--;
}

array<Pos, 4> Render(Block b) {
	double x = b.getPos().x;
	double y = b.getPos().y;
	int type = b.getType();
	int dir = b.getDir();
	array<array<int, 2>, 4> trans;
	array<Pos, 4> res{ Pos{0, 0}, Pos{0, 0}, Pos{0, 0}, Pos{0, 0} };
	switch (type) {
	case I:
		switch (dir) {
		case Up:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 2},
					array<int, 2>{1, 2},
					array<int, 2>{2, 2},
					array<int, 2>{3, 2}
			};
			break;
		case Right:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 3},
					array<int, 2>{2, 2},
					array<int, 2>{2, 1},
					array<int, 2>{2, 0}
			};
			break;
		case Down:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1},
					array<int, 2>{3, 1}
			};
			break;
		case Left:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{1, 3},
					array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0}
			};
			break;
		}
		break;
	case O:
		trans = array<array<int, 2>, 4> {
			array<int, 2>{0, 0},
				array<int, 2>{1, 0},
				array<int, 2>{0, 1},
				array<int, 2>{1, 1}
		};
		break;
	case J:
		switch (dir) {
		case Up:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 2},
					array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1}
			};
			break;
		case Right:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 2},
					array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0}
			};
			break;
		case Down:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 0},
					array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1}
			};
			break;
		case Left:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 0},
					array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0}
			};
			break;
		}
		break;
	case L:
		switch (dir) {
		case Up:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 2},
					array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1}
			};
			break;
		case Right:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 0},
					array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0}
			};
			break;
		case Down:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 0},
					array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1}
			};
			break;
		case Left:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 2},
					array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0}
			};
			break;
		}
		break;
	case S:
		switch (dir) {
		case Up:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{1, 2},
					array<int, 2>{2, 2}
			};
			break;
		case Right:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1},
					array<int, 2>{2, 0}
			};
			break;
		case Down:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 0},
					array<int, 2>{1, 0},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1}
			};
			break;
		case Left:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 2},
					array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0}
			};
			break;
		}
		break;
	case T:
		switch (dir) {
		case Up:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1},
					array<int, 2>{1, 2}
			};
			break;
		case Right:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0},
					array<int, 2>{2, 1}
			};
			break;
		case Down:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1},
					array<int, 2>{1, 0}
			};
			break;
		case Left:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{1, 2},
					array<int, 2>{1, 1},
					array<int, 2>{1, 0},
					array<int, 2>{0, 1}
			};
			break;
		}
		break;
	case Z:
		switch (dir) {
		case Up:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 1},
					array<int, 2>{1, 1},
					array<int, 2>{1, 2},
					array<int, 2>{0, 2}
			};
			break;
		case Right:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{2, 2},
					array<int, 2>{1, 1},
					array<int, 2>{2, 1},
					array<int, 2>{1, 0}
			};
			break;
		case Down:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{0, 1},
					array<int, 2>{1, 0},
					array<int, 2>{1, 1},
					array<int, 2>{2, 0}
			};
			break;
		case Left:
			trans = array<array<int, 2>, 4> {
				array<int, 2>{1, 2},
					array<int, 2>{0, 1},
					array<int, 2>{1, 1},
					array<int, 2>{0, 0}
			};
			break;
		}
		break;
	}
	res = array<Pos, 4>{
		Pos{ x + trans[0][0], y + trans[0][1] },
			Pos{ x + trans[1][0], y + trans[1][1] },
			Pos{ x + trans[2][0], y + trans[2][1] },
			Pos{ x + trans[3][0], y + trans[3][1] }
	};
	return res;
}