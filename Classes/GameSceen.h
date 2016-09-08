#pragma once

#include "Globe.h"
#include "cocos2d.h"
USING_NS_CC;
class GameSceen:public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(GameSceen);
	CREATE_SCENE(GameSceen);

	void start(Ref*);
	void newGame(Ref*);
	void regret(Ref*);
	void pause(Ref*);
	void difficulty(Ref*);
	
};

