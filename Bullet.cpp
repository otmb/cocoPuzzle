//
//  Bullet.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#include "Bullet.h"

USING_NS_CC;

//コンストラクタ
Bullet::Bullet()
: _state(State::Moving)
{
}

Bullet* Bullet::create()
{
    
    auto node = new Bullet();
    node->init();
    node->autorelease();
    
    return node;
}

bool Bullet::init()
{
    if (!Sprite::initWithFile("ball.png")){
        return false;
    }
    
    this->setScale(0.13f * bulletSize);
    //this->setScale(0.043f * bulletSize);
    auto pBall = PhysicsBody::createCircle(bulletSize,
                                           PhysicsMaterial(1.0f, 0.6f, 0.3f));
    pBall->setDynamic(true);
    pBall->setRotationEnable(true);
    pBall->setMoment(PHYSICS_INFINITY);
    //log("%f",pBall->getMass());
    pBall->setMass(1.0f);
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

