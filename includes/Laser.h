// laser class
#ifndef LASER_H
#define LASER_H
#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include <vector>
#include "Ship.h"
#include <iostream>
class Laser
{
private:
    int x_, y_,h_,w_;
    Surface & surface_;
    int laser_dy;
    Color color;    
    int speed;
    bool alive;
    Rect myrect;
    
public:
Laser( int x,int y, Surface & surface)
    :laser_dy(4), x_(x), y_(y), surface_(surface),color(YELLOW),w_(2),h_(4),alive(true)
    { }
    
    void shoot();
    void draw();    
    int get_x();
    int  get_y();
    bool get_alive() {return alive;}
    void set_alive_true(){alive = 1;}
    void set_alive_false();
    void alien_shoot();
    Rect get_rect(){return myrect;}
};

#endif



void laser_shoot(std::vector< Laser > & ships_laser);
void laser_draw(std::vector< Laser > & ships_laser);
void create(std::vector< Laser > & ships_laser, Surface & surface, int x, int y);

