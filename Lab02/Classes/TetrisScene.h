#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "Board.h"
#include "Diamond.h"
#include "MyMenu.h"
#include <queue>

using std::queue;

// 游戏区原点坐标
const int OX = 140, OY = 340;

// 等待区原点坐标
const int WX = 620, WY = 100;

class Tetris : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float deltaTime);
	void startInterval();
	void intervalCallback(float dt);
	void stopInterval();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	bool checkHit(int dir);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
	// implement the "static create()" method manually
	CREATE_FUNC(Tetris);
private:
	int score;
	int gameTime;
	Block* curBlock;
	Board* GameBoard;
	Node* fallingNode;
	Node* heapNode;
	Node* waitNode;
	queue<int> waitingBlocks;
};
