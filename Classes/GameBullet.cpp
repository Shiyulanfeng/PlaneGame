//
//  GameBullet.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "GameBullet.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameEnemy.h"

using namespace CocosDenshion;
USING_NS_CC;

GameBullet* GameBullet::createBullet(const char *bulletName, float bulletSpeed, Point bulletPosition)
{
    GameBullet *bullet = new GameBullet();
    if (bullet && bullet->initWithFile(bulletName)) {
        bullet->initBullet(bulletSpeed, bulletPosition);
        bullet->autorelease();
        return bullet;
    }
    else
    {
        CC_SAFE_DELETE(bullet);
        return NULL;
    }
}

void GameBullet::initBullet(float bulletSpeed, Point bulletPosition)
{
    SimpleAudioEngine::getInstance()->preloadEffect("effect_boom.mp3");
    speed = bulletSpeed;
    this->setPosition(bulletPosition);
    this->scheduleUpdate();
}

void GameBullet::update(float delta)
{
    //每帧子弹上移speed个像素
    this->setPosition(this->getPosition() + Point(0, speed));
    //得到enemy数组
    shared_ptr<Vector<Sprite *>> array = GameScene::getGamescene()->getEnemyArray();
    //获得数组长度
    int arrayCount = array->size();
    //循环遍历enemy数组中每个元素，进行碰撞检测
    for (int i = 0; i < arrayCount; i++) {
        GameEnemy *enemy = (GameEnemy *)array->at(i);
        if (enemy->boundingBox().intersectsRect(this->boundingBox())) {
            //爆炸音效
            SimpleAudioEngine::getInstance()->playEffect("effect_boom.mp3");
            
            //爆炸粒子效果
            ParticleSystemQuad *particle = ParticleSystemQuad::create("particle_boom.plist");
            particle->setPosition(enemy->getPosition());//怪的位置
            particle->setAutoRemoveOnFinish(true);//结束后自动释放
            GameScene::getGamescene()->addChild(particle);
            
            //增加分数
            GameScene::getGamescene()->getPlayer()->addScore(enemy->scoreValue);
            
            //增加杀敌数
            GameScene::getGamescene()->getPlayer()->addKillCount(1);
            
            //从敌人数组中删除被击中的enemy
            array->eraseObject(enemy);
            //删除子弹与怪物
            GameScene::getGamescene()->removeChild(enemy, true);
            GameScene::getGamescene()->removeChild(this, true);
            
            break;
        }
    }
}

//子弹移出屏幕后删除
void GameBullet::onExit()
{
    //取消更新函数
    this->unscheduleUpdate();
    Sprite::onExit();
}
