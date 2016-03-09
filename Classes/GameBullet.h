//
//  GameBullet.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__GameBullet__
#define __PlaneGame__GameBullet__

#include "cocos2d.h"
USING_NS_CC;

class GameBullet : public Sprite
{
public:
    //实例子弹函数
    static GameBullet* createBullet(const char *bulletName, float bulletSpeed, Point bulletPosition);
    
private:
    //初始化子弹函数
    void initBullet(float bulletSpeed, Point bulletPosition);
    
    float speed;//子弹移动的速度
    
    void update(float delta);//逐帧移动子弹
    
    void onExit();
    
};


#endif /* defined(__PlaneGame__GameBullet__) */
