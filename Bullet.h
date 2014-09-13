//
//  Bullet.h
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#ifndef __Puzzle2__Bullet__
#define __Puzzle2__Bullet__

#include "cocos2d.h"

class Bullet : public cocos2d::Sprite
{
public:
    
    // 弾の状態
    enum class State
    {
        Moving, // 移動中
        Broken, // 壊れる
    };
    
    Bullet();
    static Bullet* create();
    virtual bool init();
    //CREATE_FUNC(Bullet);
    
    CC_SYNTHESIZE_READONLY(State, _state, State); // 弾の状態
    
    void brokenBullet(); // 弾が壊れる
    float const bulletSize = 45.0f;
};

#endif /* defined(__Puzzle2__Bullet__) */
