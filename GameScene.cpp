//
//  GameScene.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#include "GameScene.h"
#include "Bullet.h"

USING_NS_CC;

#define MAX_BULLET 45

Scene* GameScene::createScene()
{
    
    //物理演算を使う為にcreateWithPhysicsを使用
    auto scene = Scene::createWithPhysics();
    
    //Worldに対して重力をセット
    Vect gravity;
    gravity.setPoint(0, -50);
    scene->getPhysicsWorld()->setGravity(gravity);
    scene->getPhysicsWorld()->setSpeed(6.0f);
    
    //物理オブジェクトにを可視的にしてくれるデバックモード
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    Vec2 vec[5] =
    {
        Vec2(1, 700),
        Vec2(1, 100),
        Vec2(winSize.width/2, 0),
        Vec2(winSize.width-1,100),
        Vec2(winSize.width-1,700),
    };
    
    auto wall = Node::create();
    //wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 5, PhysicsMaterial(0.1f, 1.0f, 0.0f)));
    wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 5, PhysicsMaterial(0.0f, 0.0f, 0.0f)));
    wall->setPosition(0, 0);
    addChild(wall);
    initTouchEvent();
    scheduleUpdate();
    
    
    return true;
}


void GameScene::update(float dt)
{
    _time += dt;
    
    // 弾の発射判定
    if (MAX_BULLET > _bullet) showBullet();
}

void GameScene::showBullet(){
    auto bullet = Bullet::create();
    
    //srand((unsigned int)time(NULL));
    int tagNum = arc4random()%5;
    bullet->setColor(_tagColor[tagNum]);
    
    auto winSize = Director::getInstance()->getWinSize();
    bullet->setPosition(winSize.width/2, winSize.height);
    
    PhysicsBody* pBall = bullet->getPhysicsBody();
    pBall->setTag(T_Bullet);
    
    addChild(bullet,Z_Bullet,tagNum+2);
    _bullet++;
}

void GameScene::initTouchEvent()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
}

#define mark - タップイベント

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
    
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & T_Bullet) != 0)
        {
            _tag = static_cast<Bullet*>(obj->getBody()->getNode())->getTag();
            break;
        }
    }
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();
    auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
    
    Bullet* bullet = nullptr;
    for (auto& obj : arr)
    {
        if ((obj->getBody()->getTag() & T_Bullet) != 0)
        {
            bullet = static_cast<Bullet*>(obj->getBody()->getNode());
            if (bullet->getTag() == _tag){
                break;
            } else {
                bullet = nullptr;
            }
        }
    }
    if (bullet != nullptr){
        if (bullet->getState() == Bullet::State::Moving){
            bullet->brokenBullet();
            _bullet--;
        }
    }
}

