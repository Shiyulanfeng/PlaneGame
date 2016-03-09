//
//  GamePlayer.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "GamePlayer.h"
#include "GameScene.h"
USING_NS_CC;

GamePlayer* GamePlayer::createPlayer(const char* playerName)
{
    GamePlayer *player = new GamePlayer();
    if (player && player->initWithFile(playerName)) {
        player->initPlayer();
        player->autorelease();
        return player;
    }
    else
    {
        CC_SAFE_DELETE(player);
        return NULL;
    }
    
}

void GamePlayer::initPlayer()
{
    //设置主角初始位置
    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(visibleSize.width/2, this->getContentSize().height/2);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan=[](Touch *touch, Event *event)
    {
        return true;
    };
    
    listener->onTouchMoved=[](Touch *touch, Event *event)
    {
        auto target = static_cast<Sprite *>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //初始化三个主角血条
    for (int i = 0;  i < 3; i++) {
        Sprite *playerHP = Sprite::create("icon_hp.png");
        playerHP->setPosition((visibleSize.width)-(playerHP->getContentSize().width*i)-20, playerHP->getContentSize().height/2);
        if (i == 0) {
            playerHP->setTag(Hp1);
        }else if (i == 1){
            playerHP->setTag(Hp2);
        }else{
            playerHP->setTag(Hp3);
        }
        GameScene::getGamescene()->addChild(playerHP, 10);
    }
    
    
    strongTime = 2*60;//设置无敌时间为2秒
    hp = 3;//初始化血量为3
    score = 0;//初始化分数为0
    killCount = 0;//初始化杀敌数为0
    
    //初始化"分数"文字加入layer中
    Label *label = Label::createWithSystemFont("分数", "Arial", 24);
    label->setPosition(30,visibleSize.height-22);
    label->setColor(Color3B::BLACK);
    GameScene::getGamescene()->addChild(label);
    
    //将Score加入 “分数” 中
    std::string strScore = Convert2String(score);
    Label *labelScore = Label::createWithSystemFont(strScore.c_str(), "Arial", 24);
    labelScore->setPosition(Point(110,visibleSize.height-22));
    labelScore->setColor(Color3B(255, 255, 0));
    GameScene::getGamescene()->addChild(labelScore, 10, scoreTag);
    
    //杀敌人数
    Label* labelKill = Label::createWithSystemFont("杀敌:", "Arial-Blod", 24);
    labelKill->setPosition(Point(30,visibleSize.height-52));
    labelKill->setColor(Color3B::BLACK);
    GameScene::getGamescene()->addChild(labelKill,10);
    
    //杀敌数字加入layer中
    std::string strKillCount=Convert2String(killCount);
    strKillCount+="/100";
    Label* labelKillCount = Label::createWithSystemFont(strKillCount.c_str(), "Arial-Blod", 24);
    labelKillCount->setPosition(Point(110,visibleSize.height-52));
    labelKillCount->setColor(Color3B(255, 255, 0));
    GameScene::getGamescene()->addChild(labelKillCount,10,killCountTag);
}

//增加积分
void GamePlayer::addScore(float value)
{
    score += value;
    std::string strScore = Convert2String(score);
    Label *labelScore = (Label *)GameScene::getGamescene()->getChildByTag(scoreTag);
    labelScore->setString(strScore.c_str());
}

//增加杀敌数
void GamePlayer::addKillCount(float num)
{
    killCount += num;
    std::string strKillCount = Convert2String(killCount);
    strKillCount += "/100";
    Label *labelKillCount = (Label *)GameScene::getGamescene()->getChildByTag(killCountTag);
    labelKillCount->setString(strKillCount.c_str());
    
    if (killCount >= 100) {
        //储存分数
        int oldScore = atoi(UserDefault::getInstance()->getStringForKey("user_score", "-1").c_str());
        if (score > oldScore) {
            UserDefault::getInstance()->getStringForKey("user_score", Convert2String(score));
            UserDefault::getInstance()->flush();
        }
        
        //调用胜利画面
        GameScene::getGamescene()->winGame();
    }
}

//主角掉血函数（默认每次只掉一滴血）
void GamePlayer::downHP()
{
    if (isStrong) {
        return;
    }
    hp -= 1;//掉一滴血
    if (hp <= 0) {
        
        this->setVisible(false);
        isDead = true;
        
        //储存最高分数
        int oldScore = atoi(UserDefault::getInstance()->getStringForKey("user_score", "-1").c_str());
        if (score > oldScore) {
            UserDefault::getInstance()->setStringForKey("user_score", Convert2String(score));
            UserDefault::getInstance()->flush();
        }
        GameScene::getGamescene()->removeChildByTag(Hp1);
        //调用失败界面
        GameScene::getGamescene()->lostGame();
        //调用失败layer
    }else{
        //将界面血量更新
        switch (hp) {
            case 1:
                GameScene::getGamescene()->removeChildByTag(Hp2);
                break;
            case 2:
                GameScene::getGamescene()->removeChildByTag(Hp3);
                break;
        }
        //设置主角无敌时间
        isStrong = true;
        strongCount = 0;
        
        this->schedule(schedule_selector(GamePlayer::playerStrong));
    }
}

//处于无敌时间时的处理函数
void GamePlayer::playerStrong(float dt)
{
    strongCount++;
    if (strongCount % strongTime == 0) {
        this->setVisible(true);
        isStrong = false;
        this->unschedule(schedule_selector(GamePlayer::playerStrong));
    }else{
        //主角出于无敌状态时的闪烁
        if (strongCount%3 == 0) {
            this->setVisible(true);
        }else{
            this->setVisible(false);
        }
    }
}
