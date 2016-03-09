//
//  GameEnemy.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__GameEnemy__
#define __PlaneGame__GameEnemy__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class GameEnemy : public Sprite
{
public:
    //实例化enemy函数
    static GameEnemy* createEnemy(const char *enemyName, int enemyType);
    //对应怪的分值
    int scoreValue;
private:
    
    int typeEnemy;//敌人类型
    bool isActive;//判断敌人是否有动作
    
    void initEnemy(const char *enemyName, int enemyType);
    
    void update(float delta);
    
    void createAnimate(const char *enemyName, int enemyCount);
    
    void onExit();
     
};

#endif /* defined(__PlaneGame__GameEnemy__) */
