#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "Constants.h"
#include "Includes.h"
#include "Color.h"
#include "Rect.h"
#include "Surface.h"
#include "Event.h"
#include "Star.h"

void Star::MoveStar()
{
    y += star_dy;
    //std::cout<< s.y <<'\n';
    if(y >= H -1)
    {
        y = 0;
        x = rand() % W;
    }
    
    
}

void Star::draw()
{
   
    surface_.put_rect(x,y,w_,h_,
                     color.r,color.g,color.b);
   
}
