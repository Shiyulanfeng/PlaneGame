//
//  GameEnemy.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "GameEnemy.h"
#include "GameScene.h"

USING_NS_CC;

GameEnemy* GameEnemy::createEnemy(const char *enemyName, int enemyType)
{
    GameEnemy *enemy = new GameEnemy();
    if (enemy && enemy->initWithFile(enemyName)) {
        enemy->initEnemy(enemyName, enemyType);
        enemy->autorelease();
        return enemy;
    }
    else
    {
        CC_SAFE_DELETE(enemy);
        return NULL;
    }
}

void GameEnemy::initEnemy(const char *enemyName, int enemyType)
{
    //为敌人创建动画效果
    this->createAnimate(enemyName, 10);
    
    Size size = Director::getInstance()->getWinSize();
    typeEnemy = enemyType;
    
    if (enemyType == 0) {
        scoreValue = 100;
    }else if (enemyType == 1)
    {
        scoreValue = 200;
    }else{
        scoreValue = 400;
    }
    
    //X在屏幕内随机位置
    this->setPosition(Point(CCRANDOM_0_1()*size.width, size.height+this->getContentSize().height));
    //敌人的运动逻辑
    this->scheduleUpdate();
}

//设置敌人的三种运动方式
void GameEnemy::update(float delta)
{
    switch (typeEnemy)
    {
        case 0:
        {
            //每帧下降3个像素
            this->setPosition(this->getPosition() + Point(0, -6));
            break;
        }
        case 1:
        {
            //判断防止重复调用此动作，保证此逻辑只会执行一次
            if (isActive) {
                break;
            }
            isActive = true;
            MoveTo *moveto1 = MoveTo::create(0.8, GameScene::getGamescene()->getPlayer()->getPosition());
            MoveTo *moveto2 = MoveTo::create(0.8, this->getPosition());
            Sequence *sequence = Sequence::create(moveto1, DelayTime::create(0.5), moveto2, NULL);
            this->runAction(sequence);
            break;
        }
        case 2:
        {
            if (isActive) {
                break;
            }
            isActive = true;
            MoveTo *moveto1 = MoveTo::create(0.6, GameScene::getGamescene()->getPlayer()->getPosition());
            MoveTo *moveto2 = MoveTo::create(0.8, this->getPosition());
            Sequence *sequence = Sequence::create(moveto1, DelayTime::create(1),moveto2, NULL);
            this->runAction(sequence);
        }
            break;
    }
    
    //碰撞检测，若有碰撞调用主角掉血函数downHP
    GamePlayer *player = GameScene::getGamescene()->getPlayer();
    if (!player->isDead) {
        if (player->boundingBox().intersectsRect(this->boundingBox())) {
            //调用主角掉血函数
            player->downHP();
        }
    }
    
    //删除enemy
    if (this->getPositionY() <= -this->getContentSize().height) {
        //从敌人数组中删除this这个敌人
        GameScene::getGamescene()->getEnemyArray()->eraseObject(this);
        //从父类中删除敌人
        this->getParent()->removeChild(this, true);
    }
}

void GameEnemy::createAnimate(const char *enemyName, int enemyCount)
{
    Animation *animation = Animation::create();
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(enemyName);
    //每个切片的宽度
    int enemyWidth = this->getContentSize().width / enemyCount;
    int enemyHeight = this->getContentSize().height;
    //循环遍历，将切片中的enemy对象逐个加入animation中
    for (int i = 0; i < enemyCount; i++) {
        animation->addSpriteFrameWithTexture(texture, Rect(i * enemyWidth, 0, enemyWidth, enemyHeight));
    }
    animation->setDelayPerUnit(0.5f);//必须设置否则不会动态播放
    animation->setRestoreOriginalFrame(true);//设置是否回到第一帧
    animation->setLoops(-1);//设置动画循环次数，-1为无限循环
    
    Animate *animate = Animate::create(animation);
    this->runAction(animate);
}

void GameEnemy::onExit()
{
    this->unscheduleUpdate();
    Sprite::onExit();
}
