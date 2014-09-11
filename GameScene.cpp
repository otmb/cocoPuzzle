//
//  GameScene.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/05.
//
//

#include "GameScene.h"
#include "Bullet.h"
#include "UIDialog.h"
#include "DrawLine.h"

USING_NS_CC;

#define MAX_BULLET 45

Scene* GameScene::createScene()
{
    
    //物理演算を使う為にcreateWithPhysicsを使用
    auto scene = Scene::createWithPhysics();
    
    //Worldに対して重力をセット
    //Vect gravity;
    //gravity.setPoint(0, -50);
    scene->getPhysicsWorld()->setGravity(Vec2(0, -98.0));
    scene->getPhysicsWorld()->setSpeed(4.0f);
    
    //物理オブジェクトにを可視的にしてくれるデバックモード
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}
#include <functional>

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if (!Layer::init())
        return false;
    
    auto winSize = Director::getInstance()->getWinSize();
    
    Vec2 vec[6] =
    {
        Vec2(winSize.width-1, winSize.height -1),
        Vec2(1, winSize.height -1),
        Vec2(1, 100),
        Vec2(winSize.width/2, 0),
        Vec2(winSize.width-1,100),
        Vec2(winSize.width-1,winSize.height -1),
    };
    
    auto wall = Node::create();
    //wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 5, PhysicsMaterial(0.1f, 1.0f, 0.0f)));
    // 密度、反発、摩擦
    wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 6, PhysicsMaterial(0.0f, 0.0f, 0.5f)));
    wall->setPosition(0, 0);
    addChild(wall);
    
    initTouchEvent();
    scheduleUpdate();
    
    Button* button = Button::create("Bullet.png");
    button->setPosition(Vec2(winSize.width,winSize.height - 50));
    button->addTouchEventListener(CC_CALLBACK_2(GameScene::touchEvent, this));
    addChild(button);
    
    _bulletVicts = new std::vector<Vec2*>();

    return true;
}

void GameScene::touchEvent(Ref *pSender, Widget::TouchEventType type)
{
    //std::function<void(Ref*,Widget::TouchEventType)> callback = CC_CALLBACK_0(GameScene::dialogClose,this);
    Widget::ccWidgetTouchCallback callback = CC_CALLBACK_0(GameScene::dialogClose,this);
    _dialog = UIDialog::create(callback);
    addChild(_dialog,Z_Dialog,T_Dialog);
}

//void GameScene::dialogClose(Ref *pSender, Widget::TouchEventType type)
void GameScene::dialogClose()
{
    auto nodes = getChildren();
    
    for (auto node : nodes)
    {
        switch (node->getTag())
        {
            case T_Dialog:
                UIDialog* dialog = static_cast<UIDialog*>(node);
                dialog->close();
                break;
        }
    }
}

void GameScene::update(float dt)
{
    _time += dt;
    
    // 弾の発射判定
    if (MAX_BULLET > _bullet) showBullet();
    
    // 線を引く
    DrawLine* node = DrawLine::create(_bulletVicts);
    addChild(node,Z_Line,T_Line);
}

void GameScene::showBullet(){
    auto bullet = Bullet::create();
    
    //srand((unsigned int)time(NULL));
    int tagNum = arc4random()%5;
    bullet->setColor(_tagColor[tagNum]);
    
    auto winSize = Director::getInstance()->getWinSize();
    bullet->setPosition(winSize.width/2, winSize.height - bullet->bulletSize);
    
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
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
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
    
    //_bullets = Vector<Bullet*>();
    //std::vector<Vec2*> * _bulletVicts = new std::vector<Vec2*>();
    
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
            _bullets.pushBack(bullet);
            _bulletVicts->push_back(new Vec2(bullet->getPosition()));
        }
    }
    
    //DrawLine* node = DrawLine::create();
    //addChild(node);
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    for (auto* bullet : _bullets){
        if (bullet->getState() == Bullet::State::Moving){
             bullet->brokenBullet();
            _bullet--;
        }
    }
    _bullets = Vector<Bullet*>();
    _bulletVicts = new std::vector<Vec2*>();
    DrawLineRemove();
}

void GameScene::DrawLineRemove()
{
    auto nodes = getChildren();
    
    for (auto node : nodes)
    {
        switch (node->getTag())
        {
            case T_Line:
                DrawLine* line = static_cast<DrawLine*>(node);
                line->remove();
                break;
        }
    }
}
