#ifndef STAR_H
#define STAR_H

#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Includes.h"
#include "Rect.h"
#include "Constants.h"
#include "Color.h"
#include "Surface.h"
#include "Event.h"

class Star 
{
private:   
    int x;
    int y;
    int h_;
    int w_;
    Color color;    
    int star_dy;
    Surface & surface_;
    

public:
Star(int speed,int w,int h, Surface & surface)
    :surface_(surface),w_(w),h_(h), star_dy(speed)
        
    {
        
        color.r = rand() % 255;
        color.g = rand() % 255;
        color.b = rand() % 255;      
        x = rand() % W;
        y = rand() % H;        
    }
    
    
    void MoveStar();
    void draw();
};

#endif
