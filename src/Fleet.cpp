#include "Fleet.h"
#include "Surface.h"
#include "Event.h"
#include "Includes.h"
#include "Image.h"


int Fleet::speed = 2;


/**************Creates a vector of alien ships*********************/
void create_fleet(Surface & surface, std::vector< Fleet > & Brain_ship,
                  int x, int y, int start,int num_aliens, Image & image, int points)
{
    for(int i = start; i < num_aliens; ++i)
    {
        Fleet alien (x, y, surface,image,points);                                              
        Brain_ship.push_back(alien);
        x += 50;
    }
}

void move_fleet(std::vector< Fleet > & Brain_ship)
{
    bool move_pos = true;
    
    // if fleet is moving towards right bound:
    if (Brain_ship[0].speed > 0)
    {
        // find right-most alive alien.
        int right_most = get_right_limit(Brain_ship);

        // Determine if right-most hits the right bound- switch all alien
        // acceleration to neg.
        if (Brain_ship[right_most].get_x() + Brain_ship[right_most].get_w() >= W)
        {
            move_pos = false;
            Brain_ship[right_most].switch_speed(move_pos);
        }
        // If right-most has not yet hit the right bound, continue moving l to r.
        else { move_fleet_ltr(Brain_ship); }  
    }
    // else if fleet is moving towards left bound:
    else  
    {
        // Find left-most alive alien.
        int left_most = get_left_limit(Brain_ship);

        // Determine if left-most has hit the left bound- switch all alien
        // acceleration to pos.
        if (Brain_ship[left_most].get_x() <= 0)
        {
            move_pos = true;
            Brain_ship[left_most].switch_speed(move_pos);
        }
        // If left-most has not yet hit the left bound, continue moving r to l.
        else { move_fleet_rtl(Brain_ship); }
    }    
}

int get_right_limit(std::vector< Fleet > & Brain_ship)
{
    int max_x = Brain_ship[0].get_x();
    int right_most = 0;
    
    for(int i = 0; i < Brain_ship.size(); ++i)
    {
        if (Brain_ship[i].get_alive() && Brain_ship[i].get_x() > max_x)
        {
            right_most = i;
            max_x = Brain_ship[i].get_x();
        }
    }
    return right_most;
}

/********** Function to find the alien located at the smallest x-coordinate
            position that is still alive in the fleet ************************/
int get_left_limit(std::vector< Fleet > & Brain_ship)
{
    int min_x = Brain_ship[0].get_x();
    int left_most = 0;
    
    for(int i = 0; i < Brain_ship.size(); ++i)
    {
        if (Brain_ship[i].get_alive() && Brain_ship[i].get_x() < min_x)
        {
            left_most = i;
            min_x = Brain_ship[i].get_x();
        }
    }
    return left_most;
}

void move_fleet_rtl(std::vector< Fleet > & Brain_ship)
{
    for(int i = Brain_ship.size() - 1; i > -1; --i)
    {
        Brain_ship[i].set_x(Brain_ship[i].get_speed());
    }
}

/**** Function to move Alien objects from left to right across the screen ****/
void move_fleet_ltr(std::vector< Fleet > & Brain_ship)
{
    for(int i = 0; i < Brain_ship.size(); ++i)
    {
        Brain_ship[i].set_x(Brain_ship[i].get_speed());
    }
}

void draw_my_fleet (std::vector< Fleet > & Brain_ship)
{
    for (int i = 0; i < Brain_ship.size(); ++i)
    {
        if(Brain_ship[i].get_alive())
        {
            Brain_ship[i].draw();
        }
    }
}

