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
Bullet::Bullet(Texture2D* texture)
: _node(nullptr), _texture(texture), _state(State::Moving)
{
}

Bullet* Bullet::create(Texture2D* texture)
{
    
    auto node = new Bullet(texture);
    node->init();
    node->autorelease();
    
    return node;
}

bool Bullet::init()
{
    if (!Sprite::init()){
        return false;
    }
    
    _node = Sprite::createWithTexture(_texture);
    //_node->setColor(_color);
    addChild(_node);
    
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

void Bullet::setColor(Color3B &color)
{
    _node->setColor(color);
}

void Bullet::brokenBullet()
{
    stopAllActions();
    // 弾を消すアクションを起こす
    Action* action = RemoveSelf::create();
    runAction(action);
    
    _state = State::Broken;
}

