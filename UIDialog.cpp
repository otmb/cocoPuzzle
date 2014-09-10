//
//  Dialog.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/10.
//
//

#include "UIDialog.h"
#include "extensions/cocos-ext.h"
//#include "ui/CocosGUI.h"

using namespace ui;

UIDialog::UIDialog(Widget::ccWidgetTouchCallback& callback)
: _callback(callback) ,_uiLayer(nullptr)
{
}

UIDialog* UIDialog::create(Widget::ccWidgetTouchCallback& callback)
{
    auto dialog = new UIDialog(callback);
    dialog->init();
    dialog->autorelease();
    return dialog;

}

#define kModalLayerPriority -1

bool UIDialog::init()
{
    if (!Layer::init())
        return false;
    
    _uiLayer = Layer::create();
    addChild(_uiLayer);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *touch,Event*event)->bool{
        return true;
    };
    auto dip = Director::getInstance()->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, this);
    dip->setPriority(listener, kModalLayerPriority);
    
    auto size = Director::getInstance()->getVisibleSize();
    ui::ScrollView* sc = ui::ScrollView::create();
    sc->setContentSize(size);
    sc->setBackGroundColor(Color3B::GREEN);
    sc->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    sc->setBounceEnabled(true);
    sc->setDirection(ui::ScrollView::Direction::VERTICAL);
    sc->setContentSize(Size(480,size.height));
    sc->setInnerContainerSize(Size(480, sc->getContentSize().height + 300 ));
    
    sc->setPosition(Vec2((size.width - sc->getContentSize().width) / 2, size.height - sc->getContentSize().height ));
    
    Button* button = Button::create("Bullet.png");
    button->setPosition(Vec2(240,320));
    button->addTouchEventListener(_callback);
    sc->addChild(button);
    
    
    auto s = sc->getContentSize();
    
    Text *alert = Text::create("What's New", "fonts/Marker Felt.ttf", 30);
    alert->setColor(Color3B(159, 168, 176));
    alert->setPosition( Vec2(s.width / 2.0f, s.height/2+50) );
    addChild(alert);
    
    alert = Text::create("Tap Start", "fonts/Marker Felt.ttf", 30);
    alert->setColor(Color3B(159, 168, 176));
    alert->setPosition(Vec2(sc->getContentSize().width / 2.0f, sc->getContentSize().height / 2.0f - alert->getContentSize().height * 3.125));
    sc->addChild(alert);
    
    _uiLayer->addChild(sc);
    
    return true;
}

void UIDialog::close()
{
    Action* action = RemoveSelf::create();
    runAction(action);
}
