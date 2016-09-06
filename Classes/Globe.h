#pragma once
#include "cocos2d.h"
#include <iostream>

using namespace std;
#define CREATE_SCENE(__type__)\
	static cocos2d::Scene* createScene()\
	{\
		Scene* scene = Scene::create();\
		__type__* layer = __type__::create();\
		scene->addChild(layer);\
		return scene;\
}


#define ADD_TOUCH_ONE(__type__)\
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();\
	listener->onTouchBegan=CC_CALLBACK_2(__type__::onTouchBegan,this);\
	listener->onTouchEnded=CC_CALLBACK_2(__type__::onTouchEnded,this);\
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

#define  ADD_TOUCH_KEY(__type__)\
	EventListenerKeyboard* listenerk = EventListenerKeyboard::create();\
	_keyboardListener = listenerk;\
	listenerk->onKeyPressed = CC_CALLBACK_2(__type__::onKeyPressed, this);\
	listenerk->onKeyReleased = CC_CALLBACK_2(__type__::onKeyReleased, this);\
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerk, this);
//_eventDispatcher->addEventListenerWithFixedPriority(listenerk, this);

#define REPLACE_SCENE(__type__)\
	if (CCScene *pScene =  CCTransitionFade::create(0.3f,__type__::createScene()))\
{\
	CCDirector::getInstance()->replaceScene(pScene);\
}

class Globe
{
public:

	static string FirshScenePath;
	static string GameScenePath;

};

