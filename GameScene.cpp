
#include "GameScene.h"


bool GameScene::init(){
	if (!Layer::init())
	{
		return false;
	}


	//游戏数据初始化
	card_num = 0;
	debt_num = 0;



	//先添加桌面背景，在最下面
	auto * table = Sprite::create("table.png");
	this->addChild(table);
	auto screenSize = Director::getInstance()->getWinSize();//获取屏幕尺寸  
	table->setPosition(screenSize.width/2,screenSize.height/2-30);
	table->setScale(1.1);//设置缩放级别
	
	//add buttons
	//按钮上的文字后期用ps来制作

	auto giveUpMenuItem = MenuItemImage::create(
		"button01.png",
		"button02.png", CC_CALLBACK_1(GameScene::button_giveUp, this));
	giveUpMenuItem->setPosition(Point(60, 40));

	auto genZhuMenuItem = MenuItemImage::create(
		"button01.png",
		"button02.png", CC_CALLBACK_1(GameScene::button_xiaZhu, this));
	genZhuMenuItem->setPosition(Point(190, 40));

	auto yiLvMenuItem = MenuItemImage::create(
		"button01.png",
		"button02.png", CC_CALLBACK_1(GameScene::button_jiaZhu, this));
	yiLvMenuItem->setPosition(Point(320, 40));

	auto starMenu = Menu::create(giveUpMenuItem, genZhuMenuItem,yiLvMenuItem,NULL);
	starMenu->setPosition(Point::ZERO);
	
	this->addChild(starMenu, 1);

	//按钮上添加文字（暂时的功能，后期完善可以删掉）
	auto button_label01 = Label::createWithSystemFont("giveUp", "Arial", 17);
	button_label01->setPosition(Point(60, 40));
	this->addChild(button_label01,2);
	//按钮上添加文字（暂时的功能，后期完善可以删掉）
	auto button_label02 = Label::createWithSystemFont("xiaZhu", "Arial", 17);
	button_label02->setPosition(Point(190, 40));
	this->addChild(button_label02,2);
	//按钮上添加文字（暂时的功能，后期完善可以删掉）
	auto button_label03 = Label::createWithSystemFont("jiaZhu", "Arial", 17);
	button_label03->setPosition(Point(320, 40));
	this->addChild(button_label03,2);




	// your codes here 
	
	/*

	char str[] = "poker_pic/13.png";
	auto test_card = Sprite::create(str);
	this->addChild(test_card);
	test_card->setPosition(screenSize.width / 2, screenSize.height -400);
	test_card->setScale(0.6);

	auto my_testCard = Card::create("roomgirl.png");  // auto == Card
	my_testCard->setPosition(screenSize.width / 2, screenSize.height - 200);
	my_testCard->setScale(0.6);
	my_testCard->setCardID(23);
	this->addChild(my_testCard);
	CCLOG("my_testCard->ID = %d .", my_testCard->getCardID());//会得到log：my_testCard->ID = 23 .

	*/

	//test_end

	//显示玩家头像，玩家筹码等信息，荷官的片，
	auto roomgirl = Sprite::create("roomgirl.png");
	this->addChild(roomgirl);
	roomgirl->setPosition(screenSize.width/2, screenSize.height-70);
	roomgirl->setScale(1);

	
	player_num = 2;//设置为2名玩家

	//添加游戏玩家(other players)
	auto player01 = addNewPlayer("player01", 50000);

	int my_total = 50000;
	char *my_name = "player_me";
	//添加自己的游戏数据========
	player_me = Player::create("default_player.png");//创建纹理，并且显示在屏幕的正下方
	player_me->setPhoto("default_player.png");
	player_me->setPosition(screenSize.width/2,170);
	player_me->setDebt(0); //set to 0
	player_me->setTotal(my_total);
	player_me->setOnTable(true);
	this->addChild(player_me);
	player01->setPlayerName(my_name);
	player01->setTotal(my_total);

	//show player name
	auto player_me_name = Label::createWithSystemFont(my_name, "Arial", 17);
	player_me_name->setPosition(screenSize.width/2, 215);
	this->addChild(player_me_name);

	//show player total money
	char tmp[9];
	sprintf(tmp, "%d",my_total);
	auto player_me_total = Label::createWithSystemFont(tmp, "Arial", 17);
	player_me_total->setPosition(screenSize.width/2,120);
	this->addChild(player_me_total);


	

	//下底注（后期可以用ps来制作一张图来支持中文）
	//show tips
	auto tips = Sprite::create("show_tips.png");
	tips->setScale(0.3);
	tips->setPosition(screenSize.width / 2, screenSize.height / 2);
	tips->setOpacity(200);
	this->addChild(tips, 0, 100);// set tag 100
	auto tips_label = Label::createWithSystemFont("XiaDiZhu", "SimSun", 30);
	tips_label->setPosition(screenSize.width / 2, screenSize.height / 2);
	tips_label->setColor(ccc3(0, 0, 0));//color black
	this->addChild(tips_label, 0, 101);// set tag 101
	this->scheduleOnce(schedule_selector(GameScene::showTips), 1);//调用回调函数来删掉刚刚创建的tips 
	
	
	player01->addDebt(DIZHU);
	player_me->addDebt(DIZHU);

	debt_num = DIZHU * 2;
	//CCLOG为调试信息
	CCLOG("player01.debt = %d ,total = %d", player01->getDebt(), player01->getTotal());
	CCLOG("player_me.debt = %d ,total = %d", player_me->getDebt(), player_me->getTotal());


	//发底牌（2张底牌）保证不相同
	srand((unsigned)time(NULL)); //初始化随机数种子

	int t1 = getOneNumber();//两名玩家共4张底牌
	int t2 = getOneNumber();
	int t3 = getOneNumber();
	int t4 = getOneNumber();
	CCLOG("DIPAI  == %d %d %d %d",t1,t2,t3,t4);
	player01->setCards(t1,t2);
	player_me->setCards(t3,t4);

	//CCLOG("PLAYER01 c1 = %d, c2 = %d ,PLAYER_ME  c3 = %d, c4 =%d ", player01->getCard01(), player01->getCard02(), player_me->getCard01(), player_me->getCard02());


	//显示玩家得到的底牌（可以添加动画效果）
	char poker_file_name[20]="poker_pic/";
	char temp[9];
	sprintf(temp, "%d", player_me->getCard01());
	strcat(poker_file_name,temp);
	strcat(poker_file_name, ".png");
	//CCLOG("poker_file_name 1 = %s", poker_file_name);
	auto dipai01 = Card::create(poker_file_name);
	dipai01->setRotation(-13);//旋转角度 
	dipai01->setScale(0.5);
	dipai01->setPosition(320, 165);
	this->addChild(dipai01);

	//重新创建一个变量
	char poker_file_name2[20] = "poker_pic/";
	sprintf(temp, "%d", player_me->getCard02());
	strcat(poker_file_name2, temp);
	strcat(poker_file_name2, ".png");
	//CCLOG("poker_file_name 2 = %s", poker_file_name2);
	auto dipai02 = Card::create(poker_file_name2);
	dipai02->setRotation(9);//旋转角度 
	dipai02->setScale(0.5);
	dipai02->setPosition(340, 165);
	this->addChild(dipai02);

	//添加背面的牌：
	auto hand_card_R = Sprite::create("hand_card_back.png");
	hand_card_R->setScale(0.6);
	hand_card_R->setPosition(22, 470);
	this->addChild(hand_card_R);

	//刚发过底牌，设置一个标签，来定义玩到了什么进度
	game_round = 1;//刚发过底牌，设置为1
	
	//若不弃牌，则下注，下注之后可选加注


	//庄家下注，玩家跟注？加注？

	//发第一张公共牌

	//发第二张公共牌

	//...

	//...直到发最后一张公共牌，是否加注？判断游戏输赢
	
	//以上内容写在了按钮中，通过读取变量值来知道是第几个回合

	return true;//init函数执行成功，返回真
}


