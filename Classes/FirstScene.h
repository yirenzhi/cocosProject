#pragma once
#include "cocos2d.h"
#include "Globe.h"
USING_NS_CC;
class FirstScene:public cocos2d::Layer
{
public:

	virtual bool init();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void callback(HttpClient *sender,HttpResponse *response);
	CREATE_FUNC(FirstScene);
	CREATE_SCENE(FirstScene);
private:
	Sprite* startBt;
};

