#pragma once

#include "cocos2d.h"


USING_NS_CC;

class myMenu:public Layer{

public:
	CREATE_FUNC(myMenu);
	bool init();

	void myMenuFun01(Ref * sender);
	void myMenuFun02(Ref * sender);


};