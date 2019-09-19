#ifndef FLEET_H
#define FLEET_H

#include "Image.h"
#include "Includes.h"
#include "Rect.h"
#include "Surface.h"
#include "Event.h"
#include "Constants.h"
#include <vector>

class Fleet 
{
private:    
    int x_, y_, dx, dy, ds;
    Rect rect;
    Image & image;
    Surface & surface;
    bool alive;
    bool fdive;
    int points_;
    int fwave_;
   
    
    
public:
Fleet(int x, int y, Surface & surface, Image & image,int points)
    : x_(x), y_(y), surface(surface),image(image),alive(true),dx(1),dy(2),ds(6),fdive(false),points_(points),
        fwave_(1) 
        {
        
            rect = image.getRect();                                                                                 
            rect.x = x_;
            rect.y = y_;
            if(fwave_ > 1)
            {
                ds += 2;
            }
        }
    static int speed;
    Surface & getSurface()
    {
        return surface;
    }
    
    Fleet switch_speed(const bool move_pos)
    {
        if(fwave_ > 1) {speed += 2;}
        if (move_pos && speed < 0){speed = -speed;}
        if (!move_pos && speed > 0){speed = -speed;}
        

    }
    Fleet dive(int shipsX)
    {
        
        rect.y += ds;
        if(rect.x < shipsX - 85)
        {
            rect.x += ds;
        }
        else if(rect.x > shipsX + 85)
        {
            rect.x -= ds;
        }
           
    }

    Fleet reposition()
    {
        //helps with "wiggling when returning to formation
        if (rect.x == x_ + 1) {rect.x = x_;}
        else if (rect.x == x_){}
        else if (rect.x > x_) {--rect.x;}
        else if (rect.x < x_) {++rect.x;}

        if (rect.y == y_){}
        else if (rect.y > y_) {--rect.y;}
        else if (rect.y < y_) {++rect.y;}
    }    
    Fleet draw()
    {
        surface.put_image(image, rect);
    }
    int get_points(){return points_;}
    void set_alive_true(){alive = 1;}
    void set_alive_false(){alive = 0;}
    void set_fwave(){fwave_ += 1;}
    int get_fwave(){return fwave_;}
    bool get_alive() const {return alive;}
    int get_speed() const {return speed;}
    int get_rect_x()const {return rect.x;}
    int get_rect_y() const {return rect.y;}
    int get_w() const {return rect.w;}
    int get_x() const {return x_;}
    int get_y() const {return y_;}
    int get_h() const {return rect.h;}   
    void set_dive(bool setdive){ fdive = setdive;}
    Rect get_rect(){return rect;}
    Fleet & set_x(int x1)
    {
        x_+= x1;
        if(!fdive)
        {
            rect.x = x_;
        }
      
        
    }
    Fleet & reset_rect_y(){rect.y = 0;}
  
};

void create_fleet(Surface & surface, std::vector< Fleet > & Brain_ship,
                  int x,int y,int start, int num_aliens, Image & image,int points);
void move_fleet(std::vector < Fleet > & Brain_ship);
void move_fleet_ltr(std::vector < Fleet > & Brain_ship);
void move_fleet_rtl(std::vector < Fleet > & Brain_ship);
int get_right_limit(std::vector < Fleet > & Brain_ship);
int get_left_limit(std::vector < Fleet > & Brain_ship);
void draw_my_fleet(std::vector < Fleet > & Brain_ship);

#endif

