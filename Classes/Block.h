#pragma once
#include<iostream>
#include<fstream>
#include<filesystem>
#include<array>
#include"cocos2d.h"

using std::array;
using cocos2d::Color3B;

class Pos {
public:
	double x, y;
	Pos() = default;
	Pos(double _x, double _y) {
		x = _x;
		y = _y;
	}
	~Pos() = default;
};

enum bTypes { I, O, J, L, S, T, Z };
enum bDir { Up, Right, Down, Left };

class Block {
private:
	Pos pos;
	int type;
	Color3B* color;
	int dir;
	static int NOO;

public:
	Block();
	Block(int _type);
	Block(double x, double y, int _type);
	Block(const Block& b);
	void setPos(int x, int y);
	Pos getPos();
	void setType(int _type);
	int getType();
	void setColor(Color3B _color);
	Color3B getColor();
	void setDir(int _dir);
	int getDir();

	virtual void fall(double speed = 0.1);
	virtual void rotate();

	static int getNOO();
	~Block();
};

array<Pos, 4> Render(Block b);