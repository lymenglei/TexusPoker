
#include "Player.h"

USING_NS_CC;





Player * Player::create(const char* picFileName){

	Player * sprite = new Player();

	if (sprite&& sprite->initWithFile(picFileName))

	{
		sprite->autorelease(); return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;

}


int Player::getDebt(){
	return debt;
}
void Player::setDebt(int n){
	debt = n;
}
void Player::addDebt(int n){
	total = total - n;
	debt = debt + n;
}
int Player::getTotal(){
	return total;
}
void Player::setTotal(int n){
	total = n;
}
void Player::setPhoto(char *c){
	photo = c;
}
char * Player::getPhoto(){
	return photo;
}

void Player::setCards(int c1, int c2){
	card01 = c1;
	card02 = c2;
}
int Player::getCard01(){
	return card01;
}
int Player::getCard02(){
	return card02;
}
void Player::setPlayerName(char *c){
	playerName = c;
}

bool Player::isOnTable(){
	return onTable;
}
void Player::setOnTable(bool b){
	onTable = b;
}