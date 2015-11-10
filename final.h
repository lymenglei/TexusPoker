
#pragma  once
#include "cocos2d.h"
#include "GameScene.h"

USING_NS_CC;

class final_layer :public Layer{

public:
	bool init();   //调用父类的初始化，若父类初始化失败，则失败
	CREATE_FUNC(final_layer);     //创建create()函数
	static Scene * createScene();//创建一个场景来包裹当前的图层


};