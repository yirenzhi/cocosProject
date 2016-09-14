#include "FirstScene.h"
#include "ui/CocosGUI.h"
#include "GameSceen.h"
USING_NS_CC;
using namespace ui;

bool FirstScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size winSize=Director::getInstance()->getWinSize();
	log("winSize.width:%f,winSize.height:%f",winSize.width,winSize.height);

	auto bg = Sprite::create("firstScreen/bg0.jpg");
	bg->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(bg);

	startBt = Sprite::create("firstScreen/startGame.png");
	startBt->setPosition(Vec2(winSize.width/2,winSize.height/2));
	addChild(startBt);
	
	//setTouchEnabled(true);
	//setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	ADD_TOUCH_ONE(FirstScene);
	return true;
}



bool FirstScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}
void FirstScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocationInView();
	pos = startBt->convertToNodeSpace(pos);
	CCSize sz = startBt->getTexture()->getContentSizeInPixels();
	CCRect rect = CCRectMake(0,0,sz.width,sz.height);
 
	if (rect.containsPoint(pos))
	{
		log("ok");

		REPLACE_SCENE(GameSceen);

	}
}
