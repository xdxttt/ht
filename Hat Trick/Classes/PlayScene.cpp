#include "PlayScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Play::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease object
	Play *layer = Play::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Play::init()
{
    this->setTouchEnabled(true);
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
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("reset.png","reset_2.png",this,menu_selector(Play::menuCloseCallback));
    CCMenuItemImage *pSettigItem = CCMenuItemImage::create("setting.png","setting_2.png",this,menu_selector(Play::menuSettingCallback));
	pCloseItem->setPosition( ccp(width - width*0.1, height*0.9) );
    pCloseItem->setScale(scale);
    
	pSettigItem->setPosition( ccp(width*0.1,height*0.9) );
    pSettigItem->setScale(scale);
	// create menu, it's an autorelease object
	pMainMenu = CCMenu::create(pCloseItem,pSettigItem, NULL);
	pMainMenu->setPosition( CCPointZero );
	this->addChild(pMainMenu, 1);
    
    CCMenuItemImage *pHelpItem = CCMenuItemImage::create("tutorial.png","tutorial_2.png",this,menu_selector(Play::menuHelpCallback));
	pHelpItem->setPosition( ccp(width*0.1+pSettigItem->boundingBox().size.width*2, height*0.9) );
    pHelpItem->setScale(scale);
    
	pSettingMenu = CCMenu::create(pHelpItem, NULL);
	pSettingMenu->setPosition( CCPointZero );
	this->addChild(pSettingMenu, 1);
    pSettingMenu->setVisible(false);
    

	CCSize size = CCDirector::sharedDirector()->getWinSize();

    jump_height = height*0.3;
    CCSprite* bg = CCSprite::create("bg.png");
    bg->setPositionX(CCDirector::sharedDirector()->getWinSize().width/2);
    bg->setPositionY(CCDirector::sharedDirector()->getWinSize().height/2);
    bg->setScaleX(scale);
    bg->setScaleY(height_scale);

    
    hat_texture = CCTextureCache::sharedTextureCache()->addImage("hat.png");
    hat_texture_2 = CCTextureCache::sharedTextureCache()->addImage("hat_2.png");

    pSprite_a = CCSprite::createWithTexture(hat_texture);
    pSprite_a->setScale(scale);
    pSprite_b = CCSprite::createWithTexture(hat_texture);
    pSprite_b->setScale(scale);
    pSprite_c = CCSprite::createWithTexture(hat_texture);
    pSprite_c->setScale(scale);
    
    pShadow_a = CCSprite::create("shadow.png");
    pShadow_a->setScale(scale);
    pShadow_b = CCSprite::create("shadow.png");
    pShadow_b->setScale(scale);
    pShadow_c = CCSprite::create("shadow.png");
    pShadow_c->setScale(scale);
    
    double hat_height = pSprite_c->boundingBox().size.height;
    
    pCoin = CCSprite::create("coin.png");
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
	this->setTouchEnabled(true);

	return true;
}

