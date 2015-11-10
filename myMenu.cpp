
#include "myMenu.h"


void myMenu::myMenuFun01(Ref * sender){

	CCLOG("my menu fun 01");
}

void myMenu::myMenuFun02(Ref * sender){
	CCLOG("my menu fun 02");
}

bool myMenu::init(){

	auto scene = Scene::create();
	auto layer = myMenu::create();
	scene->addChild(layer);
	return true;
}