
#pragma once

//定义两种类型，用来表示牌面和大小
typedef enum {
	Two = 2,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
	Ace,

} Face;

typedef enum {
	// "mark" means the smaller one
	Clubs = 0,
	Diamonds,
	Hearts,
	Spades,

} Suit;

#define  DIZHU 100   //底注的值
#define XIAZHU 200   //下注的值

