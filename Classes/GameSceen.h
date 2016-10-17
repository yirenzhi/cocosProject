#pragma once

#include "Globe.h"
#include "cocos2d.h"
#include "Stone.h"
USING_NS_CC;
class GameSceen:public cocos2d::Layer
{
public:
	//static cocos2d::Scene* createScene();

	virtual bool init();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void update(float delta);
	Vec2 getPlatePos(int x,int y);
	bool getClickPos(Vec2 point, int &x, int &y);
	int getStoneID(int x,int y);
	void changeFocus(int x,int y);
	void moveStone(int ,int);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(GameSceen);
	CREATE_SCENE(GameSceen);

	void start(Ref*);
	void newGame(Ref*);
	void regret(Ref*);
	void pause(Ref*);
	void difficulty(Ref*);

	Vec2 _stoneOffset;	//�����½ǵ������������ƫ��
	Vec2 _plateOffset;	//�������������ƫ��
	float _stoneSpace;	//���Ӽ�ļ��

private:
	vector <Stone*> vecStone;
	bool _isSelected;
	Sprite* focus;		//����

};

