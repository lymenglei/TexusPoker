
#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite{

public:
	static Player* create(const char*);//重载Sprite的构造函数，通过工场模式
	int getDebt();      //获得玩家下注的值
	void addDebt(int);  //玩家加注多少
	void setDebt(int);   //设置玩家的下注
	int getTotal();     //获得玩家总钱数
	void setTotal(int);  //设置玩家总金钱
	void setPhoto(char *);//设置玩家头像图片路径
	char * getPhoto();    //获取玩家头像图片路径
	void setCards(int, int);  //设置玩家的两张底牌
	int getCard01();        //获取玩家第一张底牌
	int getCard02();       //获取玩家第二种底牌
	void setPlayerName(char *);//设置玩家昵称
	bool isOnTable();          //获取玩家是否参与游戏
	void setOnTable(bool);       //设置玩家是否参与游戏

private:

	bool onTable;//是否退出桌面
	int card01, card02;// 两张底牌,1~52
	char * photo;
	char * playerName;
	int debt;//下注的筹码
	int total;// 玩家的总经济

};