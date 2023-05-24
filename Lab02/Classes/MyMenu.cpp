#include "MyMenu.h"

bool MyMenu::init() {
	cocos2d::Vector<cocos2d::MenuItem*> items;
	auto title = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF("HelloTetris", "fonts/arial.ttf", 50), [&](Ref* sender)
		{ cocos2d::log("Label Callback called!"); });
	title->setPosition(cocos2d::Vec2(250, 700));
	items.pushBack(title);
	auto start = cocos2d::MenuItemImage::create("start.png", "startSelect.png", [&](Ref* sender)
		{ cocos2d::log("Start Callback called!"); });
	start->setAnchorPoint(cocos2d::Vec2(0, 0));
	start->setPosition(cocos2d::Vec2(200, 0));
	items.pushBack(start);

	initWithArray(items);

	return true;
}