//添加一个新玩家
Player* GameScene::addNewPlayer(char *name,int n){
	//初始化头像，姓名，及总金钱

	player01 = Player::create("men_head3.png");
	player01->setPhoto("men_head3.png");
	player01->setPosition(50, 500);
	player01->setTotal(n);
	player01->setDebt(0);
	player01->setOnTable(true);
	this->addChild(player01);

	player01->setPlayerName(name);
	player01->setTotal(n);

	//show player name
	auto player01_name = Label::createWithSystemFont(name, "Arial", 17);
	player01_name->setPosition(50,550);
	this->addChild(player01_name);

	//show player total money
	char tmp[9];
	sprintf(tmp, "%d", n);
	auto player01_total = Label::createWithSystemFont(tmp, "Arial", 17);
	player01_total->setPosition(50, 450);
	this->addChild(player01_total);

	return player01;
}

//产生一张新牌
Card* GameScene::addNewCard(int n){
	//产生一张牌，牌的信息包括花色和牌面大小

	char tmp[9];
	sprintf(tmp, "%d", n);
	auto card01 = Card::create(tmp);//图片文件名称保存为数字形式
	//下面计算花色及点数
	if (0 < n && n <= 13){
		card01->setCardFace(n + 1);
		card01->setCardSuit(Clubs);
	}else
	if (13 < n && n < 27){
		card01->setCardFace(n - 13 + 1);
		card01->setCardSuit(Diamonds);
	}else
	if (27 <= n && n < 40){
		card01->setCardFace(n -26 + 1);
		card01->setCardSuit(Hearts);
	}else
	if (40 <= n && n <= 52){
		card01->setCardFace(n -39 + 1);
		card01->setCardSuit(Spades);
	}

	card01->setCardID(n);
	card01->setCardName(tmp);  //useless

	card_num++;//产生一个数，表示多了一张牌
	return card01;
}


