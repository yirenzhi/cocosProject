#include "HelloWorldScene.h"

USING_NS_CC;



static Rect getRect(Node * node)
{
	Rect rc;
	rc.origin = node->getPosition();
	rc.size = node->getContentSize();
	rc.origin.x -= rc.size.width / 2;
	rc.origin.y -= rc.size.height / 2;
	return rc;
}
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	log("visibX=%f   visibY=%f",visibleSize.width,visibleSize.height);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	log("originX=%d   originY=%d",origin.x,origin.y);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    


	//礼包的粒子特效
	if  (cocos2d::ParticleSystemQuad* m_libaoparticle = ParticleSystemQuad::create("UI_libao.plist"))
	{		
		m_libaoparticle->setScale(1.5f);
		m_libaoparticle->setDuration(-1);
	//	this->addChild(m_libaoparticle,5);
	//	m_libaoparticle->setPosition(CCPointMake(m_pgiftSprite->getContentSize().width/2  , m_pgiftSprite->getContentSize().height/2));

	//	m_libaoparticle->setVisible(false);
	}

	//礼包的粒子特效
	if  (cocos2d::ParticleSystemQuad* m_libaoparticle = ParticleSystemQuad::create("gifteffect/libao_shanguang.plist"))
	{		
		m_libaoparticle->setScale(1.5f);
		m_libaoparticle->setPosition(150,20);
	//	this->addChild(m_libaoparticle,5);

	}

	ParticleSystem *particle = ParticleSnow::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.png"));
//	this->addChild(particle);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	log("abc");

	testFile("test2.txt");
	testFile("tmp5_1.5.0.dt");
	testFile("tmp4_1.5.0.dt");
	testFile("save\tmp3_1.5.0.dt");
	auto path = cocos2d::FileUtils::getInstance()->getWritablePath();
	testFile((path+"mmm.txt").c_str());
	testFile("F:\\cocos2dx\\cocos2d-x-2.2.2_change_orgcocos2dxlib\\cocos2d-x-2.2.2\\projects\\HappyBabytest\\proj.win32\\Debug.win32\\save\\tmp2_1.5.0.dt1");
	testFile("F:/cocos2dx/cocos2d-x-2.2.2_change_orgcocos2dxlib/cocos2d-x-2.2.2/projects/HappyBabytest/proj.win32/Debug.win32/save/tmp8_1.5.0.dt");
	textField = TextFieldTTF::textFieldWithPlaceHolder("input some","Helvetica",15);
	textField->setAnchorPoint(ccp(0.5,0.5));
	textField->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(textField,100);

	auto fileItem = MenuItemImage::create(
		"mailbutton.png",
		"snow.png",
		CC_CALLBACK_1(HelloWorld::menufileCallback, this));

	fileItem->setPosition(Vec2(origin.x + visibleSize.width - fileItem->getContentSize().width/2 ,
		origin.y + fileItem->getContentSize().height/2+50));

	auto menu1 = Menu::create(fileItem, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1,100);


	auto pTextField = TextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
		"Thonburi.ttf",
		36);
	pTextField->setPosition(visibleSize.width/2,visibleSize.height*4/5);
	addChild(pTextField);

	_trackNode = pTextField;
    return true;
}


bool HelloWorld::onTouchBegan(Touch  *touch, Event  *event)
{
	CCLOG("++++++++++++++++++++++++++++++++++++++++++++");    
	return true;

}
void HelloWorld::onTouchEnded(Touch  *touch, Event  *event)
{
	auto endPos = touch->getLocation();
	Rect rect = getRect(_trackNode);
	auto point = convertTouchToNodeSpaceAR(touch);
	 this->onClickTrackNode(rect.containsPoint(endPos));

// 	 auto touchLocation = touch->getLocationInView();
// 	 auto pos = _trackNode->convertToNodeSpace(touchLocation);
// 	 this->onClickTrackNode(rect.containsPoint(pos));
}
void HelloWorld::onClickTrackNode(bool bClicked)
{
	auto pTextField = (TextFieldTTF*)_trackNode;
	if (bClicked)
	{
		// TextFieldTTFTest be clicked
		CCLOG("TextFieldTTFDefaultTest:TextFieldTTF attachWithIME");
		pTextField->attachWithIME();
	}
	else
	{
		// TextFieldTTFTest not be clicked
		CCLOG("TextFieldTTFDefaultTest:TextFieldTTF detachWithIME");
		pTextField->detachWithIME();
	}
}

void HelloWorld::testFile(std::string filename)
{
	FILE* file = fopen(filename.c_str(),"wb");
	if (file)
	{
		log("success");
	}
	else
	{
		log("fail");
	}

}
void HelloWorld::menufileCallback(cocos2d::Ref* pSender)
{
	std::string str= dynamic_cast<TextFieldTTF*>(_trackNode)->getString();
	log(str.c_str());
	testFile(str);
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
