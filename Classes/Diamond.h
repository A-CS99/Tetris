#pragma once

#include<iostream>
#include"cocos2d.h"

class Diamond : public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(Diamond);
};
