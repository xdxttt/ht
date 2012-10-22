//
//  Tutorial.h
//  mc
//
//  Created by xdxttt on 8/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef mc_Tutorial_h
#define mc_Tutorial_h


#include "cocos2d.h"

class Tutorial : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	// a selector callback
	virtual void startCallBack(CCObject* pSender);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	LAYER_NODE_FUNC(Tutorial);
    
    void nextSetp();
    void previousSetp();
private:
    cocos2d::CCSprite* t1; 
    cocos2d::CCSprite* t2; 
    cocos2d::CCSprite* t3; 
    cocos2d::CCSprite* t4; 
    cocos2d::CCSprite* bg; 
    cocos2d::CCMenuItemImage *pNext;
    cocos2d::CCMenuItemImage *pStart;
    cocos2d::CCMenuItemImage *pPrevious;
    
};

#endif
