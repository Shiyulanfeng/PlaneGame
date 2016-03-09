//
//  AboutScene.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "AboutScene.h"
#include "MainScene.h"

Scene* AboutScene::creatScene()
{
    auto scene = Scene::create();
    auto layer = AboutScene::create();
    scene->addChild(layer);
    return scene;
}

bool AboutScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *background = Sprite::create("about_bg.png");
    background->setPosition(Point(background->getContentSize().width/2, visibleSize.height/2));
    this->addChild(background);
    
    Label *backMain = Label::createWithSystemFont("返回主菜单", "Helvetica", 23);
    backMain->setColor(Color3B(255, 255, 0));
    MenuItemLabel *backLabel = MenuItemLabel::create(backMain, CC_CALLBACK_1(AboutScene::backToMain, this));
    backLabel->setPosition(0, -200);
    Menu *menu = Menu::create(backLabel, NULL);
    this->addChild(menu);
    
    return true;
}

void AboutScene::backToMain(Ref *sender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.5f, MainScene::createScene()));
}
