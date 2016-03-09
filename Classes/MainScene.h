//
//  MainScene.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__MainScene__
#define __PlaneGame__MainScene__

#include "cocos2d.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "AboutScene.h"
USING_NS_CC;

class MainScene : public Layer
{
public:
    static Scene* createScene();
    
    virtual bool init();
    
    void menuPlayCallback(Ref* pSender);
    void menuAboutCallback(Ref* pSender);
    void menuScoreCallback(Ref* pSender);
    
    CREATE_FUNC(MainScene);
};


#endif /* defined(__PlaneGame__MainScene__) */
