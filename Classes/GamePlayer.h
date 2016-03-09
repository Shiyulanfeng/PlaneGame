//
//  GamePlayer.h
//  PlaneGame
//
//  Created by the 9 on 14-7-8.
//
//

#ifndef __PlaneGame__GamePlayer__
#define __PlaneGame__GamePlayer__

#include "cocos2d.h"
#include <sstream>
USING_NS_CC;
using namespace std;

//主要用于将int float 等数字转换成string类型
template <typename T>
string Convert2String(const T &value)
{
	stringstream ss;
	ss << value;
	return ss.str();
}

class GamePlayer : public Sprite
{
public:
    
    int hp;//主角血量
    int score;//分数
    int killCount;//杀敌数
    bool isDead;//判断主角是否死亡
    
    void addScore(float value);//增加分数
    void addKillCount(float num);//增加杀敌数
    
    void downHP();//掉血
    static GamePlayer* createPlayer(const char* playerName);
    
private:
    bool isStrong;//判断是否为无敌状态
    int strongTime;//无敌时间
    int strongCount;//无敌时间计时器
    void initPlayer();//初始化主角函数
    void playerStrong(float dt);//处理无敌时的闪烁等处理
    
};

#endif /* defined(__PlaneGame__GamePlayer__) */
