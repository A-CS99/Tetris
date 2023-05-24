#include "Board.h"

Board::Board(int w, int h) {
	this->width = w;
	this->height = h;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			grid[x][y].ext = false;
			grid[x][y].color = cocos2d::Color3B::WHITE;
		}
	}
}

void Board::addBlock(Block* b) {
	for (const auto& i : Render(*b)) {
		int x = i.x;
		int y = i.y;
		this->grid[x][y].ext = true;
		this->grid[x][y].color = b->getColor();
	}
}

void Board::removeBlock(Block* b) {
	for (const auto& i : Render(*b)) {
		int x = i.x;
		int y = i.y;
		this->grid[x][y].ext = false;
	}
}

int Board::checkCollaps() {
	int fallDown = 0;
	int lineCount = 0;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			grid[x][y - fallDown] = grid[x][y];
			if (grid[x][y].ext) {
				lineCount++;
			}
		}
		if (lineCount == WIDTH) {
			fallDown++;
		}
		lineCount = 0;
	}
	return fallDown;
}

Pixel Board::getPx(int x, int y) {
	return this->grid[x][y];
}

Board::~Board() {
	delete[] grid;
}