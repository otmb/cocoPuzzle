//
//  Dialog.h
//  Puzzle2
//
//  Created by otmb on 2014/09/10.
//
//

#ifndef __Puzzle2__Dialog__
#define __Puzzle2__Dialog__

#include "cocos2d.h"

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class UIDialog : public Layer
{
protected:
    Layer* _uiLayer;
    Widget::ccWidgetTouchCallback& _callback;
    //void close();
    
public:
    UIDialog(Widget::ccWidgetTouchCallback& callback);
    static UIDialog* create(Widget::ccWidgetTouchCallback& callback);
    virtual bool init();
    void close();
};

#endif /* defined(__Puzzle2__Dialog__) */
