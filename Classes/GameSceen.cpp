#include "GameSceen.h"
#include "FirstScene.h"
#include <functional>
#include <algorithm>
const string GameSceenPath="gameScreen/";

bool GameSceen::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size winSize=Director::getInstance()->getWinSize();

	auto bg = Sprite::create(GameSceenPath+"bg0.jpg");
	bg->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(bg);

	ADD_TOUCH_ONE(GameSceen);
	ADD_TOUCH_KEY(GameSceen);


	//桌子
	auto zhuozi = Sprite::create(GameSceenPath+"floor.jpg");
	zhuozi->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(zhuozi);
	zhuozi->setScaleX(winSize.width/zhuozi->getContentSize().width);
	zhuozi->setScaleY(winSize.height/zhuozi->getContentSize().height);

	//棋盘
	auto qipan = Sprite::create(GameSceenPath+"background.png");
	//设置棋盘的偏移值
	Vec2	_plateOffset = Vec2(20,10);
	qipan->setAnchorPoint(Vec2(0,0));
	qipan->setPosition(_plateOffset);
	qipan->setScale((winSize.height-2*_plateOffset.y)/qipan->getContentSize().height);
	addChild(qipan);



	//菜单
	//新局   //开始  //悔棋   //暂停  //难度
	auto menu = Menu::create();
	addChild(menu);

	string menusImage[] = {"new","start","regret","pause","difficulty"};
	int len = sizeof(menusImage)/sizeof(menusImage[0]);


//	std::function<void(Ref*)> bind_func = CC_CALLBACK_1(GameSceen::start,this);
	//vector<const ccMenuCallback&>  callbackFuc;
	vector<std::function<void(Ref*)>>  callbackFuc;

	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::newGame,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::start,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::regret,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::pause ,this));
	callbackFuc.push_back(CC_CALLBACK_1(GameSceen::difficulty,this));
	for (int i=0;i<len;i++)
	{
		auto newGame = MenuItemImage::create(GameSceenPath+menusImage[i]+".jpg",GameSceenPath+menusImage[i]+".jpg",callbackFuc[i]);
		menu->addChild(newGame);
		newGame->setPosition(Vec2(280,220-i*80));
	}

	//棋子
	for(int i=0;i<32;i++)
	{
		auto stone = Stone::create(i);
		addChild(stone);
		vecStone.push_back(stone);
	}


	return true;
}
void GameSceen::update(float delta)
{

}

void GameSceen::start(Ref*)
{
	log("start");
}

void GameSceen::newGame(Ref*)
{
	log("newGame");
}
void GameSceen::regret(Ref*)
{
	log("regret");
}
void GameSceen::pause(Ref*)
{
	log("pause");
}
void GameSceen::difficulty(Ref*)
{
	log("difficulty");
}


bool GameSceen::onTouchBegan(Touch *touch, Event *unused_event)
{
	//Vec2 point = convertToNodeSpace(touch);
	auto pos = touch->getLocationInView();


	return true;
}

Vec2 GameSceen::getPlatePos(int x,int y)
{

}


void GameSceen::onTouchEnded(Touch *touch, Event *unused_event)
{

}


void GameSceen::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_BACK==keyCode)
	{
		REPLACE_SCENE(FirstScene);
	}
}
void GameSceen::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}
