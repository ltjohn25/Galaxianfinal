#ifndef SHIP_H
#define SHIP_H
#include "Image.h"
#include "Includes.h"
#include "Rect.h"
#include "Surface.h"
#include "Event.h"
#include "Constants.h"
class Ship //: public GameObject
{
private:
    int x_, y_; 
    Rect myrect;
    Image & image_;
    Surface & surface_;
    int speed;
    bool moveLeft;
    bool alive;
  
    
public:
Ship(int x, int y, Surface & surface, Image & player)
    :x_(x), y_(y), surface_(surface), image_(player),moveLeft(true),speed(5),alive(true)
    {
        myrect = image_.getRect();
        myrect.x = x_;
        myrect.y = y_;       
    }
    
    int get_x() const{ return myrect.x;}
    int get_y() const{ return myrect.y;}
    void move(bool moveLeft);
    void draw();
    void shoot();
    Rect get_rect(){return myrect;}
    bool get_alive(){return alive;}
    void set_alive_true(){alive = 1;}
    void set_alive_false(){alive = 0;}
    int get_w() const {return myrect.w;}
    int get_h() const {return myrect.h;}  
     
   
};
#endif
     