void Play::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){

    pSettingMenu->setVisible(false);
    isFingerMoved = false;
    touchMoveCount = 0;
    touchMaxPoint = 0;

    for(CCSetIterator iterTouch = pTouches->begin(); iterTouch != pTouches->end(); iterTouch++)
    {
        CCTouch *pTouch =  (cocos2d::CCTouch*)(*iterTouch);
        m_touchPoint = pTouch->getLocation();
        m_touchPoint = CCDirector::sharedDirector()->convertToGL( m_touchPoint );
        
        if (pCoin->isVisible()) {
            CCRect touchRect = cocos2d::CCRectMake( m_touchPoint.x,  m_touchPoint.y, 30, 30);
            CCRect cionRect = pCoin->boundingBox();
            if(cionRect.intersectsRect(touchRect)){
                
                CCPoint touchPoint = pTouch->getLocation();
                touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );                        
                cocos2d::CCPoint delta = ccpSub(touchPoint, pCoin->getPosition());
                cocos2d::CCPoint p = pCoin->getPosition();
                pCoin->setPosition(ccpAdd(p, delta));
                
                if(pSprite_a->boundingBox().intersectsRect(cionRect)){
                    isInCup = true;
                }else if(pSprite_b->boundingBox().intersectsRect( cionRect)){
                    isInCup = true;
                }else if(pSprite_c->boundingBox().intersectsRect( cionRect)) {
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
    node->setVisible(false);
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
        CCPoint _touchPoint = pTouch->getLocation();
        _touchPoint = CCDirector::sharedDirector()->convertToGL( _touchPoint );
        
        if (_touchPoint.x!=m_touchPoint.x&&_touchPoint.y!=m_touchPoint.y) {
            isFingerMoved = true;
        }
        
        if (pCoin->isVisible()) {
          
            CCRect touchRect = cocos2d::CCRectMake( _touchPoint.x,  _touchPoint.y, 30, 30);
            CCRect cionRect = pCoin->boundingBox();
            if(cionRect.intersectsRect(touchRect)){
                CCPoint touchPoint = pTouch->getLocation();
                touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );                        
                cocos2d::CCPoint delta = ccpSub(touchPoint, pCoin->getPosition());
                cocos2d::CCPoint p = pCoin->getPosition();
                pCoin->setPosition(ccpAdd(p, delta));
                
                if (!isInCup) {
                    if(pSprite_a->boundingBox().intersectsRect(cionRect)){
                        CCMoveTo* moveto = CCMoveTo::create(0.8,shadow_pointe_a);
                        CCMoveTo* moveto2 = CCMoveTo::create(0.2, pointe_a);
                        CCScaleTo* iconsc=CCScaleTo::create(1, 0.6*this->scale);  
                        pCoin->runAction( CCSpawn::create(CCSequence::create(moveto,moveto2,CCCallFuncN::create(pCoin,callfuncN_selector(Play::setInvisible)),NULL),iconsc, NULL));
                      
                        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*this->scale);
                        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*this->scale);
                        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
                        pShadow_a->runAction(sq1);
  
                        
                        CCJumpTo* jump = CCJumpTo::create(1,pointe_a,height*0.2,1);
                        pSprite_a->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_a,callfuncN_selector(Play::closeHat)), NULL));
                        pSprite_a->setTexture(hat_texture_2);
                        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                        isLayoutCoin = false;
                    }else if(pSprite_b->boundingBox().intersectsRect( cionRect)){
                        
                       // CCJumpTo* jumpto = CCJumpTo::create(1, pointe_b,jump_height,1);
                        CCMoveTo* moveto = CCMoveTo::create(0.8, shadow_pointe_b);
                        CCMoveTo* moveto2 = CCMoveTo::create(0.2, pointe_b);
                        CCScaleTo* iconsc=CCScaleTo::create(1, 0.6*this->scale); 
                        pCoin->runAction( CCSpawn::create(CCSequence::create(moveto,moveto2,CCCallFuncN::create(pCoin,callfuncN_selector(Play::setInvisible)),NULL),iconsc, NULL));
                        
                        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*this->scale);
                        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*this->scale);
                        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
                        pShadow_b->runAction(sq1);
                        
                        CCJumpTo* jump = CCJumpTo::create(1, pointe_b,height*0.2,1);
                        pSprite_b->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_b,callfuncN_selector(Play::closeHat)), NULL));
                        pSprite_b->setTexture(hat_texture_2);
                        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                        isLayoutCoin = false;
                    }else if (pSprite_c->boundingBox().intersectsRect(cionRect)) {
                        
                        CCMoveTo* moveto = CCMoveTo::create(0.8, shadow_pointe_c);
                        CCMoveTo* moveto2 = CCMoveTo::create(0.2, pointe_c);
                        CCScaleTo* iconsc=CCScaleTo::create(1, 0.8*this->scale); 

                        pCoin->runAction( CCSpawn::create(CCSequence::create(moveto,moveto2,CCCallFuncN::create(pCoin,callfuncN_selector(Play::setInvisible)),NULL),iconsc, NULL));
                        
                        
                        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*this->scale);
                        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*this->scale);
                        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
                        pShadow_c->runAction(sq1);
                        
                        
                        CCJumpTo* jump = CCJumpTo::create(1, pointe_c,height*0.2,1);
                        pSprite_c->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_c,callfuncN_selector(Play::closeHat)), NULL));
                        pSprite_c->setTexture(hat_texture_2);
                        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                        isLayoutCoin = false;
                    }
                }else {
                    if(pSprite_a->boundingBox().intersectsRect(cionRect)){
                       
                    }else if(pSprite_b->boundingBox().intersectsRect( cionRect)){
                        
                    }else if (pSprite_c->boundingBox().intersectsRect(cionRect)) {
                        
                    }else {
                        isInCup = false;
                    }
                }
            }else{
             
                // CCJumpTo* jump = CCJumpTo::create(0.5, pCoin->getPosition(),10,1);
                // pCoin->runAction( CCSequence::actions(jump, NULL));
            }
        }else{
            
            if (isLayoutCoin) {
                
            }else {
                if(isFingerMoved&&touchMoveCount>3){
                    if (pTouch->getPreviousLocation( ).x<size.width/2) {
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
        if (!pCoin->isVisible()) {
            isLayoutCoin = false;
            if (!isFingerMoved) {
                
                CCTouch *pTouch =  (cocos2d::CCTouch*)(*iterTouch);
                CCPoint touchPoint = pTouch->getLocation();
                touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
                CCRect touchRect = cocos2d::CCRectMake( touchPoint.x,  touchPoint.y, 5, 5);
                CCRect coinbb ;
                coinbb.size.width = pSprite_a->boundingBox().size.width;
                coinbb.size.height = pSprite_a->boundingBox().size.height;
                coinbb.origin.x = pCoin->getPositionX()-pSprite_a->boundingBox().size.width/2;
                coinbb.origin.y = pCoin->getPositionY()-pSprite_a->boundingBox().size.height/2;
                
                if( coinbb.intersectsRect(touchRect)){
                    CCPoint point = pCoin->getPosition();
                    point.y=height*0.2;
                    CCMoveTo* moveto = CCMoveTo::create(1, point);
                    pCoin->setScale(0.6*this->scale);
                    CCScaleTo* scale=CCScaleTo::create(1, this->scale); 
                    CCRotateTo *rot = CCRotateTo::create(0.1, 20);
                    CCRotateTo *rot2 = CCRotateTo::create(0.1, -20);
                    CCRotateTo *rot3 = CCRotateTo::create(0.1, 10);
                    CCRotateTo *rot4 = CCRotateTo::create(0.1, -10);
                    CCRotateTo *rot5 = CCRotateTo::create(0.1, 0);
                    pCoin->runAction( CCSpawn::create(scale,CCSequence::create(moveto,CCCallFuncN::create(pCoin,callfuncN_selector(Play::playCoinMp3)),rot,rot2,rot3,rot4,rot5,NULL),NULL));
                    pCoin->setVisible(true);
                    isLayoutCoin = true;
                    isInCup = false;
                }
                
               
                if(pSprite_a->boundingBox().intersectsRect(touchRect)){
                    
                    CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
                    CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
                    CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
                    pShadow_a->runAction(sq1);
                    CCJumpTo* jump = CCJumpTo::create(1, pointe_a,height*0.2,1);
                    pSprite_a->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_a,callfuncN_selector(Play::closeHat)), NULL));
                    pSprite_a->setTexture(hat_texture_2);
                    SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                }else if(pSprite_b->boundingBox().intersectsRect(touchRect)){
                    CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
                    CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
                    CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
                    pShadow_b->runAction(sq1);
                    
                    CCJumpTo* jump = CCJumpTo::create(1, pointe_b,height*0.2,1);
                    pSprite_b->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_b,callfuncN_selector(Play::closeHat)), NULL));
                    pSprite_b->setTexture(hat_texture_2);
                    SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");

                }else if (pSprite_c->boundingBox().intersectsRect( touchRect)) {
                    CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
                    CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
                    CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
                    pShadow_c->runAction(sq1);
                    
                    CCJumpTo* jump = CCJumpTo::create(1, pointe_c,height*0.2,1);
                    pSprite_c->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_c,callfuncN_selector(Play::closeHat)), NULL));
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
        
        CCJumpTo* jump2b = CCJumpTo::create(switch_speed, pointe_b,height*0.2,1);
        CCJumpTo* jump2a = CCJumpTo::create(switch_speed, pointe_a,height*0.2,1);
        
        pSprite_a->runAction(CCSequence::create(jump2b,NULL));
        pSprite_b->runAction(CCSequence::create(jump2a,NULL));
        
        CCMoveTo* move2b = CCMoveTo::create(switch_speed, shadow_pointe_b);
        CCMoveTo* move2a = CCMoveTo::create(switch_speed, shadow_pointe_a);
        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCScaleTo* sc3 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc4 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
        CCFiniteTimeAction *sq2 = CCSequence::create(sc3,sc4,NULL);

        pShadow_a->runAction(CCSpawn::create(move2b,sq1,NULL));
        pShadow_b->runAction(CCSpawn::create(move2a,sq2,NULL));
        
        
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
        
        CCJumpTo* jump2b = CCJumpTo::create(switch_speed, pointe_b,height*0.2,1);
        CCJumpTo* jump2c = CCJumpTo::create(switch_speed, pointe_c,height*0.2,1);
        
        pSprite_c->runAction(CCSequence::create(jump2b,NULL));
        pSprite_b->runAction(CCSequence::create(jump2c,NULL));
        
        CCMoveTo* move2b = CCMoveTo::create(switch_speed, shadow_pointe_b);
        CCMoveTo* move2c = CCMoveTo::create(switch_speed, shadow_pointe_c);
        
        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCScaleTo* sc3 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc4 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
        CCFiniteTimeAction *sq2 = CCSequence::create(sc3,sc4,NULL);
        
        pShadow_c->runAction(CCSpawn::create(move2b,sq1,NULL));
        pShadow_b->runAction(CCSpawn::create(move2c,sq2,NULL));
        
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

    if (!pCoin->isVisible()) {
        CCRect cionRect = pCoin->boundingBox();
        if(pSprite_a->boundingBox().intersectsRect(cionRect)){
            pCoin->setPosition(pointe_b);
        }else if(pSprite_b->boundingBox().intersectsRect( cionRect)){
            pCoin->setPosition(pointe_a);
        }
        
    }
    }
}
void Play::switchRightCion(){
    
    if (pSprite_b->numberOfRunningActions()==0&&pSprite_c->numberOfRunningActions()==0) {

    if (!pCoin->isVisible()) {
        CCRect cionRect = pCoin->boundingBox();
        if(pSprite_b->boundingBox().intersectsRect(cionRect)){
            pCoin->setPosition(pointe_c);
        }else if (pSprite_c->boundingBox().intersectsRect(cionRect)) {
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
    if (pCoin->isVisible()==false) {
        CCPoint point = pCoin->getPosition();
        point.y=height*0.2;

        CCMoveTo* moveto = CCMoveTo::create(1, point);
        pCoin->setScale(0.6*this->scale);
        CCScaleTo* scale=CCScaleTo::create(1, this->scale); 
        CCRotateTo *rot = CCRotateTo::create(0.1, 20);
        CCRotateTo *rot2 = CCRotateTo::create(0.1, -20);
        CCRotateTo *rot3 = CCRotateTo::create(0.1, 10);
        CCRotateTo *rot4 = CCRotateTo::create(0.1, -10);
        CCRotateTo *rot5 = CCRotateTo::create(0.1, 0);
        pCoin->runAction( CCSpawn::create(scale,CCSequence::create(moveto,CCCallFuncN::create(pCoin,callfuncN_selector(Play::playCoinMp3)),rot,rot2,rot3,rot4,rot5,NULL),NULL));
    }
   
    pCoin->setVisible(true);
    isLayoutCoin = true;
    isInCup = false;

    if(pSprite_a->boundingBox().intersectsRect(pCoin->boundingBox())){
        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
        pShadow_a->runAction(sq1);
        
        CCJumpTo* jump = CCJumpTo::create(1, pointe_a,height*0.2,1);
        pSprite_a->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_a,callfuncN_selector(Play::closeHat)), NULL));
       
        pSprite_a->setTexture(hat_texture_2);
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        

    }else if(pSprite_b->boundingBox().intersectsRect(pCoin->boundingBox())){
        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
        pShadow_b->runAction(sq1);
        CCJumpTo* jump = CCJumpTo::create(1, pointe_b,height*0.2,1);
        pSprite_b->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_b,callfuncN_selector(Play::closeHat)), NULL));
        pSprite_b->setTexture(hat_texture_2);
        SimpleAudioEngine::sharedEngine()->playEffect("hat.mp3");
        


    }else if (pSprite_c->boundingBox().intersectsRect(pCoin->boundingBox())) {
        CCScaleTo* sc1 = CCScaleTo::create(switch_speed/2.0, 0.6*scale);
        CCScaleTo* sc2 = CCScaleTo::create(switch_speed/2.0, 1*scale);
        CCFiniteTimeAction *sq1 = CCSequence::create(sc1,sc2,NULL);
        pShadow_c->runAction(sq1);
        CCJumpTo* jump = CCJumpTo::create(1, pointe_c,height*0.2,1);
        pSprite_c->runAction( CCSequence::create(jump,CCCallFuncN::create(pSprite_c,callfuncN_selector(Play::closeHat)), NULL));
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
    pSettingMenu->setVisible(true);

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
