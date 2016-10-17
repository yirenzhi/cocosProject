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


	_stoneOffset=Vec2(83,46);
	_plateOffset=Vec2(20,10);
	_stoneSpace=61;
	_isSelected=false;
	focus=NULL;
	_isSelected=false;
	//桌子
	auto zhuozi = Sprite::create(GameSceenPath+"floor.jpg");
	zhuozi->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(zhuozi);
	zhuozi->setScaleX(winSize.width/zhuozi->getContentSize().width);
	zhuozi->setScaleY(winSize.height/zhuozi->getContentSize().height);

	//棋盘
	auto qipan = Sprite::create(GameSceenPath+"background.png");
	//设置棋盘的偏移值
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


bool GameSceen::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos= touch->getLocation();

	int x,y;		//用来存储触摸点对应的棋盘x,y值
	if (!getClickPos(pos,x,y))
	{
		return false;
	}
	
	int selectId = getStoneID(x,y);
	
	if (_isSelected)//已经有棋子选中
	{
		moveStone(x,y);
	}
	else//没有棋子选中
	{
		if (selectId!=-1)
		{
			changeFocus(x,y);
		}
	}

	return true;
}

Vec2 GameSceen::getPlatePos(int x,int y)
{

	int xx = x*61;
	int yy = y*61;
	return Vec2(xx,yy)+_stoneOffset;
}

int GameSceen::getStoneID(int x,int y)
{
	for (int i=0;i<vecStone.size();i++)
	{
		if (x==vecStone[i]->getX()&&y==vecStone[i]->getY())
		{
			return vecStone[i]->getId();
		}
	}
	return -1;

}

void GameSceen::changeFocus(int x,int y)
{
	if(focus==NULL)
	{
		focus=Sprite::create(GameSceenPath+"selected.png");
		addChild(focus);
	}

	focus->setPosition(getPlatePos(x,y));
	_isSelected=true;
}

bool GameSceen::getClickPos(Vec2 point, int &x, int &y)
{
	for (x=0;x<9;x++)
	{
		for (y=0;y<10;y++)
		{
			Vec2 platePos = getPlatePos(x,y);
			if (point.getDistance(platePos)<30)
			{
				return true;
			}
		}
	}
	return false;
}

void GameSceen::moveStone(int x,int y)
{
	for (int i=0;i<vecStone.size();i++)
	{
		if (vecStone[i]->getPosition()==focus->getPosition())
		{
			vecStone[i]->setX(x);
			vecStone[i]->setY(y);
			vecStone[i]->setPosition(getPlatePos(x,y));
			focus->setPosition(getPlatePos(x,y));
			_isSelected=false;
		}
	}
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
