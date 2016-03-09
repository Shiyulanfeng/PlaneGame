//
//  ScoreScene.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__ScoreScene__
#define __PlaneGame__ScoreScene__

#include "cocos2d.h"
USING_NS_CC;

class ScoreScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    
    void backToMain(Ref *sender);
    
    CREATE_FUNC(ScoreScene);
};


#endif /* defined(__PlaneGame__ScoreScene__) */
