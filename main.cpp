/****************************************************************************
 Yihsiang Liow
 Copyright
 ****************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Ship.h"
#include "Fleet.h"
#include "Star.h"
#include "Laser.h"




/*****************************************************************************
For our programs involving graphics and sound, the template is this:

int main(int argc, char* argv[])
{
    ... PROGRAM ...

    return 0;
}

Our main() is made up of calling various functions. This is the first time you
are actually seeing the *code* of functions. Before this, you have been 
*using* functions, i.e. *calling* the functions.

For instance the first function call is

	test_event();

When you run this program, the program will execute a function call to 
test_event(). This means that the program will look for "text_event" and 
execute the code until it sees the statement "return". Executing return
will cause the program to go back to where it came from.

After running the program, comment out the call to test_event(), uncomment
the call to test_pixel() and run the program. Etc.
*****************************************************************************/


const int NUM_STARS = 1500;   
const int Num_brain = 10;
const int Num_Fire = 8;
const int Num_Ice = 6;
const int Num_flagship = 6;
const int Num_eye = 4;
/*void ShipShield(Ship & ship)
  {
  if(invincible 
  }*/
const int gspeed = 2;
const Color n = {225,0,0};

            
bool any_brain_alive(std::vector < Fleet > & Brain_fleet)
{
    for(int a = 0; a < Brain_fleet.size(); ++a)
    {
        if(Brain_fleet[a].get_alive())
        {
            return true;
        }
    }
    return false;
}
bool laser_fleet_collide(Laser laser,Fleet fleet)
{
    int r1x1 = laser.get_x();
    int r1x2 = laser.get_x() + 2;
    int r1y1 = laser.get_y();
    int r1y2 = laser.get_y() + 4;
    int r2x1 = fleet.get_rect_x();
    int r2x2 = fleet.get_rect_x() + fleet.get_w();
    int r2y1 = fleet.get_rect_y();
    int r2y2 = fleet.get_rect_y() + fleet.get_h();

    return ((r2x1 > r1x1 && r2x1 < r1x2 || r1x1 < r2x2 && r1x2 >r2x2) &&
            (r2y1 > r1y1 && r2y1 < r1y2 || r1y1 < r2y2 && r1y2 >r2y2))||
            ((r1x1 > r2x1 && r1x1 < r2x2 || r2x1 < r1x2 && r2x2 > r1x2) &&
            (r1y1 > r2y1 && r1y1 < r2y2 || r2y1 < r1y2 && r2y2 >r1y2));
 
}
bool laser_ship_collide(Laser laser, Ship ship)
{
    int r1x1 = laser.get_x();
    int r1x2 = laser.get_x() + 2;
    int r1y1 = laser.get_y();
    int r1y2 = laser.get_y() + 4;
    int r2x1 = ship.get_x();
    int r2x2 = ship.get_x() + ship.get_w();
    int r2y1 = ship.get_y();
    int r2y2 = ship.get_y() + ship.get_h();

    return ((r2x1 > r1x1 && r2x1 < r1x2 || r1x1 < r2x2 && r1x2 >r2x2) &&
            (r2y1 > r1y1 && r2y1 < r1y2 || r1y1 < r2y2 && r1y2 >r2y2))||
            ((r1x1 > r2x1 && r1x1 < r2x2 || r2x1 < r1x2 && r2x2 > r1x2) &&
            (r1y1 > r2y1 && r1y1 < r2y2 || r2y1 < r1y2 && r2y2 >r1y2));
 
}

bool fleet_ship_collide(Fleet fleet, Ship ship)
{
    int r1x1 = fleet.get_x();
    int r1x2 = fleet.get_x() + fleet.get_w();
    int r1y1 = fleet.get_y();
    int r1y2 = fleet.get_y() + fleet.get_h();
    int r2x1 = ship.get_x();
    int r2x2 = ship.get_x() + ship.get_w();
    int r2y1 = ship.get_y();
    int r2y2 = ship.get_y() + ship.get_h();

    return ((r2x1 > r1x1 && r2x1 < r1x2 || r1x1 < r2x2 && r1x2 >r2x2) &&
            (r2y1 > r1y1 && r2y1 < r1y2 || r1y1 < r2y2 && r1y2 >r2y2))||
            ((r1x1 > r2x1 && r1x1 < r2x2 || r2x1 < r1x2 && r2x2 > r1x2) &&
            (r1y1 > r2y1 && r1y1 < r2y2 || r2y1 < r1y2 && r2y2 >r1y2));
 
}

