#include "Tutorial.h"
#include "SimpleAudioEngine.h"
#include "PlayScene.h"
using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Tutorial::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
    Tutorial *layer = Tutorial::node();
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
    
    
    t1 = CCSprite::spriteWithFile("step1.png");
    t1->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    t2 = CCSprite::spriteWithFile("step2.png");
    t2->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    t3 = CCSprite::spriteWithFile("step3.png");
    t3->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    t4 = CCSprite::spriteWithFile("step4.png");
    t4->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );
    bg = CCSprite::spriteWithFile("bg.png");
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
    
    this->setIsTouchEnabled(true);
    
    
    width = CCDirector::sharedDirector()->getWinSize().width;
    height = CCDirector::sharedDirector()->getWinSize().height;
    
    float scale = width/960.0;
	pNext = CCMenuItemImage::itemWithNormalImage("next.png","next_2.png",this,menu_selector(Tutorial::nextSetp));
    pStart = CCMenuItemImage::itemWithNormalImage("start.png","start_2.png",this,menu_selector(Tutorial::nextSetp));
    pPrevious = CCMenuItemImage::itemWithNormalImage("previous.png","previous_2.png",this,menu_selector(Tutorial::previousSetp));
	pNext->setPosition( ccp(width - width*0.1, height*0.1) );
    pNext->setScale(scale);
    pStart->setPosition( ccp(width - width*0.1, height*0.1) );
    pStart->setScale(scale);
    pStart->setIsVisible(false);
    
	pPrevious->setPosition( ccp(width*0.1,height*0.1) );
    pPrevious->setScale(scale);
    pPrevious->setIsVisible(false);
	// create menu, it's an autorelease object
	CCMenu* pMainMenu = CCMenu::menuWithItems(pNext,pStart,pPrevious, NULL);
	pMainMenu->setPosition( CCPointZero );
	this->addChild(pMainMenu, 6);
    
	return true;
}

void Tutorial::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
     
}
void Tutorial::nextSetp(){
    if (t1->getIsVisible()) {
        t1->setIsVisible(false);
        pPrevious->setIsVisible(true);
    }else if(t2->getIsVisible()){
        t2->setIsVisible(false);
    }else if(t3->getIsVisible()){
        t3->setIsVisible(false);
        pNext->setIsVisible(false);
        pStart->setIsVisible(true);
    }else if(t4->getIsVisible()){
        t4->setIsVisible(false);
        CCUserDefault *save=CCUserDefault::sharedUserDefault(); 
        save->setBoolForKey("tutorialed",true); 
        save->flush();
        CCScene* pPlay = Play::scene();
        CCTransitionFade *pTranScene = CCTransitionFade::transitionWithDuration(0.5, pPlay);
        CCDirector::sharedDirector()->pushScene(pTranScene);
      
        t1->setIsVisible(true);
        t2->setIsVisible(true);
        t3->setIsVisible(true);
        t4->setIsVisible(true);
        pPrevious->setIsVisible(false);
        pNext->setIsVisible(true);
        pStart->setIsVisible(false);
    }
}


void Tutorial::previousSetp(){
    if (t1->getIsVisible()) {
        
    }else if(t2->getIsVisible()){
        t1->setIsVisible(true);
        pPrevious->setIsVisible(false);
    }else if(t3->getIsVisible()){
        t2->setIsVisible(true);
    }else if(t4->getIsVisible()){
        t3->setIsVisible(true);
        pNext->setIsVisible(true);
        pStart->setIsVisible(false);
    }
}

void Tutorial::startCallBack(CCObject* pSender)
{
    //CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
}
