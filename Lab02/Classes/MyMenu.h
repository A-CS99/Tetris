#pragma once
#include<iostream>
#include"cocos2d.h"

class MyMenu : public cocos2d::Menu {
public:
	virtual bool init();
	CREATE_FUNC(MyMenu);
};