bool laser_ship_collide(Laser laser, Laser slaser)
{
    int r1x1 = laser.get_x();
    int r1x2 = laser.get_x() + 2;
    int r1y1 = laser.get_y();
    int r1y2 = laser.get_y() + 4;
    int r2x1 = laser.get_x();
    int r2x2 = laser.get_x() + 2;
    int r2y1 = laser.get_y();
    int r2y2 = laser.get_y() + 4;

    return ((r2x1 > r1x1 && r2x1 < r1x2 || r1x1 < r2x2 && r1x2 >r2x2) &&
            (r2y1 > r1y1 && r2y1 < r1y2 || r1y1 < r2y2 && r1y2 >r2y2))||
            ((r1x1 > r2x1 && r1x1 < r2x2 || r2x1 < r1x2 && r2x2 > r1x2) &&
            (r1y1 > r2y1 && r1y1 < r2y2 || r2y1 < r1y2 && r2y2 >r1y2));
 
}
 bool collided(Rect one, Rect two)
{
    int r1x1 = one.x;
    int r1x2 = one.x + one.w;
    int r1y1 = one.y;
    int r1y2 = one.y + one.h;
    int r2x1 = two.x;
    int r2x2 = two.x + two.w;
    int r2y1 = two.y;
    int r2y2 = two.y + two.h;

  

    return((r2x1 <= r1x1 && r2x2 >= r1x1) ||
           (r2x1 <= r1x2 && r2x2 >= r1x2) ||
           (r2x1 >= r1x1 && r2x1 <= r1x2) ||
           (r2x2 >= r1x1 && r2x2 <= r1x2) &&
        
           (r2y1 <= r1y1 && r2y2 >= r1y1) ||
           (r2y1 >= r1y1 && r2y1 <= r1y2) ||
           (r2y1 >= r1y2 && r2y1 <= r1y1) ||
           (r2y2 >= r1y1 && r2y2 <= r1y2));


}

