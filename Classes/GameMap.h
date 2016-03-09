//
//  GameMap.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__GameMap__
#define __PlaneGame__GameMap__

#include "cocos2d.h"
USING_NS_CC;

typedef enum{
    mapTag1 = 0,
    mapTag2,
    
}tagMap;//枚举两张地图背景的交替出现

class GameMap : public Layer
{
public:
    static GameMap* createMap(const char *mapName);
    
private:
    
    void initMap(const char *mapName);
    
    void update(float delta);
    
    void onExit();
    
    CREATE_FUNC(GameMap);
};


#endif /* defined(__PlaneGame__GameMap__) */
