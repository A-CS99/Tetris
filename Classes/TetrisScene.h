#pragma once

#include "cocos2d.h"
#include "Block.h"
#include "Board.h"
#include "Diamond.h"
#include "MyMenu.h"
#include <queue>

using std::queue;

// ��Ϸ��ԭ������
const int OX = 140, OY = 340;

// �ȴ���ԭ������
const int WX = 620, WY = 100;

class Tetris : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float deltaTime);
	void startInterval();
	void intervalCallback(float dt);
	void stopInterval();
	void setFallSpeed(double _speed);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

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
	float fallSpeed;
	queue<int> waitingBlocks;
};