int GameScene::getOneNumber(){
	//get a number between 1 and 52
	//随机数的种子要放到函数中，不能放在这个函数里，本程序放到了init()中
	// [a,b]  ==(rand() % (b-a+1))+ a  == 1~52
	int num = rand() % 53  ;
	for (int i = 0; i < diff_count; i++){
		if (num == different_card_array[i] || num == 0){  //如果出现了相同的数据，则再返回一个值，直到不重复
			return getOneNumber();
		}
	}
	different_card_array[diff_count] = num;//产生的新数字添加到数组
	diff_count++;
	return num;
}


Scene * GameScene::createScene(){
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}


//回调函数

void GameScene::showTips(float t){
	this->removeChildByTag(100, true);
	this->removeChildByTag(101, true);
}


//button !
void GameScene::button_giveUp(Object * pSender){
	



	auto screenSize = Director::getInstance()->getWinSize();//获取屏幕尺寸




	//CCLOG("button give up touched !");
	if (player_num > 1){
		player_num = player_num - 1;
	}
	else{
		CCLOG("==error==,player num <1 !");// 玩家数必须大于等于1
	}
	//CCLOG("player num = %d", player_num);
	player_me->setOnTable(false);

	//决定是否弃牌，若玩家数<=1，则游戏结束
	// 先写玩家的操作，电脑AI的操作最后在写
	if (player_num < 2){
		//game over 
		Player * p1, *p2; // p1 win ,p2 lose
		if (player_me->isOnTable() == false){
			p1 = player01;
			p2 = player_me;
		}
		else{// 不是我赢就是电脑赢
			p1 = player_me;
			p2 = player01;
		}

		//显示玩家的牌，并且重新开始游戏，谁获胜
		//CCLOG("create GameEnd Sprite");
		auto GameEnd = Sprite::create("show_tips.png");
		GameEnd->setPosition(screenSize.width / 2, screenSize.height / 2);
		this->addChild(GameEnd,7);

		auto giveup_title = Label::createWithSystemFont("some player give up", "Arial", 26);
		giveup_title->setPosition(400, 440);
		giveup_title->setColor(ccc3(0, 0, 0));
		GameEnd->addChild(giveup_title);



		//button in gameover游戏结束按钮！！！
		auto reGame = MenuItemImage::create(
			"button01.png",
			"button02.png", CC_CALLBACK_1(GameScene::button_gameEnd, this));
		reGame->setPosition(400, 30);

		auto reGameMenu = Menu::create(reGame, NULL);
		reGameMenu->setPosition(Point::ZERO);

		GameEnd->addChild(reGameMenu, 1);

		//按钮上添加文字（暂时的功能，后期完善可以删掉）
		auto button_label01 = Label::createWithSystemFont("ReStart", "Arial", 17);
		button_label01->setPosition(Point(48, 20));
		reGame->addChild(button_label01, 2);


		//显示弃牌之后，两个玩家的牌都是什么？谁赢？
		/////赢家
		auto winner = Label::createWithSystemFont("Winner", "Arial", 20);
		winner->setPosition(200, 350);
		winner->setColor(ccc3(0, 0, 0));
		GameEnd->addChild(winner);
		
		auto winner_pic = Sprite::create(p1->getPhoto());
		winner_pic->setPosition(200, 280);
		GameEnd->addChild(winner_pic);

		//2张底牌，n张公共牌,n可以为0
		char poker_file_name[20] = "poker_pic/";
		char temp[9];
		sprintf(temp, "%d", p1->getCard01());
		strcat(poker_file_name, temp);
		strcat(poker_file_name, ".png");// error some time
		CCLOG("SOME_TIME_ERROR_LINE@367____poker file name = %s", poker_file_name);
		auto p1_1 = Sprite::create(poker_file_name);
		p1_1->setPosition(280, 280);
		p1_1->setScale(0.5);
		GameEnd->addChild(p1_1);

		char poker_file_name2[20] = "poker_pic/";
		sprintf(temp, "%d", p1->getCard02());
		strcat(poker_file_name2, temp);
		strcat(poker_file_name2, ".png");
		auto p1_2 = Sprite::create(poker_file_name2);
		p1_2->setPosition(300, 280);
		p1_2->setScale(0.5);
		GameEnd->addChild(p1_2);



		//////输家
		auto loser = Label::createWithSystemFont("Loser", "Arial", 20);
		loser->setPosition(200, 170);
		loser->setColor(ccc3(0, 0, 0));
		GameEnd->addChild(loser);

		auto loser_pic = Sprite::create(p2->getPhoto());
		loser_pic->setPosition(200, 100);
		GameEnd->addChild(loser_pic);
		
		//dipai 2
		char poker_file_name3[20] = "poker_pic/";
		sprintf(temp, "%d", p2->getCard01());
		strcat(poker_file_name3, temp);
		strcat(poker_file_name3, ".png");
		auto p2_1 = Sprite::create(poker_file_name3);
		p2_1->setPosition(280, 100);
		p2_1->setScale(0.5);
		GameEnd->addChild(p2_1);

		char poker_file_name4[20] = "poker_pic/";
		sprintf(temp, "%d", p2->getCard02());
		strcat(poker_file_name4, temp);
		strcat(poker_file_name4, ".png");
		auto p2_2 = Sprite::create(poker_file_name4);
		p2_2->setPosition(300, 100);
		p2_2->setScale(0.5);
		GameEnd->addChild(p2_2);



		//显示一遍公共牌？ 
		Point p[5];
		p[0] = Point(400, 190);
		p[1] = Point(450, 190);
		p[2] = Point(500, 190);
		p[3] = Point(550, 190);
		p[4] = Point(600, 190);
		CCLOG("card_num = %d", card_num);
		for (int i = 0; i < card_num ; i++){ //减掉底牌就是公共牌数  ???肯定是哪里不对了，目前程序对

			char poker_file_name5[20] = "poker_pic/";
			sprintf(temp, "%d", gongGongCard[i]);
			strcat(poker_file_name5, temp);
			strcat(poker_file_name5, ".png");
			auto gonggongcard = Sprite::create(poker_file_name5);
			gonggongcard->setScale(0.7);
			gonggongcard->setPosition(p[i]);
			GameEnd->addChild(gonggongcard);
			CCLOG("giveup_gonggong %d = %s", i, poker_file_name5);
		}

	}//end IF



	//game end


}
void GameScene::button_xiaZhu(Object * pSender){
	//CCLOG("button jiazhu touched !");
	//当点击了下注，则所有玩家的经济变化（AI默认为下注）
	//第一轮下注后，则发三张牌，
	if (game_round == 1){
		gongGongCard[0] = getOneNumber();
		gongGongCard[1] = getOneNumber();
		gongGongCard[2] = getOneNumber();

		card_num = card_num + 3;

		//CCLOG("gonggong card 0 1 2 = %d %d %d", gongGongCard[0], gongGongCard[1], gongGongCard[2]);
		//创建3张牌并显示
		char poker_file_name[20] = "poker_pic/";
		char  temp[9];
		sprintf(temp, "%d", gongGongCard[0]);
		strcat(poker_file_name, temp);
		strcat(poker_file_name, ".png");
		auto gonggong01 = Sprite::create(poker_file_name);
		gonggong01->setPosition(80, 370);
		gonggong01->setScale(0.6);
		this->addChild(gonggong01);

		char poker_file_name1[20] = "poker_pic/";
		
		sprintf(temp, "%d", gongGongCard[1]);
		strcat(poker_file_name1, temp);
		strcat(poker_file_name1, ".png");
		auto gonggong02 = Sprite::create(poker_file_name1);
		gonggong02->setPosition(160, 370);
		gonggong02->setScale(0.6);
		this->addChild(gonggong02);

		char poker_file_name2[20] = "poker_pic/";
		
		sprintf(temp, "%d", gongGongCard[2]);
		strcat(poker_file_name2, temp);
		strcat(poker_file_name2, ".png");
		auto gonggong03 = Sprite::create(poker_file_name2);
		gonggong03->setPosition(240, 370);
		gonggong03->setScale(0.6);
		this->addChild(gonggong03);

		game_round = 2;//设置为第一轮已经结束
		player01->addDebt(XIAZHU);//下注200
		player_me->addDebt(XIAZHU);
		return;
	}
	//第二轮下注后,发一张

	if (game_round == 2){
		gongGongCard[3] = getOneNumber();
		card_num++;
		//CCLOG("gong gong card [3] = %d", gongGongCard[3]);
		char poker_file_name[20] = "poker_pic/";
		char  temp[9];
		sprintf(temp, "%d", gongGongCard[3]);
		strcat(poker_file_name, temp);
		strcat(poker_file_name, ".png");
		auto gonggong04 = Sprite::create(poker_file_name);
		gonggong04->setPosition(320, 370);
		gonggong04->setScale(0.6);
		this->addChild(gonggong04);

		game_round = 3;
		player01->addDebt(XIAZHU);//下注200
		player_me->addDebt(XIAZHU);
		return;
	}
	//最后一轮下注后，发一张
	if (game_round == 3){
		gongGongCard[4] = getOneNumber();
		card_num++;
		//CCLOG("gong gong card [4] = %d", gongGongCard[4]);
		char poker_file_name[20] = "poker_pic/";
		char  temp[9];
		sprintf(temp, "%d", gongGongCard[4]);
		strcat(poker_file_name, temp);
		strcat(poker_file_name, ".png");
		auto gonggong05 = Sprite::create(poker_file_name);
		gonggong05->setPosition(400, 370);
		gonggong05->setScale(0.6);
		this->addChild(gonggong05);

		game_round = 4;
		player01->addDebt(XIAZHU);//下注200
		player_me->addDebt(XIAZHU);
		return;
	}
	//牌发完后，还可以下注


	if (game_round == 4){
		int  me = checkFinal(player_me);// just test
		int ai = checkFinal(player01);

		CCLOG("check final Player_me = %d", me);
		CCLOG("check final Player_01 = %d", ai);

		//写一个跳转的函数
		//this->scheduleOnce(schedule_selector(GameScene::jump2final), 2);//延时5秒 



		//===============================================================
		auto screenSize = Director::getInstance()->getWinSize();//获取屏幕尺寸
		Player * p1, *p2; // p1 win ,p2 lose

		


		if (me == ai && me<100 && ai<100){
			//两种牌型都相同
			//则继续比较牌面大小
			if (getGaoPai(player01) < getGaoPai(player_me)){
				p1 = player_me;
				p2 = player01;
			}
			else{
				p1 = player01;
				p2 = player_me;
			}
			
		}
		else{
			if (me > 100 && ai > 100){
				//若两个都是高牌
				if (me < ai){
					p1 = player01;
					p2 = player_me;
				}
				else{//  问题？  高牌都相同时无法判断谁赢，应该事平局，但是默认时有输赢的
					p1 = player_me;
					p2 = player01;
				}
			}
			else{//有对应的牌型，或者高牌，最小的牌型最大
				if (me < ai){
					p1 = player_me;
					p2 = player01;
				}
				else{
					p1 = player01;
					p2 = player_me;
				}
			}
		}
		//game over 
			
			

			//显示玩家的牌，并且重新开始游戏，谁获胜
			//CCLOG("create GameEnd Sprite");
			auto GameEnd = Sprite::create("show_tips.png");
			GameEnd->setPosition(screenSize.width / 2, screenSize.height / 2);
			this->addChild(GameEnd, 7);

			//button in gameover游戏结束按钮！！！
			auto reGame = MenuItemImage::create(
				"button01.png",
				"button02.png", CC_CALLBACK_1(GameScene::button_gameEnd, this));
			reGame->setPosition(400,30);

			auto reGameMenu = Menu::create(reGame,NULL);
			reGameMenu->setPosition(Point::ZERO);

			GameEnd->addChild(reGameMenu, 1);

			//按钮上添加文字（暂时的功能，后期完善可以删掉）
			auto button_label01 = Label::createWithSystemFont("ReStart", "Arial", 17);
			button_label01->setPosition(Point(48,20));
			reGame->addChild(button_label01, 2);

			///============================================================
			auto giveup_title = Label::createWithSystemFont("game over!", "Arial", 26);
			giveup_title->setPosition(400, 440);
			giveup_title->setColor(ccc3(0, 0, 0));
			GameEnd->addChild(giveup_title);


			//显示弃牌之后，两个玩家的牌都是什么？谁赢？
			/////赢家
			auto winner = Label::createWithSystemFont("Winner", "Arial", 20);
			winner->setPosition(200, 350);
			winner->setColor(ccc3(0, 0, 0));
			GameEnd->addChild(winner);

			auto winner_pic = Sprite::create(p1->getPhoto());
			winner_pic->setPosition(200, 280);
			GameEnd->addChild(winner_pic);

			//2张底牌，n张公共牌,n可以为0
			char poker_file_name[20] = "poker_pic/";
			char temp[9];
			sprintf(temp, "%d", p1->getCard01());
			strcat(poker_file_name, temp);
			strcat(poker_file_name, ".png");// error some time
			CCLOG("SOME_TIME_ERROR_LINE@367____poker file name = %s", poker_file_name);
			auto p1_1 = Sprite::create(poker_file_name);
			p1_1->setPosition(280, 280);
			p1_1->setScale(0.5);
			GameEnd->addChild(p1_1);

			char poker_file_name2[20] = "poker_pic/";
			sprintf(temp, "%d", p1->getCard02());
			strcat(poker_file_name2, temp);
			strcat(poker_file_name2, ".png");
			auto p1_2 = Sprite::create(poker_file_name2);
			p1_2->setPosition(300, 280);
			p1_2->setScale(0.5);
			GameEnd->addChild(p1_2);



			//////输家
			auto loser = Label::createWithSystemFont("Loser", "Arial", 20);
			loser->setPosition(200, 170);
			loser->setColor(ccc3(0, 0, 0));
			GameEnd->addChild(loser);

			auto loser_pic = Sprite::create(p2->getPhoto());
			loser_pic->setPosition(200, 100);
			GameEnd->addChild(loser_pic);

			//dipai 2
			char poker_file_name3[20] = "poker_pic/";
			sprintf(temp, "%d", p2->getCard01());
			strcat(poker_file_name3, temp);
			strcat(poker_file_name3, ".png");
			auto p2_1 = Sprite::create(poker_file_name3);
			p2_1->setPosition(280, 100);
			p2_1->setScale(0.5);
			GameEnd->addChild(p2_1);

			char poker_file_name4[20] = "poker_pic/";
			sprintf(temp, "%d", p2->getCard02());
			strcat(poker_file_name4, temp);
			strcat(poker_file_name4, ".png");
			auto p2_2 = Sprite::create(poker_file_name4);
			p2_2->setPosition(300, 100);
			p2_2->setScale(0.5);
			GameEnd->addChild(p2_2);



			//显示一遍公共牌？ 
			Point p[5];
			p[0] = Point(400, 190);
			p[1] = Point(450, 190);
			p[2] = Point(500, 190);
			p[3] = Point(550, 190);
			p[4] = Point(600, 190);
			CCLOG("card_num = %d", card_num);
			for (int i = 0; i < card_num; i++){ //减掉底牌就是公共牌数  ???肯定是哪里不对了，目前程序对

				char poker_file_name5[20] = "poker_pic/";
				sprintf(temp, "%d", gongGongCard[i]);
				strcat(poker_file_name5, temp);
				strcat(poker_file_name5, ".png");
				auto gonggongcard = Sprite::create(poker_file_name5);
				gonggongcard->setScale(0.7);
				gonggongcard->setPosition(p[i]);
				GameEnd->addChild(gonggongcard);
				CCLOG("giveup_gonggong %d = %s", i, poker_file_name5);
			}


			//显示对应牌型的名称
			auto paixing1 = Label::createWithSystemFont(getPaiXing(checkFinal(p2)), "Arial", 20);
			paixing1->setPosition(300, 170);//对应输家的牌型
			paixing1->setColor(ccc3(0, 0, 0));
			GameEnd->addChild(paixing1);

			auto paixing2 = Label::createWithSystemFont(getPaiXing(checkFinal(p1)), "Arial", 20);
			paixing2->setPosition(300, 350);//对应赢家
			paixing2->setColor(ccc3(0, 0, 0));
			GameEnd->addChild(paixing2);

		}//end IF(game_round == 4)

	
}
void GameScene::button_jiaZhu(Object * pSender){
	CCLOG("button jiazhu touched !");
	//暂时不用一律加注这个选项

}

