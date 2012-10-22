#include "PlayScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Play::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	Play *layer = Play::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Play::init()
{
    this->setIsTouchEnabled(true);
    switch_speed = 1;
    isInCup = false;
    isLayoutCoin = true;
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
   
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
    
    width = CCDirector::sharedDirector()->getWinSize().width;
    height = CCDirector::sharedDirector()->getWinSize().height;

    scale = width/960.0;
    float height_scale = height/640.0;
	CCMenuItemImage *pCloseItem = CCMenuItemImage::itemWithNormalImage("reset.png","reset_2.png",this,menu_selector(Play::menuCloseCallback));
    CCMenuItemImage *pSettigItem = CCMenuItemImage::itemWithNormalImage("setting.png","setting_2.png",this,menu_selector(Play::menuSettingCallback));
	pCloseItem->setPosition( ccp(width - width*0.1, height*0.9) );
    pCloseItem->setScale(scale);
    
	pSettigItem->setPosition( ccp(width*0.1,height*0.9) );
    pSettigItem->setScale(scale);
	// create menu, it's an autorelease object
	pMainMenu = CCMenu::menuWithItems(pCloseItem,pSettigItem, NULL);
	pMainMenu->setPosition( CCPointZero );
	this->addChild(pMainMenu, 1);
    
    CCMenuItemImage *pHelpItem = CCMenuItemImage::itemWithNormalImage("tutorial.png","tutorial_2.png",this,menu_selector(Play::menuHelpCallback));
	pHelpItem->setPosition( ccp(width*0.1+pSettigItem->boundingBox().size.width*2, height*0.9) );
    pHelpItem->setScale(scale);
    
	pSettingMenu = CCMenu::menuWithItems(pHelpItem, NULL);
	pSettingMenu->setPosition( CCPointZero );
	this->addChild(pSettingMenu, 1);
    pSettingMenu->setIsVisible(false);
    

	CCSize size = CCDirector::sharedDirector()->getWinSize();

    jump_height = height*0.3;
    CCSprite* bg = CCSprite::spriteWithFile("bg.png");
    bg->setPositionX(CCDirector::sharedDirector()->getWinSize().width/2);
    bg->setPositionY(CCDirector::sharedDirector()->getWinSize().height/2);
    bg->setScaleX(scale);
    bg->setScaleY(height_scale);

    
    hat_texture = CCTextureCache::sharedTextureCache()->addImage("hat.png");
    hat_texture_2 = CCTextureCache::sharedTextureCache()->addImage("hat_2.png");

    pSprite_a = CCSprite::spriteWithTexture(hat_texture);
    pSprite_a->setScale(scale);
    pSprite_b = CCSprite::spriteWithTexture(hat_texture);
    pSprite_b->setScale(scale);
    pSprite_c = CCSprite::spriteWithTexture(hat_texture);
    pSprite_c->setScale(scale);
    
    pShadow_a = CCSprite::spriteWithFile("shadow.png");
    pShadow_a->setScale(scale);
    pShadow_b = CCSprite::spriteWithFile("shadow.png");
    pShadow_b->setScale(scale);
    pShadow_c = CCSprite::spriteWithFile("shadow.png");
    pShadow_c->setScale(scale);
    
    double hat_height = pSprite_c->boundingBox().size.height;
    
    pCoin = CCSprite::spriteWithFile("coin.png");
    pCoin->setScale(scale);
    
    pCoin->boundingBox();
    
    pointe_a = ccp(width*0.2, height/2);
    pointe_b = ccp(width*0.5, height/2) ;
    pointe_c = ccp(width*0.8, height/2) ;
    shadow_pointe_a = ccp(width*0.2, height/2 -hat_height/2);
    shadow_pointe_b = ccp(width*0.5, height/2 -hat_height/2) ;
    shadow_pointe_c = ccp(width*0.8, height/2 -hat_height/2) ;
    
    
    
    pCoin->setPosition(ccp(width*0.6,height*0.2));
	pSprite_a->setPosition(pointe_a);
	pSprite_b->setPosition(pointe_b);
    pSprite_c->setPosition(pointe_c);
    
    pShadow_a->setPosition(shadow_pointe_a);
	pShadow_b->setPosition(shadow_pointe_b);
    pShadow_c->setPosition(shadow_pointe_c);
    
	// add the sprite as a child to this layer
    this->addChild(pCoin, 2);
	this->addChild(pSprite_a, 3);
    this->addChild(pSprite_b, 3);
    this->addChild(pSprite_c, 3);
    this->addChild(pShadow_a, 1);
    this->addChild(pShadow_b, 1);
    this->addChild(pShadow_c, 1);
    
    this->addChild(bg, -1);
	this->setIsTouchEnabled(true);

	return true;
}

