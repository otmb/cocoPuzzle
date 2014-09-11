//
//  DrawLine.h
//  Puzzle2
//
//  Created by otmb on 2014/09/11.
//
//

#ifndef __Puzzle2__DrawLine__
#define __Puzzle2__DrawLine__

#include "cocos2d.h"

USING_NS_CC;

class DrawLine : public DrawNode
{
protected:
    DrawNode* _node;
    std::vector<Vec2*>*  _vects;
    
public:
    DrawLine(std::vector<Vec2*>*);
    static DrawLine* create(std::vector<Vec2*>*);
    virtual bool init();
    void remove();
};


#endif /* defined(__Puzzle2__DrawLine__) */
