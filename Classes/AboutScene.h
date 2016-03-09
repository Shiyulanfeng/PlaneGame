//
//  AboutScene.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__AboutScene__
#define __PlaneGame__AboutScene__

#include "cocos2d.h"
USING_NS_CC;

class AboutScene : public Layer
{
public:
    static Scene* creatScene();
    
    virtual bool init();
    
    void backToMain(Ref *sender);
    
    CREATE_FUNC(AboutScene);
};

#endif /* defined(__PlaneGame__AboutScene__) */
