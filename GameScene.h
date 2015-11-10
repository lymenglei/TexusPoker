


#pragma  once
#include "iostream"
#include "cocos2d.h"
#include "card.h"
#include "Player.h"
#include "ezcard.h"
#include "final.h"
#include "SpalshScene.h"


USING_NS_CC;

class GameScene : public Layer{
	//GameScene是一个图层

public:
	bool init();   //调用父类的初始化，若父类初始化失败，则失败
	CREATE_FUNC(GameScene);     //创建create()函数
	static Scene * createScene();//创建一个场景来包裹当前的图层

	Player* addNewPlayer(char *,int);   //添加一个玩家
	Card* addNewCard(int);   // 添加一张牌
	


	void showTips(float);//显示提示
	//按钮绑定相应的回调函数
	void button_giveUp(Object *);
	void button_xiaZhu(Object*);
	void button_jiaZhu(Object*);

	void button_gameEnd(Object *);
	//返回这个玩家牌面组合的最大值（换算为内部表现形式）
	int checkFinal(Player *);

	//按照扑克牌的花色进行排序
	void sort_ezCard_suit(ezCard *arr, int n);
	//按照扑克牌的牌面大小进行排序。以上两种方法是为了计算牌面的值的
	void sort_ezCard_face(ezCard *arr, int n);



	int getOneNumber();//返回一个数字1 ~ 52，把这个数字设置为牌的ID，在创建一张牌时调用次方法
	int getGaoPai(Player *);
	char * getPaiXing(int);// 返回该数字对应牌型的字符串指针
	//下面是些游戏数据变量

	//在头文件中定义两个玩家的指针
	Player * player_me;
	Player * player01;


	int player_num;//桌上共有多少名玩家
	int card_num;//发了多少张牌
	int debt_num;//目前桌面上的赌注是多少
	int game_round;//第几轮发牌
	int gongGongCard[5];//5张公共牌
	int different_card_array[9];//最多的牌数，保证不同
	int diff_count = 0;//数组中已经存在几个不相同的值
	
	//每个玩家的底牌，暂定有4个玩家（多余的可以不用）， 以后可能用到
	//int player01_card[2];
	//int player02_card[2];
	//int player03_card[2];
	//int player04_card[2];

	void jump2final(float);
	void jump2Game(float);
	void jump2Splash(float);

};