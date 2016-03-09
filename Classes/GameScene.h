//
//  GameScene.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__GameScene__
#define __PlaneGame__GameScene__

#include "cocos2d.h"
#include "GamePlayer.h"
USING_NS_CC;

typedef enum{
    playerTag = 0,//主角
    Hp1,          //第一滴血
    Hp2,          //第二滴血
    Hp3,          //第三滴血
    scoreTag,    //分数
    killCountTag  //杀敌数
    
}nodeTag;//枚举变量

class GameScene : public Layer
{
public:
    static Scene* createScene();
    static GameScene* getGamescene();
    GamePlayer* getPlayer();
    //获取存放敌怪的数组
    std::shared_ptr<Vector<Sprite *>> getEnemyArray();
    
    void winGame();
    void lostGame();
    
private:
    
    float totalTime;//一共的时间
    
    virtual bool init();
    void bulletShow(float dt);//生成子弹
    void enemyShow(float dt); //生成敌对精灵
    
    void update(float delta);
    
    //存放敌怪的数组，碰撞检测怪物遍历时使用
    std::shared_ptr<Vector<Sprite *>> enemyArray = std::make_shared<Vector<Sprite *>>();
    
    void backToMain(Ref *sender);//返回菜单函数
    
    CREATE_FUNC(GameScene);
};


#endif /* defined(__PlaneGame__GameScene__) */
