
#include "final.h"
#include "GameScene.h"

bool final_layer::init(){
	//调用父类的初始化，若父类初始化失败，则失败
	if (!Layer::init()){
		return false;
	}


	//your codes
	auto sprite = Sprite::create("button01.png");
	this->addChild(sprite);
	sprite->setPosition(300, 300);


	auto screenSize = Director::getInstance()->getWinSize();//获取屏幕尺寸
	
	



	


	return true;

}

Scene * final_layer::createScene()
{
	auto scene = Scene::create();
	auto layer = final_layer::create();
	scene->addChild(layer);
	return scene;
}


