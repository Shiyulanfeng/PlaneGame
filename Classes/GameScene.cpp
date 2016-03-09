//
//  GameScene.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameMap.h"
#include "GameBullet.h"
#include "GameEnemy.h"
#include "MainScene.h"
USING_NS_CC;
using namespace CocosDenshion;

static GameScene* gameScene = NULL;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    gameScene = this;//用于获得GameScene的实例对象
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("gameMusic.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("gameMusic.mp3", true);
    
    SimpleAudioEngine::getInstance()->preloadEffect("effect_bullet.mp3");
    
    //创建背景地图
    GameMap *map = GameMap::createMap("map.png");
    this->addChild(map);
    
    //创建主角精灵
    GamePlayer *player = GamePlayer::createPlayer("player.png");
    this->addChild(player, 1, playerTag);
    
    //每隔一段时间创建一个子弹
    this->schedule(schedule_selector(GameScene::bulletShow), 0.37f);
    
    //每隔一段时间随机创建数个敌人
    this->schedule(schedule_selector(GameScene::enemyShow), 1.0f);
    
    return true;
}

GameScene* GameScene::getGamescene()
{
    return gameScene;
}

GamePlayer* GameScene::getPlayer()
{
    GamePlayer *player = (GamePlayer *)GameScene::getGamescene()->getChildByTag(playerTag);
    return player;
}

//创建子弹
void GameScene::bulletShow(float dt)
{
    //获得主角精灵对象，以此确定子弹的初始位置
    GamePlayer *player = (GamePlayer *)this->getChildByTag(playerTag);
    GameBullet *bullet = GameBullet::createBullet("p_bullet.png", 8, player->getPosition() + Point(0,player->getContentSize().height*0.5));
    this->addChild(bullet, 9);
    //子弹音效
    SimpleAudioEngine::getInstance()->playEffect("effect_bullet.mp3");
}

//用于获得enemy数组，用于碰撞检测
std::shared_ptr<Vector<Sprite *>> GameScene::getEnemyArray()
{
    return enemyArray;
}

//周董创建怪物对象
void GameScene::enemyShow(float dt)
{
    int randomNum = CCRANDOM_0_1()*5;//随机生成0-10之间的怪物个数
    for (int i = 0; i < randomNum; i++) {
        int random=CCRANDOM_0_1()*10;//随机生成一个0到10之间的随机数
        GameEnemy *enemy = NULL;
        int randomType = CCRANDOM_0_1()*12;;
        
        //随机怪物的名字
        const char *enemyName;
        if(random>=0 && random<=2)
        {
            enemyName="enemy_bug.png";
        }
        else if(random>=3 && random<=6)
        {
            enemyName="enemy_duck.png";
        }
        else if(random>=7 && random<=10)
        {
            enemyName="enemy_pig.png";
        }
        
        //随机类型,用于控制不同怪物的不同得分，以及不同的攻击方式
        if (randomType % 3 == 0) {
            randomType = 0;
        }else if (randomType % 3 == 1){
            randomType = 1;
        }else{
            randomType = 2;
        }
        enemy = GameEnemy::createEnemy(enemyName, randomType);
        enemyArray->pushBack(enemy);
        this->addChild(enemy);
        
    }
}

void GameScene::update(float delta)
{
    totalTime += delta;//每帧所用时间相加
}

void GameScene::winGame()
{
    //添加胜利画面
    Size visibleSize = Director::getInstance()->getWinSize();
    LayerColor *layer = LayerColor::create(Color4B(0, 0, 0, 190), visibleSize.width, visibleSize.height);
    Sprite *winSprite = Sprite::create("game_win.png");
    winSprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    layer->addChild(winSprite);
    this->addChild(layer, 100);
    
    //添加一个按钮用于返回主界面
    Label *toMain = Label::createWithSystemFont("返回主菜单", "Helvetica-Bold", 23);
    MenuItemLabel *menuLabel = MenuItemLabel::create(toMain, CC_CALLBACK_1(GameScene::backToMain, this));
    menuLabel->setPosition(Point(0, -200));
    Menu *menu = Menu::create(menuLabel, NULL);
    this->addChild(menu, 100);
    
    //暂停游戏
    Director::getInstance()->pause();
    
    _eventDispatcher->pauseEventListenersForTarget(this->getChildByTag(playerTag));
}

//游戏失败函数
void GameScene::lostGame()
{
    
    
    //添加失败界面
    Size visibleSize = Director::getInstance()->getWinSize();
    LayerColor *layer = LayerColor::create(Color4B(0, 0, 0, 190), visibleSize.width, visibleSize.height);
    Sprite *lostSprite = Sprite::create("game_lost.png");
    lostSprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    layer->addChild(lostSprite);
    this->addChild(layer, 100);
    
    
    
    //添加一个按钮用于返回主界面
    Label *toMain = Label::createWithSystemFont("返回主菜单", "Helvetica-Bold", 23);
    MenuItemLabel *menuLabel = MenuItemLabel::create(toMain, CC_CALLBACK_1(GameScene::backToMain, this));
    menuLabel->setPosition(Point(0, -200));
    Menu *menu = Menu::create(menuLabel, NULL);
    this->addChild(menu, 100);
    
    //暂停游戏
    Director::getInstance()->pause();
}

//返回主菜单函数
void GameScene::backToMain(Ref *sender)
{
    this->unscheduleUpdate();
    //继续游戏
    Director::getInstance()->resume();
    //切换到“主菜单”
    return Director::getInstance()->replaceScene(MainScene::createScene());
}
