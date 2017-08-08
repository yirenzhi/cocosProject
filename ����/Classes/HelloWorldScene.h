#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	// a selector callback
	void menufileCallback(cocos2d::Ref* pSender);

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//测试文件功能
	//test file 
	void testFile(std::string);

	void onClickTrackNode(bool bClicked);

	bool onTouchBegan(Touch  *touch, Event  *event);
	void onTouchEnded(Touch  *touch, Event  *event);
private:
	Node * textField;
	Node * _trackNode;
};

#endif // __HELLOWORLD_SCENE_H__