void Play::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){

    pSettingMenu->setIsVisible(false);
    isFingerMoved = false;
    touchMoveCount = 0;
    touchMaxPoint = 0;

    for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++)
    {
        CCTouch *pTouch =  (cocos2d::CCTouch*)(*iterTouch);
        m_touchPoint = pTouch->locationInView( );
        m_touchPoint = CCDirector::sharedDirector()->convertToGL( m_touchPoint );
        
        if (pCoin->getIsVisible()) {
            CCRect touchRect = cocos2d::CCRectMake( m_touchPoint.x,  m_touchPoint.y, 30, 30);
            CCRect cionRect = pCoin->boundingBox();
            if( CCRect::CCRectIntersectsRect(cionRect, touchRect)){
                
                CCPoint touchPoint = pTouch->locationInView();
                touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );                        
                cocos2d::CCPoint delta = ccpSub(touchPoint, pCoin->getPosition());
                cocos2d::CCPoint p = pCoin->getPosition();
                pCoin->setPosition(ccpAdd(p, delta));
                
                if( CCRect::CCRectIntersectsRect(pSprite_a->boundingBox(), cionRect)){
                    isInCup = true;
                }else if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), cionRect)){
                    isInCup = true;
                }else if ( CCRect::CCRectIntersectsRect(pSprite_c->boundingBox(), cionRect)) {
                    isInCup = true;
                }else {
                    isInCup = false;
                }
            }
        }else {
           
                    
        }
    }
    return ;
}
void Play::setInvisible(CCNode * node){
    node->setIsVisible(false);
}
void Play::closeHat(CCSprite* node){
    CCTexture2D* hat_texture = CCTextureCache::sharedTextureCache()->textureForKey("hat.png");
    node->setTexture(hat_texture);
}

void Play::playCoinMp3(CCSprite* node){
    SimpleAudioEngine::sharedEngine()->playEffect("coin.mp3");
}

