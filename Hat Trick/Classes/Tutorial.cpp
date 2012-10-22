#include "Tutorial.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Tutorial::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
    Tutorial *layer = Tutorial::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool Tutorial::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    double width = CCDirector::sharedDirector()->getWinSize().width;
    double height = CCDirector::sharedDirector()->getWinSize().height;
    double scale_width = width/960;
    double scale_height = height/640;
    
    
    t1 = CCSprite::create("step1.png");
    t1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    t2 = CCSprite::create("step2.png");
    t2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    t3 = CCSprite::create("step3.png");
    t3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    t4 = CCSprite::create("step4.png");
    t4->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    bg = CCSprite::create("bg.png");
    bg->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );

    this->addChild(bg, 1);
    this->addChild(t4, 2);
    this->addChild(t3, 3);
    this->addChild(t2, 4);
    this->addChild(t1, 5);
    
    
    t1->setScaleX(scale_width); 
    t2->setScaleX(scale_width); 
    t3->setScaleX(scale_width); 
    t4->setScaleX(scale_width); 
    bg->setScaleX(scale_width);
    
    t1->setScaleY(scale_height); 
    t2->setScaleY(scale_height); 
    t3->setScaleY(scale_height); 
    t4->setScaleY(scale_height); 
    bg->setScaleY(scale_height);
    
    this->setTouchEnabled(true);
    
    
    width = CCDirector::sharedDirector()->getWinSize().width;
    height = CCDirector::sharedDirector()->getWinSize().height;
    
    float scale = width/960.0;
	pNext = CCMenuItemImage::create("next.png","next_2.png",this,menu_selector(Tutorial::nextSetp));
    pStart = CCMenuItemImage::create("start.png","start_2.png",this,menu_selector(Tutorial::nextSetp));
    pPrevious = CCMenuItemImage::create("previous.png","previous_2.png",this,menu_selector(Tutorial::previousSetp));
	pNext->setPosition( ccp(width - width*0.1, height*0.1) );
    pNext->setScale(scale);
    pStart->setPosition( ccp(width - width*0.1, height*0.1) );
    pStart->setScale(scale);
    pStart->setVisible(false);
    
	pPrevious->setPosition( ccp(width*0.1,height*0.1) );
    pPrevious->setScale(scale);
    pPrevious->setVisible(false);
	// create menu, it's an autorelease object
	CCMenu* pMainMenu = CCMenu::create(pNext,pStart,pPrevious, NULL);
	pMainMenu->setPosition( CCPointZero );
	this->addChild(pMainMenu, 6);
    
	return true;
}

void Tutorial::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
     
}
void Tutorial::nextSetp(){
    if (t1->isVisible()) {
        t1->setVisible(false);
        pPrevious->setVisible(true);
    }else if(t2->isVisible()){
        t2->setVisible(false);
    }else if(t3->isVisible()){
        t3->setVisible(false);
        pNext->setVisible(false);
        pStart->setVisible(true);
    }else if(t4->isVisible()){
        t4->setVisible(false);
        CCUserDefault *save=CCUserDefault::sharedUserDefault(); 
        save->setBoolForKey("tutorialed",true); 
        save->flush();
        CCScene* pPlay = Play::scene();
        CCTransitionFade *pTranScene = CCTransitionFade::create(0.5, pPlay);
        CCDirector::sharedDirector()->pushScene(pTranScene);
      
        t1->setVisible(true);
        t2->setVisible(true);
        t3->setVisible(true);
        t4->setVisible(true);
        pPrevious->setVisible(false);
        pNext->setVisible(true);
        pStart->setVisible(false);
    }
}


void Tutorial::previousSetp(){
    if (t1->isVisible()) {
        
    }else if(t2->isVisible()){
        t1->setVisible(true);
        pPrevious->setVisible(false);
    }else if(t3->isVisible()){
        t2->setVisible(true);
    }else if(t4->isVisible()){
        t3->setVisible(true);
        pNext->setVisible(true);
        pStart->setVisible(false);
    }
}

void Tutorial::startCallBack(CCObject* pSender)
{
    //CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
}