void GameScene::button_gameEnd(Object * pSender){
	//点击此按钮，返回游戏开始界面，并且对内存进行释放
	//初步打算是非常的时间来跳转到Spalsh界面，然后就进入游戏画面
	this->scheduleOnce(schedule_selector(GameScene::jump2Game), 1);//延时5秒 
}


//============== sort ========

void GameScene::sort_ezCard_face(ezCard *arr, int n)
//bubble sort冒泡排序  
{
	int permutation = 1;   //permutation 意为排序  
	int k = n - 1, j;
	ezCard tmp(0);
	while ((k >= 1) && (permutation == 1)){
		permutation = 0;
		for (j = 0; j < k; j++)
		{
			if (arr[j].getFace()>arr[j + 1].getFace())//此排序为按照ezCard.face
			{
				//tmp = &arr[j];
				tmp.setFace(arr[j].getFace());
				tmp.setSuit(arr[j].getSuit());
				tmp.setID(arr[j].getID());
				//arr[j] = arr[j + 1];
				arr[j].setFace(arr[j + 1].getFace());
				arr[j].setSuit(arr[j + 1].getSuit());
				arr[j].setID(arr[j].getID());
				//arr[j + 1] = *tmp;
				arr[j + 1].setFace(tmp.getFace());
				arr[j + 1].setSuit(tmp.getSuit());
				arr[j + 1].setID(tmp.getID());
				permutation = 1;
			}
		}
		k = k - 1;
	}
	CCLOG("===sort_ezCard_face");
}

