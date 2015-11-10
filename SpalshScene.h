
#pragma  once
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class  Spalsh:public Layer
{
public:
	bool init();
	CREATE_FUNC(Spalsh);
	static Scene * createScene();
	Sprite * sprite1;


	//»Øµ÷º¯Êý
	void menuItemImage_callback();
	void jump2game(float);
};