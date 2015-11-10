
#include "SpalshScene.h"
#include "GameScene.h"


bool Spalsh::init(){
	if (!Layer::init()){
		return false;
	}
	// your codes here

	//创建精灵对象方法1，直接使用单个图片作为纹理
	Sprite * s = Sprite::create("dezhoupuke.png");
	this->addChild(s);// 将精灵添加到这个层中
	auto screenSize = Director::getInstance()->getWinSize();//获取屏幕尺寸
	s->setPosition(screenSize.width/2,screenSize.height-100);//设置在屏幕中的位置

	auto sprite1 = Sprite::create("texus_poker.png");
	// 在bird.plist中的图片book.png
	sprite1->setPosition(screenSize.width / 2 - 26, screenSize.height /2+200);//设置在屏幕中的位置
	this->addChild(sprite1);// 将精灵添加到这个层中

	//label,使用系统字体
	auto gametitle = Label::createWithSystemFont("design by MengLei", "Arial", 20);
	gametitle->setPosition(screenSize.width / 2 +140, 50);//设置在屏幕中的位置
	this->addChild(gametitle);// 将字体添加到这个层中
	
	//写一个跳转的函数
	this->scheduleOnce(schedule_selector(Spalsh::jump2game), 2);//延时5秒


	return true;
}

Scene * Spalsh::createScene()
{
	auto scene = Scene::create();
	auto layer = Spalsh::create();
	scene->addChild(layer);
	return scene;
}

void Spalsh::jump2game(float t){
	//回调函数 
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));//以某种动画形式跳转到另外一个场景
}
