#ifndef SHIP_H
#define SHIP_H
#include "Image.h"
#include "Includes.h"
#include "Rect.h"
#include "Surface.h"
#include "Event.h"
#include "Constants.h"
class Ship
{
private:
    int x_, y_;  
    Rect myrect;
    Image & image_;
    Surface & surface_;
    int speed;
    bool moveLeft;
    
public:
Ship(int x, int y, Surface & surface, Image & player)
    :x_(x), y_(y), surface_(surface), image_(player),moveLeft(true),speed(5)
    {
        myrect = image_.getRect();
        myrect.x = x_;
        myrect.y = y_;       
    }
     void move(bool moveLeft);
     void draw();
   
};
#endif
     
   
