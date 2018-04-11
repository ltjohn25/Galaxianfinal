#include "Ship.h"
#include "Surface.h"
#include "Event.h"
#include "Includes.h"
#include "Image.h"
#include <iostream>
void Ship::move(bool moveLeft)
{
    
    if(moveLeft)
    {
        myrect.x -= speed;
    }
    else
    {
        myrect.x += speed;
    }
   
    if (myrect.x + myrect.w >= W)
    {
        // CASE: right side of image touches the right side of surface
       
        myrect.x = W - myrect.w;
            
       
    }    
    else if (myrect.x <= 0)
    {
    // CASE: left side of image touches the left side of surface
       
        myrect.x = 0;
      
    }

   
}
   
void Ship::draw()
{
    surface_.put_image(image_, myrect); // blit image at rect on surface   
}
