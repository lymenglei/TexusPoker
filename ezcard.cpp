
#include"cocos2d.h"
#include "define.h"
#include "ezcard.h"

USING_NS_CC;


int ezCard::getSuit(){
	return this->Suit;
}
int ezCard::getFace(){
	return this->Face;
}
int ezCard::getID(){
	return ID;
}

void ezCard::setSuit(int n){
	Suit = n;
}
void ezCard::setFace(int n){
	Face = n;
}
void ezCard::setID(int n){
	ID = n;
}

ezCard::ezCard(int n){

	ID = n;
	if (n == 0){
		this->Face = 0;
		this->Suit = 0;
	}
	 
	// 1  ~ 13 club 梅花
	// 14 ~ 26 dimonds 方块
	// 27 ~ 39 heart 红桃
	// 40 ~ 52 spades 黑桃

	//下面计算花色及点数
	if (0 < n && n <= 13){
		this->Suit = Clubs;
		this->Face = n + 1;
	}
	else
	if (13 < n && n < 27){   //这几个的错误，导致牌的存储出现问题
		this->Suit = Diamonds;
		this->Face = n - 13 + 1;
	}
	else
	if (27 <= n && n < 40){
		this->Suit = Hearts;
		this->Face = n - 26 + 1;
	}
	else
	if (40 <= n && n <= 52){
		this->Suit = Spades;
		this->Face = n - 39 + 1;
	}
}