int main(int argc, char* argv[])
{
   
/***************************************

                IMAGES/Fonts

*************************************/
    Color p = {225,0,0};
    Color t = {125,255,0};
    Color c = {255,255,0};
    Color w = {WHITE};
    Surface surface(W, H);
    Event event;
    Font font("fonts/emulogic.ttf", 15);
    Font Hiscoredef("fonts/emulogic.ttf",25);
    Font title("fonts/emulogic.ttf", 65);
    Image title_image(title.render("BRAIN-VASION", t));    
    Font up_font("fonts/emulogic.ttf",25);
    Image player1(up_font.render("PLAYER 1",p));   
    Image player2(up_font.render("PLAYER 2",p));
    Image up1(up_font.render("1UP",p));   
    Image game_up1(up_font.render("1UP",p));    
    Image up2(up_font.render("2UP",p));
    Font game("fonts/emulogic.ttf",25);
    Image game_image(game.render("PRESS SPACEBAR",p));
     Font endgame("fonts/Something Strange.ttf",30);
    Image endgame_image(endgame.render("PRESS ENTER",p));  
    Font copyright("fonts/emulogic.ttf",10);
    Image copy(copyright.render("Copyright John Epstein 2018",c));
    Font gameover("fonts/Something Strange.ttf",200);
    Image gameover_image(gameover.render("GAME",n));
    Font gameover2("fonts/Something Strange.ttf",200);
    Image gameover2_image(gameover2.render("OVER",n));
    Font score("fonts/emulogic.ttf",25);
    Image hi_score(score.render("HI-SCORE",p));
    Font levels("fonts/Something Strange.ttf",25);   
    Image level_image(levels.render("Wave",n));
    Font lwaves("fonts/Something Strange.ttf",25);
    Image image = "images/galaxian/SpaceShip3_50.png";    
    static Image fire = "images/galaxian/brain_fire.png";
    static Image brain = "images/galaxian/Brain.png";
    static Image ice ="images/galaxian/brain_freeze3.png";
    static Image eyeball = "images/galaxian/eyeball.png";
    Image lives ="images/galaxian/SpaceShip3_50_40.png";
    Image lives2 ="images/galaxian/SpaceShip3_50_40.png";
    Image lives3 ="images/galaxian/SpaceShip3_50_40.png";
/***************************************

          Rects

*************************************/

    Rect up2_rect = up2.getRect();
    up2_rect.x = 1150;
    up2_rect.y = 100;
    
    Rect title_rect = title_image.getRect();
    title_rect.x = H/2 - 120;
    title_rect.y = W/2 - 450;
    
    Rect player1_rect = player1.getRect();        
    player1_rect.x = 550;
    player1_rect.y = 350;
    
    Rect lives_rect = lives.getRect();
    lives_rect.x = 1150;
    lives_rect.y = 670;
    Rect up1_rect = up1.getRect();
    up1_rect.x = 100;
    up1_rect.y = 100;
    Rect game_up1_rect = up1.getRect();
    game_up1_rect.x = 100;
    game_up1_rect.y = 10;
    Rect player2_rect = player2.getRect();        
    player2_rect.x = 550;    
    player2_rect.y = 450;
    
    Rect game_rect = game_image.getRect();
    game_rect.x = 475;
    game_rect.y = 600;
    
    Rect endgame_rect = endgame_image.getRect();
    endgame_rect.x = 475;
    endgame_rect.y = 600;
    
    Rect lives2_rect = lives2.getRect();
    lives2_rect.x = 1180;
    lives2_rect.y = 670;
    
    Rect hi_rect = hi_score.getRect();
    hi_rect.x = 525;
    hi_rect.y = 100;
    
    Rect lives3_rect = lives3.getRect();
    lives3_rect.x = 1200;
    lives3_rect.y = 670;
    
    Rect copy_rect = copy.getRect();
    copy.rect.x = 20;
    copy_rect.y = 700;
    
    Rect levels_rect = level_image.getRect();
    levels_rect.x = 1150;
    levels_rect.y = 10;
    
    Rect gameover_rect = gameover_image.getRect();
    gameover_rect.x = W/2 - 225;
    gameover_rect.y = H/2 - 200;
     
    Rect gameover2_rect = gameover2_image.getRect();
    gameover2_rect.x = W/2-225;
    gameover2_rect.y = H/2;

    /**********************************

              music and sounds

    **********************************/
    Music during_game("sounds/Cyberpunk.ogg");
    Sound laser("sounds/laser.wav");
    Music startscreen("sounds/Mars.wav");
    Sound explosion("sounds/rumble.wav"); 
    Music endscreen("sounds/endscreen.wav");
    /*************************************

                  GamePlay Stuff

    ************************************/
    int num_lives = 3;// number of ships lives   
    
    std::vector< Fleet >Brain_ship;
    std::vector< Laser >ships_laser;
    std::vector< Laser > alien_laser;
    std::vector< Star > starField;
    // makes the starField
    for(int i = 0; i < 750; ++i)
    {
        Star stars(1,1,1,surface);
        Star stars2(2,2,2,surface);
        starField.push_back(stars);
        starField.push_back(stars2);
    }    
    
    Ship test (W / 2, H / 2 + 250, surface, image);
   
    int index= 0;  
    bool dive = false, reposition = false;
    int dive_index = 0;    
    int current_time = 0;
    int ship_delay = 300;
    int last_shot = 0;
    int alien_time = 0;
    int alien_delay = 400;
    int alien_ls = 0;  
  
   
    int state = 1; // controls the game state i.e startscreen gameplay etc 
    
    int player_score = 0;
    bool fleet_dead = false;
   
 
    
    int waves = 1;
    startscreen.play();
    while (1)
    {      
       
       
        if (event.poll() && event.type() == QUIT) break;
        switch(state)
        {
            
            case 0:
            {
                startscreen.play();
                state = 1;
            }
            break;
            case 1://title screen
            {
               
                std::ifstream high_scores;
                high_scores.open("high_scores.txt"); 
                char output[100];
                int index;
                
                if(high_scores.is_open())
                {                   
                    while(!high_scores.eof())
                    {
                        high_scores >> output;
                        ++index;
                    }
                    high_scores.close();
                } 
                     
                Image scores_image(score.render(output,w));
                Rect scores_rect = scores_image.getRect();
                scores_rect.x = 595;
                scores_rect.y = 150;                
                high_scores.close();
                Image default_image(score.render("2000",w));
                Rect default_rect = scores_image.getRect();
                default_rect.x = 595;
                default_rect.y = 150;                
                KeyPressed keypressed = get_keypressed();
                if(keypressed[SPACE])
                {                    
                    state = 2;
                    test.set_alive_true();
                    num_lives = 3;
                    player_score = 0;
                    waves = 1;
                    startscreen.stop();                    
                }                
                
                for(int i = 0; i < starField.size(); ++i)
                {
                    starField[i].MoveStar();
                }      
                surface.lock();
                surface.fill(BLACK);
                for(int i = 0; i < starField.size(); ++i)
                {
                    starField[i].draw();
            
                }
                
                surface.put_image(title_image, title_rect);
                surface.put_image(up1, up1_rect);
                surface.put_image(up2, up2_rect);
                surface.put_image(player1, player1_rect);
                surface.put_image(player2, player2_rect);
                surface.put_image(game_image,game_rect);            
                surface.put_image(hi_score, hi_rect);
                if(output < "2000")
                {
                    surface.put_image(default_image,default_rect); 
                }
                else 
                {
                    surface.put_image(scores_image,scores_rect);
                }
                surface.put_image(copy, copy_rect);
                surface.unlock();
                surface.flip();
                delay(15);
        }
        break;
        case 2://init
        {
            startscreen.stop();
            during_game.play();
            Brain_ship.clear();
         
            create_fleet(surface,Brain_ship,40,200,index,Num_brain + index,brain,20);
            create_fleet(surface,Brain_ship,40,225,index,Num_brain +index,brain,20);
            index += Num_brain;
            create_fleet(surface,Brain_ship,90,145,index,Num_Fire + index,fire,30);
            index += Num_Fire;
            create_fleet(surface,Brain_ship,90,170,index,Num_Fire + index,fire,30);
            index += Num_Fire;
            create_fleet(surface,Brain_ship,150,115,index,Num_Ice + index,ice,45);        
            create_fleet(surface,Brain_ship,190,80,index,Num_eye + index,eyeball,55);
            index += Num_eye;
               
                
       
                state = 3;
                
            }
            break;
            case 3: //game play
            {           
                
                
                for(int i = 0; i <starField.size(); ++i)
                {
                    starField[i].MoveStar();
                }
                
                move_fleet(Brain_ship);
                
                for(int a = 0; a < alien_laser.size(); ++a)
                {            
                    if(test.get_alive() && alien_laser[a].get_alive())
                    {
                        if(laser_ship_collide(alien_laser[a], test))
                        {                       
                            //test.set_alive_false();
                            alien_laser[a].set_alive_false();
                            --num_lives;
                        }
                    }
            
                }

                //enemy and friendly laser collide
                for(int a = 0; a < Brain_ship.size(); ++a)
                {
                    for(int s = 0; s < ships_laser.size(); ++ s)
                    {
                        
                        if(Brain_ship[a].get_alive() && ships_laser[s].get_alive())
                        {
                            if(laser_fleet_collide(ships_laser[s],Brain_ship[a]))
                            {                              
                                Brain_ship[a].set_alive_false();
                                ships_laser[s].set_alive_false();                         
                                player_score += Brain_ship[a].get_points();
                                explosion.play();
                                
                            }
                        }
                    }
                }
                 std::string score_string = std::to_string(player_score);
                 char const * pchar = score_string.c_str();
                 Image pscore(score.render(pchar,w));
                 Rect pscore_rect = pscore.getRect();
                 pscore_rect.x = 100;
                 pscore_rect.y = 40;
                              
                for(int a = 0; a < alien_laser.size(); ++a)
                {
                    for(int s = 0; s < ships_laser.size(); ++ s)
                    {
                        if(alien_laser[a].get_alive() && ships_laser[s].get_alive())
                        {
                            if(laser_fleet_collide(ships_laser[s],Brain_ship[a]))
                            {                       
                                ships_laser[s].set_alive_false();
                                alien_laser[a].set_alive_false();
                            }
                        }
                    }
                }

                for(int a = 0; a < Brain_ship.size(); ++a)
                {            
                    if(test.get_alive() && Brain_ship[a].get_alive())
                    {
                        if(fleet_ship_collide(Brain_ship[a], test))
                        {                       
                            //test.set_alive_false();
                            Brain_ship[a].set_alive_false();                           
                            --num_lives;
                            
                        }
                        
                    }
                }
               
                if (!dive && !reposition)
                {
                    while(1)
                    {
                        dive_index = rand() % Brain_ship.size();
                        if(Brain_ship[dive_index].get_alive() == true)
                        {
                            dive = true; 
                            break;
                        }
                    }
           
                }

                // makes alien dive toward players ship:
                if (dive)
                {
            
                    alien_time = getTicks();
                    if(alien_time - alien_ls > alien_delay)
                    {
                        alien_ls = alien_time;
                        alien_laser.push_back(Laser(Brain_ship[dive_index].get_rect_x()+ 10,
                                                    Brain_ship[dive_index].get_rect_y()+Brain_ship[dive_index].get_w(),
                                                    surface));
                        if(Brain_ship[dive_index].get_alive() == false)
                        {
                            alien_laser.clear();
                        }
                    }
                    Brain_ship[dive_index].dive(test.get_x());
                    Brain_ship[dive_index].set_dive(true);            
                    if (Brain_ship[dive_index].get_rect_y() >= H)
                    {
                        dive = false; // stop that alien from diving & make new one dive
                        reposition = true;
                        Brain_ship[dive_index].reset_rect_y();
                        Brain_ship[dive_index].set_dive(false);
                    }
                }

                // Make alien go back to its position in the moving fleet. 
                if (reposition)
                {
                    Brain_ship[dive_index].reposition();
                    if (Brain_ship[dive_index].get_x() == Brain_ship[dive_index].get_rect_x() &&
                        Brain_ship[dive_index].get_y() == Brain_ship[dive_index].get_rect_y())
                    {
                        reposition = false;
                    }
                }                
                KeyPressed keypressed = get_keypressed();
                if (keypressed[LEFTARROW])
                {
                    test.move(true);
                }
                if(keypressed[RIGHTARROW])
                {
                    test.move(false);
                }
         
                if (keypressed[SPACE])
             
                {
                    current_time = getTicks();
                    if(current_time -last_shot > ship_delay && test.get_alive())
                    {
                        last_shot = current_time;
                        create(ships_laser,surface,test.get_x()+20,test.get_y());        
                        laser.play();               
                    }
                     
                }        
                laser_shoot(ships_laser);
                for(int i = 0; i < alien_laser.size(); ++i)
                {
                    alien_laser[i].alien_shoot();
                }
                 
                if(any_brain_alive(Brain_ship) == false)
                {
                    waves += 1;
                    for(int i = 0; i < Brain_ship.size(); ++i)
                    {
                        Brain_ship[i].set_fwave();
                        
                    }
                }
               
                //puts the waves into a string that can be displayed on the screen
                std::string wave_string = std::to_string(waves);
                char const * wchar = wave_string.c_str();
                Image pwaves(lwaves.render(wchar,w));
                Rect pwaves_rect = pwaves.getRect();
                pwaves_rect.x = 1250;
                pwaves_rect.y = 10;
                
                if(any_brain_alive(Brain_ship) == false)
                {
                  
                    state = 2;
                }
                       
                if(num_lives == 0)
                {
                    test.set_alive_false();
                   
                }
                if(num_lives == 0)
                {
                    std::ofstream high_scores("high_scores.txt", std::ofstream::out |
                                              std::ofstream::app);
                    high_scores << pchar << std::endl;                   
                    high_scores.close();                  
                }
               
                if(num_lives == 0)
                {
                 
                    state = 4;
                }
               
                // draw game objects
                surface.lock();
                surface.fill(BLACK);       
      
                for(int i = 0; i < starField.size(); ++i)
                {
                    starField[i].draw();
            
                }               
                surface.put_image(game_up1, game_up1_rect);
                if(num_lives == 3)
                {
                surface.put_image(lives,lives_rect);
                surface.put_image(lives2,lives2_rect);
                surface.put_image(lives3,lives3_rect);
                }
                else if(num_lives == 2)
                {
                  
                surface.put_image(lives2,lives2_rect);
                surface.put_image(lives3,lives3_rect);
                }
                else
                {
                    surface.put_image(lives3,lives3_rect);
                }
                   
                draw_my_fleet(Brain_ship);
                surface.put_image(pscore,pscore_rect);
                surface.put_image(level_image,levels_rect);
                surface.put_image(pwaves,pwaves_rect);
                if(test.get_alive())
                {
                    test.draw();
                }
                
                for(int m = 0; m < ships_laser.size(); ++m)
                {
                    
                    if(ships_laser[m].get_alive())
                    {
                        ships_laser[m].draw();
                    }
                }        
            
            
                for(int i = 0; i < alien_laser.size(); ++i)
                {
                    if(alien_laser[i].get_alive())
                    {
                        alien_laser[i].draw();
                    }
                }       
                surface.unlock();
                surface.flip();
                delay(15);                
            }
                break;
            case 4:// to be able to play endscreen music
                {
                    during_game.stop();
                    endscreen.play();
                    state = 5;
                }
                break;
            case 5://end screen
            {
                
                 KeyPressed keypressed = get_keypressed();
                
                          
                if(keypressed[SDLK_RETURN])
                {
                    
                    state = 6;                  
                    
                }                
                
                for(int i = 0; i < starField.size(); ++i)
                {
                    starField[i].MoveStar();
                }
               
                surface.lock();
                surface.fill(BLACK);
                for(int i = 0; i < starField.size(); ++i)
                {
                    starField[i].draw();
            
                }        
                surface.put_image(gameover_image, gameover_rect);
                surface.put_image(gameover2_image, gameover2_rect);
                surface.put_image(endgame_image, endgame_rect);   
                surface.unlock();
                surface.flip();
                delay(20);
                
            }
            break;
            case 6:
            {
                endscreen.stop();
                state = 0;
            }
        }
    }
   
    
    return 0;
}
