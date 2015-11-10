#include "card.h"


USING_NS_CC;


Card * Card::create(const char* picFileName){

	
	Card * sprite = new Card();

	if (sprite&& sprite->initWithFile(picFileName))

	{
		sprite->autorelease();
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;

}


void Card::setCardFace(int n){
	cardFace = n;
}
void Card::setCardID(int n){
	cardID = n;
}
void Card::setCardName(char * c){
	cardName = c;
}
void Card::setCardSuit(int n){
	cardSuit = n;
}




int Card::getCardFace(){
	return cardFace;
}
int Card::getCardSuit(){
	return cardSuit;
}
int Card::getCardID(){
	return cardID;
}
char* Card::getCardName(){
	return cardName;
}

