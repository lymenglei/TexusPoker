

//Card.h 

#pragma once

#include "cocos2d.h"
#include "define.h"

USING_NS_CC;
/*
we name the card such as "2.png"

Clubs =  1,    1 ~ 13 梅花
Diamonds,2     14~ 26 方块
Hearts,  3     27~ 39 红桃
Spades,  4     40~ 52 黑桃

we get a random number from 1~52 as num,   we rename the pic_name as a number;

*/
class Card :public Sprite
	//继承自精灵类
{
public:

	static Card* create(const char*);//重载Sprite的构造函数，通过工场模式

	void setCardID(int);// set方法
	void setCardName(char *);
	void setCardFace(int);
	void setCardSuit(int);

	int getCardID();// get方法
	int getCardFace();
	int getCardSuit();
	char * getCardName();
	
private:
	int cardID;     // 0~51 牌所代表的ID
	char * cardName;//  牌的名字
	int cardFace;   //2 ~ 14牌面
	int cardSuit;   //0~3 牌型
};