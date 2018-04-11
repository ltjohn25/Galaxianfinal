#ifndef FLEET_H
#define FLEET_H

#include "Image.h"
#include "Includes.h"
#include "Rect.h"
#include "Surface.h"
#include "Event.h"
#include "Constants.h"

class Fleet
{
private:    
    int x_, y_,dx,dy;
    Rect rect;
    Image & image;
    Surface & surface;
    bool moveLeft;
    static int speed;
    
    
public:
Fleet(int x, int y, Surface & surface, Image & alien)
    : x_(x), y_(y), surface(surface),moveLeft(true),image(alien),dx(dx),dy(0)        
    {            
        rect = image.getRect();
        rect.x = x_;
        rect.y = y_;       
    }

    Surface & getSurface()
    {
        return surface;
    }
    
void fleet_move(bool moveLeft);
void fleet_draw();

};
#endif
