/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "TetrisScene.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <ctime>

USING_NS_CC;

Scene* Tetris::createScene()
{
	return Tetris::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Tetris::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->score = 0;
	this->gameTime = 0;

	std::filesystem::path pdifficulty{ "D:/Courses/Cpp/Projects/Lab02/config/difficulty.txt" };
	std::fstream fsdifficulty{ pdifficulty, std::ios::in | std::ios::out };

	srand(static_cast<unsigned int>(time(nullptr)));
	this->waitingBlocks.push(rand() % 7);
	for (int i = 0; i < 3; i++) {
		int randdiff = rand() % 6 + 1;
		int newType = (this->waitingBlocks.back() + randdiff) % 7;
		this->waitingBlocks.push(newType);
	}
	this->curBlock = new Block{ waitingBlocks.front() };
	this->waitingBlocks.pop();

	this->GameBoard = new Board{ WIDTH, HEIGHT };

	this->waitNode = Node::create();
	this->waitNode->setAnchorPoint(Vec2(0, 0));
	this->waitNode->setPosition(Vec2(WX, WY));
	this->addChild(waitNode, -1);

	auto menu = MyMenu::create();
	menu->setPosition(Vec2(OX + 36 + 408, OY + 36));
	this->addChild(menu, -1);

	auto background = Sprite::create("background.png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(0, 0));
	background->setScale(1.035);
	this->addChild(background, -2);

	this->fallingNode = Node::create();
	this->fallingNode->setAnchorPoint(Vec2(0, 0));
	this->fallingNode->setPosition(Vec2(0, 0));
	this->addChild(fallingNode, -3);

	this->heapNode = Node::create();
	this->heapNode->setAnchorPoint(Vec2(0, 0));
	this->heapNode->setPosition(Vec2(0, 0));
	this->addChild(heapNode, -4);

	auto border = Sprite::create("BorderNew.png");
	border->setAnchorPoint(Vec2(0, 0));
	border->setPosition(Vec2(OX - 4, OY - 4));
	this->addChild(border, -99);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Tetris::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Tetris::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	this->startInterval();

	return true;
}

void Tetris::update(float delta) {
	static int interval = 0;
	if (interval == 0) {
		queue<int> showWaiting = this->waitingBlocks;

		// 展示等待队列
		Pos waitPos{ 0, 0 };
		this->waitNode->removeAllChildren();
		while (!showWaiting.empty()) {
			int waitType = showWaiting.front();
			Block* waitBlock = new Block{ waitType };
			for (const auto& i : Render(*waitBlock)) {
				auto b = Diamond::create();
				b->setAnchorPoint(Vec2(0, 0));
				b->setPosition(Vec2(waitPos.x + i.x * 40, waitPos.y + i.y * 40));
				b->setColor(waitBlock->getColor());
				this->waitNode->addChild(b);
			}
			waitPos.y -= 180;
			showWaiting.pop();
		}
	}

	if (checkHit(Down)) {
		if (checkHit(Out)) {
			this->unscheduleUpdate();
		}
		this->GameBoard->addBlock(curBlock);
		this->fallingNode->removeAllChildren();

		this->curBlock = new Block{ waitingBlocks.front() };
		this->waitingBlocks.pop();
		int randdiff = rand() % 6 + 1;
		int newType = (this->waitingBlocks.back() + randdiff) % 7;
		this->waitingBlocks.push(newType);

		this->score += this->GameBoard->checkCollaps();
		log("Score: %d", this->score);
		this->heapNode->removeAllChildren();
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 10; x++) {
				Pixel curPx = GameBoard->getPx(x, y);
				if (curPx.ext) {
					log("%d %d exists.", x, y);
					auto b = Diamond::create();
					b->setAnchorPoint(Vec2(0, 0));
					b->setPosition(Vec2(OX + x * 40, OY + y * 40));
					b->setColor(Color3B::WHITE);
					this->heapNode->addChild(b);
				}
			}
		}
	}
	else {
		if (interval == 0) {
			this->fallingNode->removeAllChildren();
			for (const auto& i : Render(*curBlock)) {
				int x = i.x;
				int y = i.y;
				auto b = Diamond::create();
				b->setAnchorPoint(Vec2(0, 0));
				b->setPosition(Vec2(OX + x * 40, OY + y * 40));
				b->setColor(curBlock->getColor());
				this->fallingNode->addChild(b);
			}
			this->curBlock->fall(1);
		}
	}

	interval = (interval + 1) % 60;
}

void Tetris::startInterval() {
	this->schedule(CC_SCHEDULE_SELECTOR(Tetris::intervalCallback), 1.0f);
}

void Tetris::intervalCallback(float dt) {
	this->gameTime++;
	log("Time: %d", this->gameTime);
	std::filesystem::path precord{ "D:/Courses/Cpp/Projects/Lab02/config/record.txt" };
	std::fstream fsrecord{ precord, std::ios::out };
	fsrecord << this->score << " " << this->gameTime;
}

void Tetris::stopInterval() {
	this->unschedule(CC_SCHEDULE_SELECTOR(Tetris::intervalCallback));
}

bool Tetris::checkHit(int dir) {
	for (const auto& i : Render(*curBlock)) {
		switch (dir) {
		case Up:
		{
			Block temp = *curBlock;
			temp.rotate();
			for (const auto& i : Render(temp)) {
				int x = temp.getPos().x;
				int y = temp.getPos().y;
				if (x < 0 || x > 9 || y < 0) {
					return true;
				}
				if (this->GameBoard->getPx(x, y).ext) {
					return true;
				}
			}
			break;
		}
		case Left:
		{
			if (i.x - 1 < 0) {
				return true;
			}
			if (this->GameBoard->getPx(i.x - 1, i.y).ext) {
				return true;
			}
			break;
		}
		case Right:
		{
			if (i.x + 1 > 9) {
				return true;
			}
			if (this->GameBoard->getPx(i.x + 1, i.y).ext) {
				return true;
			}
			break;
		}
		case Down:
		{
			if (i.y - 1 < 0) {
				return true;
			}
			if (this->GameBoard->getPx(i.x, i.y - 1).ext) {
				return true;
			}
			break;
		}
		case Out:
			if (i.y > 19) {
				return true;
			}
		default:
			break;
		}
	}
	return false;
}

void Tetris::onKeyPressed(EventKeyboard::KeyCode key, Event* event) {
	switch (key) {
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		if (!checkHit(Up))
			curBlock->rotate();
		break;
	}
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		if (!checkHit(Down))
			curBlock->fall(1);
		break;
	}
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		if (!checkHit(Left))
			curBlock->operator--();
		break;
	}
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		if (!checkHit(Right))
			curBlock->operator++();
		break;
	}
	default:
		break;
	}

	this->fallingNode->removeAllChildren();
	for (const auto& i : Render(*curBlock)) {
		int x = i.x;
		int y = i.y;
		auto b = Diamond::create();
		b->setAnchorPoint(Vec2(0, 0));
		b->setPosition(Vec2(OX + x * 40, OY + y * 40));
		b->setColor(curBlock->getColor());
		this->fallingNode->addChild(b);
	}
}

void Tetris::onKeyReleased(EventKeyboard::KeyCode key, Event* event) {
	switch (key) {
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		break;
	}
	default:
		break;
	}
}

void Tetris::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}