void Play::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    
    touchMoveCount++;
    if (touchMaxPoint<pTouches->count()) {
        touchMaxPoint = pTouches->count();
    }
            
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    printf("ccTouchesMoved begin pTouches count %d\r\n",pTouches->count());        // do something

    for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++)
    {
        CCTouch *pTouch =  (cocos2d::CCTouch*)(*iterTouch);
        CCPoint _touchPoint = pTouch->locationInView();
        _touchPoint = CCDirector::sharedDirector()->convertToGL( _touchPoint );
        
        if (_touchPoint.x!=m_touchPoint.x&&_touchPoint.y!=m_touchPoint.y) {
            isFingerMoved = true;
        }
        
        if (pCoin->getIsVisible()) {
          
            CCRect touchRect = cocos2d::CCRectMake( _touchPoint.x,  _touchPoint.y, 30, 30);
            CCRect cionRect = pCoin->boundingBox();
            if( CCRect::CCRectIntersectsRect(cionRect, touchRect)){
                CCPoint touchPoint = pTouch->locationInView();
                touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );                        
                cocos2d::CCPoint delta = ccpSub(touchPoint, pCoin->getPosition());
                cocos2d::CCPoint p = pCoin->getPosition();
                pCoin->setPosition(ccpAdd(p, delta));
                
                if (!isInCup) {
                    if( CCRect::CCRectIntersectsRect(pSprite_a->boundingBox(), cionRect)){
                        CCMoveTo* moveto = CCMoveTo::actionWithDuration(0.8,shadow_pointe_a);
                        CCMoveTo* moveto2 = CCMoveTo::actionWithDuration(0.2, pointe_a);
                        CCScaleTo* iconsc=CCScaleTo::actionWithDuration(1, 0.6*this->scale);  
                        pCoin->runAction( CCSpawn::actions(CCSequence::actions(moveto,moveto2,CCCallFuncN::actionWithTarget(pCoin,callfuncN_selector(Play::setInvisible)),NULL),iconsc, NULL));
                      
                        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*this->scale);
                        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*this->scale);
                        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
                        pShadow_a->runAction(sq1);
  
                        
                        CCJumpTo* jump = CCJumpTo::actionWithDuration(1,pointe_a,height*0.2,1);
                        pSprite_a->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_a,callfuncN_selector(Play::closeHat)), NULL));
                        pSprite_a->setTexture(hat_texture_2);
                        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                        isLayoutCoin = false;
                    }else if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), cionRect)){
                        
                       // CCJumpTo* jumpto = CCJumpTo::actionWithDuration(1, pointe_b,jump_height,1);
                        CCMoveTo* moveto = CCMoveTo::actionWithDuration(0.8, shadow_pointe_b);
                        CCMoveTo* moveto2 = CCMoveTo::actionWithDuration(0.2, pointe_b);
                        CCScaleTo* iconsc=CCScaleTo::actionWithDuration(1, 0.6*this->scale); 
                        pCoin->runAction( CCSpawn::actions(CCSequence::actions(moveto,moveto2,CCCallFuncN::actionWithTarget(pCoin,callfuncN_selector(Play::setInvisible)),NULL),iconsc, NULL));
                        
                        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*this->scale);
                        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*this->scale);
                        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
                        pShadow_b->runAction(sq1);
                        
                        CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_b,height*0.2,1);
                        pSprite_b->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_b,callfuncN_selector(Play::closeHat)), NULL));
                        pSprite_b->setTexture(hat_texture_2);
                        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                        isLayoutCoin = false;
                    }else if ( CCRect::CCRectIntersectsRect(pSprite_c->boundingBox(), cionRect)) {
                        
                        CCMoveTo* moveto = CCMoveTo::actionWithDuration(0.8, shadow_pointe_c);
                        CCMoveTo* moveto2 = CCMoveTo::actionWithDuration(0.2, pointe_c);
                        CCScaleTo* iconsc=CCScaleTo::actionWithDuration(1, 0.8*this->scale); 

                        pCoin->runAction( CCSpawn::actions(CCSequence::actions(moveto,moveto2,CCCallFuncN::actionWithTarget(pCoin,callfuncN_selector(Play::setInvisible)),NULL),iconsc, NULL));
                        
                        
                        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*this->scale);
                        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*this->scale);
                        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
                        pShadow_c->runAction(sq1);
                        
                        
                        CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_c,height*0.2,1);
                        pSprite_c->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_c,callfuncN_selector(Play::closeHat)), NULL));
                        pSprite_c->setTexture(hat_texture_2);
                        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                        isLayoutCoin = false;
                    }
                }else {
                    if( CCRect::CCRectIntersectsRect(pSprite_a->boundingBox(), cionRect)){
                       
                    }else if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), cionRect)){
                        
                    }else if ( CCRect::CCRectIntersectsRect(pSprite_c->boundingBox(), cionRect)) {
                        
                    }else {
                        isInCup = false;
                    }
                }
            }else{
             
                // CCJumpTo* jump = CCJumpTo::actionWithDuration(0.5, pCoin->getPosition(),10,1);
                // pCoin->runAction( CCSequence::actions(jump, NULL));
            }
        }else{
            
            if (isLayoutCoin) {
                
            }else {
                if(isFingerMoved&&touchMoveCount>3){
                    if (pTouch->previousLocationInView( ).x<size.width/2) {
                        if (touchMaxPoint==1) {
                            switchLeftCion();
                        }
                        switchLeftCup();
                    }else{
                        if (touchMaxPoint==1) {
                            switchRightCion(); 
                        }     
                        switchRightCup();
                    }
                }
             
              //  }
            }
       }
        m_touchPoint = _touchPoint;
    }
   
    return ;
}

