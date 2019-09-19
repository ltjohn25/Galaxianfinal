#include"Laser.h"
#include"Rect.h"
#include <vector>
#include <iostream>
#include "Includes.h"

// laser cpp
void Laser::shoot()
{
    if(alive)
    {
        y_ -= laser_dy;
    }
    if(y_ < -1)
    {
        alive = false;
    }
  
}

int Laser::get_x()
{
    return x_;
}
int Laser::get_y()
{
    return y_;
}
void Laser::draw()
{  
    surface_.put_rect(x_,y_,w_,h_, color.r,color.g,color.b); 
}


void create(std::vector< Laser > & ships_laser, Surface & surface, int x, int y)
{
      
        Laser bob(x,y,surface);
        ships_laser.push_back(bob);
             

}


void laser_shoot(std::vector< Laser > & ships_laser)
{
    for(int m =0; m < ships_laser.size(); ++m)
    {
        ships_laser[m].shoot();        
    }
}


void Laser::alien_shoot()
{
     if(alive)
    {
        y_ += laser_dy +7;
    }
    if(y_ > H)
    {
        alive = false;
    }
}

void Laser::set_alive_false()
{
    alive = 0;
   
}
