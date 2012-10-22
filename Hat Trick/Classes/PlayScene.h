#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class Play : public cocos2d::CCLayer
{
public:
	virtual bool init();  

	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
    virtual void menuSettingCallback(CCObject* pSender);
    virtual void menuHelpCallback(CCObject* pSender);
    
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    void setInvisible(CCNode * node);
    void closeHat(cocos2d::CCSprite* node);
    void playCoinMp3(cocos2d::CCSprite* node);
    
    
    void switchLeftCup();
    void switchRightCup();
    void switchLeftCion();
    void switchRightCion();
    void speedup();
    void resetSpeed();
    // implement the "static node()" method manually
	CREATE_FUNC(Play);
    
    cocos2d::CCSprite* pSprite_a;
    cocos2d::CCSprite* pSprite_b;
    cocos2d::CCSprite* pSprite_c;
    
    cocos2d::CCSprite* pShadow_a;
    cocos2d::CCSprite* pShadow_b;
    cocos2d::CCSprite* pShadow_c;
    
    cocos2d::CCSprite* pCoin;
    
    cocos2d::CCPoint pointe_a;
    cocos2d::CCPoint pointe_b;
    cocos2d::CCPoint pointe_c;
    
    cocos2d::CCTexture2D * hat_texture;
    cocos2d::CCTexture2D * hat_texture_2;

    
    cocos2d::CCPoint shadow_pointe_a;
    cocos2d::CCPoint shadow_pointe_b;
    cocos2d::CCPoint shadow_pointe_c;
    
    cocos2d::CCPoint m_touchPoint;
    bool isFingerMoved;    
    double switch_speed;
    bool isLayoutCoin;
    bool isInCup;
    int width;
    int height;
    float scale;
    
    
    int touchMoveCount;
    int touchMaxPoint;
    int speed;
    int jump_height;
    cocos2d::CCMenu* pMainMenu;
    cocos2d::CCMenu* pSettingMenu;
    
};

#endif // __PLAY_SCENE_H__
