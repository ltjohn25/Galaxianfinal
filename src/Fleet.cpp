#include "Fleet.h"
#include "Surface.h"
#include "Event.h"
#include "Includes.h"
#include "Image.h"



void Fleet::fleet_move(bool moveleft)
{
   
    if(moveLeft)
    {
        rect.x -= speed;
    }
    else
    {
        rect.x += speed;
    } 
 
   
    if (rect.x + rect.w >= W)
    {
        // CASE: right side of image touches the right side of surface
        rect.x = -speed;
        moveleft = false;
    }
    else if (rect.x <= 0)
    {
        // CASE: right side of image touches the right side of surface
        rect.x = speed;
        moveleft = true;
    }      
    
}
void Fleet::fleet_draw()
{
    surface.put_image(image,rect);     // blit image at rect on surface   
}
