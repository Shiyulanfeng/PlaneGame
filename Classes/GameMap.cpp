//
//  GameMap.cpp
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#include "GameMap.h"
USING_NS_CC;

GameMap* GameMap::createMap(const char *mapName)
{
    GameMap *map = new GameMap();
    if (map && map->init()) {
        map->initMap(mapName);
        map->autorelease();
        return map;
    }
    else
    {
        CC_SAFE_DELETE(map);
        return NULL;
    }
}

void GameMap::initMap(const char *mapName)
{
    Sprite *map1 = Sprite::create("map.png");
    Sprite *map2 = Sprite::create("map.png");
    map1->setPosition(Point(map1->getContentSize().width*0.5, map1->getContentSize().height*0.5));
    map2->setPosition(Point(map2->getContentSize().width*0.5, map2->getContentSize().height*1.5));
    this->addChild(map1, 0, mapTag1);
    this->addChild(map2, 0, mapTag2);
    
    this->scheduleUpdate();
}

void GameMap::update(float delta)
{
    Sprite *map1 = (Sprite *)this->getChildByTag(mapTag1);
    if (map1->getPositionY() <= -map1->getContentSize().height/2) {
        map1->setPosition(map1->getContentSize().width/2, map1->getContentSize().height*1.5 -11.f);
        
    }
    else
    {
        map1->setPosition(map1->getPosition() + Point(0, -2.5f));
    }
    
    Sprite *map2 = (Sprite *)this->getChildByTag(mapTag2);
    if (map2->getPositionY() <= -map2->getContentSize().height/2) {
        map2->setPosition(map2->getContentSize().width/2, map2->getContentSize().height*1.5 - 11.f);
        
    }
    else
    {
        map2->setPosition(map2->getPosition() + Point(0, -2.5f));
    }
}

void GameMap::onExit()
{
    //接触更新函数
    this->unscheduleUpdate();
    Layer::onExit();
}
