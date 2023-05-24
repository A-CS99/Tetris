#pragma once
#include "cocos2d.h"
#include "Block.h"

using cocos2d::Vec2;

const int WIDTH = 10, HEIGHT = 24;

struct Pixel {
	bool ext;
	cocos2d::Color3B color;
};

class Board {
private:
	Vec2 pos;
	int width;
	int height;
	Pixel grid[WIDTH][HEIGHT];

public:
	Board(int w = WIDTH, int h = HEIGHT);
	void addBlock(Block* b);
	void removeBlock(Block* b);
	int checkCollaps();
	Pixel getPx(int x, int y);
	~Board();
};
