#include "GameSceen.h"
#include "FirstScene.h"
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


	//����
	auto zhuozi = Sprite::create(GameSceenPath+"floor.jpg");
	zhuozi->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(zhuozi);
	zhuozi->setScaleX(winSize.width/zhuozi->getContentSize().width);
	zhuozi->setScaleY(winSize.height/zhuozi->getContentSize().height);

	//����
	auto qipan = Sprite::create(GameSceenPath+"background.png");
	//�������̵�ƫ��ֵ
	Vec2	_plateOffset = Vec2(20,10);
	qipan->setAnchorPoint(Vec2(0,0));
	qipan->setPosition(_plateOffset);
	qipan->setScale((winSize.height-2*_plateOffset.y)/qipan->getContentSize().height);
	addChild(qipan);


	//����

	//�˵�
	auto menu = Menu::create();
	addChild(menu);

	//�¾�
	auto newGame = MenuItemImage::create(GameSceenPath+"new.jpg",GameSceenPath+"new.jpg",CC_CALLBACK_1(GameSceen::start,this));
	menu->addChild(newGame);
	newGame->setPosition(Vec2(220,120));

	//��ʼ
	auto itemStart = MenuItemImage::create(GameSceenPath+"start.jpg",GameSceenPath+"start.jpg",CC_CALLBACK_1(GameSceen::start,this));
	menu->addChild(itemStart);
	itemStart->setPosition(Vec2(220,120));

	//����

	//��ͣ

	//�Ѷ�

	return true;
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
	return true;
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
