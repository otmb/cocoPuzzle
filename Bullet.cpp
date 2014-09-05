//
//  Bullet.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#include "Bullet.h"

USING_NS_CC;

#define CIRCLE_SIZE 45.0f

//コンストラクタ
Bullet::Bullet()
: _state(State::Moving)
{
}

bool Bullet::init()
{
    if (!Sprite::initWithFile("Bullet.png")){
        return false;
    }
    
    //this->setColor(Color3B(255,255,255));
    auto pBall = PhysicsBody::createCircle(CIRCLE_SIZE);
    pBall->setDynamic(true);
    pBall->setRotationEnable(true);
    //log("%f",pBall->getMass());
    //pBall->setMass(10000.0f);
    this->setPhysicsBody(pBall);
    
    return true;
}

void Bullet::brokenBullet()
{
    stopAllActions();
    // 弾を消すアクションを起こす
    Action* action = RemoveSelf::create();
    runAction(action);
    
    _state = State::Broken;
}

