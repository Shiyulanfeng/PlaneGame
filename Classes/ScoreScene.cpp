//
//  ScoreScene.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "ScoreScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* ScoreScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ScoreScene::create();
    scene->addChild(layer);
    return scene;
}

bool ScoreScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *background = Sprite::create("score_bg.png");
    background->setPosition(Point(background->getContentSize().width/2, visibleSize.height/2));
    this->addChild(background);
    
    Label *backMain = Label::createWithSystemFont("返回主菜单", "Helvetica", 23);
    backMain->setColor(Color3B(255, 255, 0));
    MenuItemLabel *backLabel = MenuItemLabel::create(backMain, CC_CALLBACK_1(ScoreScene::backToMain, this));
    backLabel->setPosition(0, -200);
    Menu *menu = Menu::create(backLabel, NULL);
    this->addChild(menu);
    
    //添加一个文本储存分数
    std::string scoreStr = "";
    //获取储存的分数
    std::string score = UserDefault::getInstance()->getStringForKey("user_score","-1").c_str();
    //判断当前是否为最高分
    if (atoi(score.c_str()) != -1) {
        //如果有最高分
        scoreStr += score;
    }else{
        scoreStr = "0";
    }
    
    //将分数以Label的形式添加到layer上并且显示
    Label* scoreLabel = Label::createWithSystemFont(scoreStr.c_str(), "Helvetica", 23);
    scoreLabel->setPosition(Point(visibleSize.width*0.5-50,visibleSize.height*0.5+40));
    scoreLabel->setColor(Color3B(255, 0, 0));
    this->addChild(scoreLabel);
    
    return true;
}

void ScoreScene::backToMain(Ref *sender)
{
    //切换到主界面
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, MainScene::createScene()));
}