void GameScene::sort_ezCard_suit(ezCard *arr, int n)
{
	int permutation = 1;   //permutation 意为排序  
	int k = n - 1, j;
	ezCard tmp(0);
	while ((k >= 1) && (permutation == 1)){
		permutation = 0;
		for (j = 0; j < k; j++)
		{
			if (arr[j].getSuit()>arr[j + 1].getSuit())//此排序为按照ezCard.suit
			{
				//tmp = &arr[j];
				tmp.setFace(arr[j].getFace());
				tmp.setSuit(arr[j].getSuit());
				tmp.setID(arr[j].getID());
				//arr[j] = arr[j + 1];
				arr[j].setFace(arr[j + 1].getFace());
				arr[j].setSuit(arr[j + 1].getSuit());
				arr[j].setID(arr[j].getID());
				//arr[j + 1] = *tmp;
				arr[j + 1].setFace(tmp.getFace());
				arr[j + 1].setSuit(tmp.getSuit());
				arr[j + 1].setID(tmp.getID());
				permutation = 1;
			}
		}
		k = k - 1;
	}
	CCLOG("===sort_ezCard_suit");
}

int GameScene::checkFinal(Player * p){
	//return a number ,the lower ,the better
	//玩家2张底牌+5张公共牌
	int c[7];
	
	c[0] = p->getCard01();
	c[1] = p->getCard02();
	c[2] = gongGongCard[0];
	c[3] = gongGongCard[1];
	c[4] = gongGongCard[2];//error
	c[5] = gongGongCard[3];
	c[6] = gongGongCard[4];//error
	
	ezCard card[7] = { c[0], c[1], c[2], c[3], c[4], c[5], c[6] };//初始化ezcard

	CCLOG("====checkFinall!");
	CCLOG("CARD_FACE = %d %d %d %d %d %d %d", card[0].getFace(), card[1].getFace(), card[2].getFace(), card[3].getFace(), card[4].getFace(), card[5].getFace(), card[6].getFace());
	CCLOG("SUIT  : meihua = 0, fangpian = 1, hongtao = 2, heitao =3 ");
	CCLOG("CARD_SUIT = %d %d %d %d %d %d %d ", card[0].getSuit(), card[1].getSuit(), card[2].getSuit(), card[3].getSuit(), card[4].getSuit(), card[5].getSuit(), card[6].getSuit());
	//同花大顺？若都是同花顺，则比较点数和
	sort_ezCard_suit(card, 7);
	for (int j = 0; j < 3; j++){
		if (card[j].getSuit()== card[1+j].getSuit() && card[1+j].getSuit()==card[2+j].getSuit() &&
			card[2+j].getSuit() == card[3+j].getSuit()&& card[3+j].getSuit() == card[4+j].getSuit()			
			){//同花色	
			if ((card[j].getFace()+1) == card[1+j].getFace() && (card[1+j].getFace()+1) == card[2+j].getFace() &&
				(card[2+j].getFace() + 1) == card[3+j].getFace() && (card[3+j].getFace() + 1) == card[4+j].getFace()						
				){
				//相邻差1
				return 1;//  1代表同花顺
			}

		}
	}
	//四条2
	sort_ezCard_face(card, 7);
	CCLOG("sitiao");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  face == %d", i, card[i].getFace());
	}
	for (int i = 0; i < 4; i++){
		if (card[i].getFace() == card[1 + i].getFace() && card[1 + i].getFace() == card[2 + i].getFace() &&
			card[2 + i].getFace() == card[3 + i].getFace()
			)
		{//  4 same face
			return 2;
		}
	}
	//葫芦3
	sort_ezCard_face(card, 7);
	CCLOG("hulu");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  face == %d", i, card[i].getFace());
	}
	int tmp;//保存相同3个牌面的首张牌的位置0~6
	for (int i = 0; i < 5; i++){
		if (card[i].getFace() == card[i + 1].getFace() && card[i + 1].getFace() == card[i + 2].getFace())//连续三张牌牌面相同，再找剩下的牌有没有一对牌
		{
			CCLOG("hulu_get 3 same");
			CCLOG("weizhi_tmp = %d", i);
			tmp = i;//连续相同3张牌的第一个牌的位置
			for (int j = 0; j < 6; j++){
				if ((j != tmp) &&( j != (tmp + 1)) && (j != (tmp + 2))){  //& (j == (tmp + 2)  error!!!! small fool
					if (card[j].getFace() == card[j + 1].getFace()){//找到额外位置有一对相同的牌
						return 3;
					}
				}
			}
		}
	}



	//同花4
	sort_ezCard_suit(card, 7);
	CCLOG("tonghua");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  suit == %d", i, card[i].getSuit());
	}
	for (int i = 0; i < 3; i++){
		if (card[i].getSuit() == card[i + 1].getSuit() && card[i + 1].getSuit() == card[i + 2].getSuit() &&
			card[i + 2].getSuit() == card[i + 3].getSuit() && card[i + 3].getSuit() == card[i + 4].getSuit())
		{
			return 4;
		}
			
	}

	//顺子5
	sort_ezCard_face(card, 7);
	CCLOG("shunzi");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  face == %d", i, card[i].getFace());
	}
	for (int i = 0; i < 3; i++){
		if ((card[i].getFace() + 1) == card[i + 1].getFace() && (card[i + 1].getFace() + 1) == card[i + 2].getFace() &&
			(card[i + 2].getFace() + 1) == card[i + 3].getFace() && (card[i + 3].getFace() + 1) == card[i + 4].getFace()
			){

			return 5;
		}
	}

	//三条6
	sort_ezCard_face(card, 7);
	CCLOG("santiao");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  face == %d", i, card[i].getFace());
	}
	for (int i = 0; i < 5; i++){
		if (card[i].getFace() == card[i + 1].getFace() && card[i + 1].getFace() == card[i + 2].getFace()){
			return 6;
		}
	}


	//两对7
	sort_ezCard_face(card, 7);
	CCLOG("liangdui");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  face == %d", i, card[i].getFace());
	}
	for (int i = 0; i < 4; i++){
		if (card[i].getFace() == card[i+1].getFace() ){
			for (int j = i + 2; j < 6; j++){
				if (card[j].getFace() == card[j + 1].getFace())
				{
					return 7;
				}
			}

		}
	}

	//一对8
	sort_ezCard_face(card, 7);
	CCLOG("yidui");
	for (int i = 0; i < 7; i++){
		CCLOG("card-%d  face == %d", i, card[i].getFace());
	}
	for (int i = 0; i < 6; i++){
		if (card[i].getFace() == card[i + 1].getFace()){
			return 8;
		}
	}


	//高牌9 ++100
	sort_ezCard_face(card, 7);
	CCLOG("GAOPAI");
	int total_c = 0;//高牌的总和
	for (int i = 0; i < 5; i++){
		//这里有问题，之前是定义的变量t，但是t这个变量中会有栈溢出，估计是名字问题
		total_c += card[i + 2].getFace();
	}
	return total_c+100;// 设置高牌的值都是大于100的

}