void Play::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    printf("ccTouchesEnded begin\r\n");        // do something
    m_touchPoint=::CCPointZero;
    touchMoveCount = 0;
    for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++)
    {
        if (!pCoin->getIsVisible()) {
            isLayoutCoin = false;
            if (!isFingerMoved) {
                
                CCTouch *pTouch =  (cocos2d::CCTouch*)(*iterTouch);
                CCPoint touchPoint = pTouch->locationInView();
                touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
                CCRect touchRect = cocos2d::CCRectMake( touchPoint.x,  touchPoint.y, 5, 5);
                CCRect coinbb ;
                coinbb.size.width = pSprite_a->boundingBox().size.width;
                coinbb.size.height = pSprite_a->boundingBox().size.height;
                coinbb.origin.x = pCoin->getPositionX()-pSprite_a->boundingBox().size.width/2;
                coinbb.origin.y = pCoin->getPositionY()-pSprite_a->boundingBox().size.height/2;
                
                if( CCRect::CCRectIntersectsRect(coinbb, touchRect)){
                    CCPoint point = pCoin->getPosition();
                    point.y=height*0.2;
                    CCMoveTo* moveto = CCMoveTo::actionWithDuration(1, point);
                    pCoin->setScale(0.6*this->scale);
                    CCScaleTo* scale=CCScaleTo::actionWithDuration(1, this->scale); 
                    CCRotateTo *rot = CCRotateTo::actionWithDuration(0.1, 20);
                    CCRotateTo *rot2 = CCRotateTo::actionWithDuration(0.1, -20);
                    CCRotateTo *rot3 = CCRotateTo::actionWithDuration(0.1, 10);
                    CCRotateTo *rot4 = CCRotateTo::actionWithDuration(0.1, -10);
                    CCRotateTo *rot5 = CCRotateTo::actionWithDuration(0.1, 0);
                    pCoin->runAction( CCSpawn::actions(scale,CCSequence::actions(moveto,CCCallFuncN::actionWithTarget(pCoin,callfuncN_selector(Play::playCoinMp3)),rot,rot2,rot3,rot4,rot5,NULL),NULL));
                    pCoin->setIsVisible(true);
                    isLayoutCoin = true;
                    isInCup = false;
                }
                
               
                if( CCRect::CCRectIntersectsRect(pSprite_a->boundingBox(), touchRect)){
                    
                    CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
                    CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
                    CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
                    pShadow_a->runAction(sq1);
                    CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_a,height*0.2,1);
                    pSprite_a->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_a,callfuncN_selector(Play::closeHat)), NULL));
                    pSprite_a->setTexture(hat_texture_2);
                    SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                }else if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), touchRect)){
                    CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
                    CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
                    CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
                    pShadow_b->runAction(sq1);
                    
                    CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_b,height*0.2,1);
                    pSprite_b->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_b,callfuncN_selector(Play::closeHat)), NULL));
                    pSprite_b->setTexture(hat_texture_2);
                    SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                }else if ( CCRect::CCRectIntersectsRect(pSprite_c->boundingBox(), touchRect)) {
                    CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
                    CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
                    CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
                    pShadow_c->runAction(sq1);
                    
                    CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_c,height*0.2,1);
                    pSprite_c->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_c,callfuncN_selector(Play::closeHat)), NULL));
                    pSprite_c->setTexture(hat_texture_2);
                    SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                    
                }   
            }
        }
    }
    
    return ;
}
void Play::switchLeftCup(){
    if (pSprite_a->numberOfRunningActions()==0&&pSprite_b->numberOfRunningActions()==0) {
        
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        
        CCJumpTo* jump2b = CCJumpTo::actionWithDuration(switch_speed, pointe_b,height*0.2,1);
        CCJumpTo* jump2a = CCJumpTo::actionWithDuration(switch_speed, pointe_a,height*0.2,1);
        
        pSprite_a->runAction(CCSequence::actions(jump2b,NULL));
        pSprite_b->runAction(CCSequence::actions(jump2a,NULL));
        
        CCMoveTo* move2b = CCMoveTo::actionWithDuration(switch_speed, shadow_pointe_b);
        CCMoveTo* move2a = CCMoveTo::actionWithDuration(switch_speed, shadow_pointe_a);
        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCScaleTo* sc3 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc4 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
        CCFiniteTimeAction *sq2 = CCSequence::actions(sc3,sc4,NULL);

        pShadow_a->runAction(CCSpawn::actions(move2b,sq1,NULL));
        pShadow_b->runAction(CCSpawn::actions(move2a,sq2,NULL));
        
        
        cocos2d::CCSprite* temp = pShadow_b;
        pShadow_b = pShadow_a;
        pShadow_a = temp;
        

        
        temp = pSprite_b;
        pSprite_b = pSprite_a;
        pSprite_a = temp;
        speedup();
    }
}
void Play::switchRightCup(){
    if (pSprite_b->numberOfRunningActions()==0&&pSprite_c->numberOfRunningActions()==0) {
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        
        CCJumpTo* jump2b = CCJumpTo::actionWithDuration(switch_speed, pointe_b,height*0.2,1);
        CCJumpTo* jump2c = CCJumpTo::actionWithDuration(switch_speed, pointe_c,height*0.2,1);
        
        pSprite_c->runAction(CCSequence::actions(jump2b,NULL));
        pSprite_b->runAction(CCSequence::actions(jump2c,NULL));
        
        CCMoveTo* move2b = CCMoveTo::actionWithDuration(switch_speed, shadow_pointe_b);
        CCMoveTo* move2c = CCMoveTo::actionWithDuration(switch_speed, shadow_pointe_c);
        
        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCScaleTo* sc3 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc4 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
        CCFiniteTimeAction *sq2 = CCSequence::actions(sc3,sc4,NULL);
        
        pShadow_c->runAction(CCSpawn::actions(move2b,sq1,NULL));
        pShadow_b->runAction(CCSpawn::actions(move2c,sq2,NULL));
        
        cocos2d::CCSprite* temp = pShadow_b;
        pShadow_b = pShadow_c;
        pShadow_c = temp;
        
        
        temp = pSprite_b;
        pSprite_b = pSprite_c;
        pSprite_c = temp;
        speedup();
    }
}

