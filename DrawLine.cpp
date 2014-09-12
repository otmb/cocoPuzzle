//
//  DrawLine.cpp
//  Puzzle2
//
//  Created by otmb on 2014/09/11.
//
//

#include "DrawLine.h"

DrawLine::DrawLine(std::vector<Vec2*>* vecs)
: _node(nullptr), _vects(vecs)
{
}

DrawLine* DrawLine::create(std::vector<Vec2*>* vecs)
{
    auto node = new DrawLine(vecs);
    node->init();
    node->autorelease();
    return node;
}

bool DrawLine::init()
{
    if (!DrawNode::init())
        return false;
    
    _node = DrawNode::create();
    addChild(_node);
    
    // from,to,radius,color
    Vec2* tmpVec = nullptr;
    if (_vects != nullptr){
        for(auto* vec : *_vects){
            
            if (tmpVec != nullptr){
                _node->drawSegment(Vec2(tmpVec->x,tmpVec->y), Vec2(vec->x,vec->y), 3, Color4F::WHITE);
                /*
                Point points[] = {
                    Point(tmpVec->x + 5,tmpVec->y + 5), Point(tmpVec->x -5,tmpVec->y -5) ,
                    Point(vec->x - 5,vec->y -5 ), Point(vec->x + 5,vec->y + 5)};
                _node->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F::WHITE, 1, Color4F::GREEN);
                */
            }
            tmpVec = vec;
        }
    }
    
    return true;
    
}

void DrawLine::remove()
{
    Action* action = RemoveSelf::create();
    runAction(action);
}