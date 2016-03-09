//
//  MainScene.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //播放背景音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("menuMusic.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("menuMusic.mp3", true);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *background = Sprite::create("menu_bg.png");
    background->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    this->addChild(background, 0);
    
    auto playItem = MenuItemImage::create(
                                          "play_nor.png",
                                          "play_pre.png",
                                          CC_CALLBACK_1(MainScene::menuPlayCallback, this));
    playItem->setPosition(Point(visibleSize.width/2, visibleSize.height/2+20));
    
    auto scoreItem = MenuItemImage::create(
                                           "score_nor.png",
                                           "score_pre.png",
                                           CC_CALLBACK_1(MainScene::menuScoreCallback, this));
    scoreItem->setPosition(Point(visibleSize.width/2, visibleSize.height/2-40));
    
    auto aboutItem = MenuItemImage::create(
                                           "about_nor.png",
                                           "about_pre.png",
                                           CC_CALLBACK_1(MainScene::menuAboutCallback, this));
    aboutItem->setPosition(Point(visibleSize.width/2, visibleSize.height/2-100));
    
    auto menu = Menu::create(playItem, aboutItem, scoreItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}

void MainScene::menuPlayCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    TransitionFade *fade = TransitionFade::create(0.5f, GameScene::createScene(), Color3B::RED);
    Director::getInstance()->replaceScene(fade);
}

void MainScene::menuAboutCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    TransitionFade *fade = TransitionFade::create(0.5f, AboutScene::creatScene(), Color3B::BLUE);
    Director::getInstance()->replaceScene(fade);
}

void MainScene::menuScoreCallback(Ref* pSender)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    TransitionFade *fade = TransitionFade::create(0.5f, ScoreScene::createScene(), Color3B::YELLOW);
    Director::getInstance()->replaceScene(fade);
}