int GameScene::getGaoPai(Player *p){
	//获取某个玩家的高牌组合是多少
	int c[7];
	c[0] = p->getCard01();
	c[1] = p->getCard02();
	c[2] = gongGongCard[0];
	c[3] = gongGongCard[1];
	c[4] = gongGongCard[2];//error
	c[5] = gongGongCard[3];
	c[6] = gongGongCard[4];//error
	ezCard card[7] = { c[0], c[1], c[2], c[3], c[4], c[5], c[6] };//初始化ezcard
	sort_ezCard_face(card, 7);
	int t_gg = 0;//高牌的总和
	for (int i = 0; i < 5; i++){
		t_gg += card[i + 2].getFace();
	}
	return t_gg;
}

char * GameScene::getPaiXing(int n){
	if (n == 1){
		return "^tonghuashun";
	}
	if (n == 2)
		return"^sitiao";
	if (n == 3)
		return "^hulu";
	if (n == 4)
		return "^tonghua";
	if (n == 5)
		return"^shunzi";
	if (n == 6)
		return "^santiao";
	if (n == 7)
		return "^liangdui";
	if (n == 8)
		return "^yidui";
	if (n > 100){
		return "^gaopai";
	}
	else{
		return "error_data!";
		CCLOG(" check Final data error in getPaiXing");
	}
	//char poker_file_name[20] = "poker_pic/";
	//char temp[9];
	//sprintf(temp, "%d", p1->getCard01());
	//strcat(poker_file_name, temp);
	//strcat(poker_file_name, ".png");// error some time
}




//5月27号
//已经实现了判断某个玩家的牌型大小，剩下的就是设计游戏逻辑，来完成最终的游戏。目前已经不会涉及到太多的关于数据的东西了，剩下的就是设计逻辑了，一些界面的调用顺序等，还要添加动画等
//添加一个新的场景 ，场景中有个层，用来显示谁是玩家，玩家的牌信息等
// 还要添加一个按钮，用来返回最初的游戏开始场景，用来实现不退出即可进行下一轮游戏
//而且赌注也要有相应的变化
void GameScene::jump2final(float t){// useless
	auto scene = final_layer::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));//以某种动画形式跳转到另外一个场景
}

void GameScene::jump2Game(float t){// useless
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));//以某种动画形式跳转到另外一个场景
}

void GameScene::jump2Splash(float t){// useless
	auto scene = Spalsh::createScene();
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));//以某种动画形式跳转到另外一个场景
}