void Play::switchLeftCion(){
    if (pSprite_b->numberOfRunningActions()==0&&pSprite_c->numberOfRunningActions()==0) {

    if (!pCoin->getIsVisible()) {
        CCRect cionRect = pCoin->boundingBox();
        if( CCRect::CCRectIntersectsRect(pSprite_a->boundingBox(), cionRect)){
            pCoin->setPosition(pointe_b);
        }else if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), cionRect)){
            pCoin->setPosition(pointe_a);
        }
        
    }
    }
}
void Play::switchRightCion(){
    
    if (pSprite_b->numberOfRunningActions()==0&&pSprite_c->numberOfRunningActions()==0) {

    if (!pCoin->getIsVisible()) {
        CCRect cionRect = pCoin->boundingBox();
        if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), cionRect)){
            pCoin->setPosition(pointe_c);
        }else if ( CCRect::CCRectIntersectsRect(pSprite_c->boundingBox(), cionRect)) {
            pCoin->setPosition(pointe_b);
        }
    }
    }
}
void Play::speedup(){
    if(switch_speed>0.5){
        switch_speed = switch_speed-0.1;
    }
}
void Play::resetSpeed(){
    switch_speed = 1;
}


void Play::menuCloseCallback(CCObject* pSender)
{
    if (pCoin->getIsVisible()==false) {
        CCPoint point = pCoin->getPosition();
        point.y=height*0.2;
        CCMoveTo* moveto = CCMoveTo::actionWithDuration(1, point);
        pCoin->setScale(0.6*this->scale);
        CCScaleTo* scale=CCScaleTo::actionWithDuration(1, this->scale); 
        CCRotateTo *rot = CCRotateTo::actionWithDuration(0.1, 20);
        CCRotateTo *rot2 = CCRotateTo::actionWithDuration(0.1, -20);
        CCRotateTo *rot3 = CCRotateTo::actionWithDuration(0.1, 10);
        CCRotateTo *rot4 = CCRotateTo::actionWithDuration(0.1, -10);
        CCRotateTo *rot5 = CCRotateTo::actionWithDuration(0.1, 0);
        pCoin->runAction( CCSpawn::actions(scale,CCSequence::actions(moveto,CCCallFuncN::actionWithTarget(pCoin,callfuncN_selector(Play::playCoinMp3)),rot,rot2,rot3,rot4,rot5,NULL),NULL));
    }
   
    pCoin->setIsVisible(true);
    isLayoutCoin = true;
    isInCup = false;

    if( CCRect::CCRectIntersectsRect(pSprite_a->boundingBox(), pCoin->boundingBox())){
        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
        pShadow_a->runAction(sq1);
        
        CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_a,height*0.2,1);
        pSprite_a->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_a,callfuncN_selector(Play::closeHat)), NULL));
       
        pSprite_a->setTexture(hat_texture_2);
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        

    }else if( CCRect::CCRectIntersectsRect(pSprite_b->boundingBox(), pCoin->boundingBox())){
        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
        pShadow_b->runAction(sq1);
        CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_b,height*0.2,1);
        pSprite_b->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_b,callfuncN_selector(Play::closeHat)), NULL));
        pSprite_b->setTexture(hat_texture_2);
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        


    }else if ( CCRect::CCRectIntersectsRect(pSprite_c->boundingBox(), pCoin->boundingBox())) {
        CCScaleTo* sc1 = CCScaleTo::actionWithDuration(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::actionWithDuration(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::actions(sc1,sc2,NULL);
        pShadow_c->runAction(sq1);
        CCJumpTo* jump = CCJumpTo::actionWithDuration(1, pointe_c,height*0.2,1);
        pSprite_c->runAction( CCSequence::actions(jump,CCCallFuncN::actionWithTarget(pSprite_c,callfuncN_selector(Play::closeHat)), NULL));
        pSprite_c->setTexture(hat_texture_2);
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        
	
    }
    
    resetSpeed();
    
    //CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
}
void Play::menuSettingCallback(CCObject* pSender)
{
    pSettingMenu->setIsVisible(true);

    //CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
}
void Play::menuHelpCallback(CCObject* pSender)
{

    CCDirector::sharedDirector()->popScene();
    CCUserDefault *save=CCUserDefault::sharedUserDefault(); 
    save->setBoolForKey("tutorialed",true); 
    save->flush();
    
//CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);
#endif
}
