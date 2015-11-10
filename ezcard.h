
#pragma once


USING_NS_CC;

class ezCard{
	//easy card，自己定义的类，简单card类，为了方便计算
private:
	int Suit;
	int Face;
	int ID; // 1 ~ 52
public:
	int getSuit();//get方法
	int getFace();
	int getID();
	void setSuit(int);//set方法
	void setFace(int);
	void setID(int);
	ezCard(int);// 构造函数
	
};

//~ezCard();//@大兮瓜 你声明了析构函数，编译器认为这个东西你已经实现了，所以就不给你生成默认析构函数了，但是链接器在链接的时候并没有找到实现
/************************************************************************/
/* >GameScene.obj : error LNK2019: 无法解析的外部符号 "public: __thiscall ezCard::~ezCard(void)"
(??1ezCard@@QAE@XZ)，该符号在函数 "public: void __thiscall GameScene::sort_ezCard_suit(class ezCard *,int)"
(?sort_ezCard_suit@GameScene@@QAEXPAVezCard@@H@Z) 中被引用                                                                     */
/************************************************************************/