#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "src/rsdl.hpp"
#include "Config.h"
#include "Obstacle.h"
#include "Mario.h"
#include "Functions.h"

using namespace std;

void check_gameover(Mario *mario,Window &win)
{
  int lives=mario->return_mario_lives();
  cout<<lives;
  if(lives==0)
  {
    win.clear();
    win.show_text("Game Over!", Point(170, 150), WHITE, FONT,FONT_SIZE_GAMEOVER);
    win.update_screen();
  }
}

void get_click(Window &win,char& click)
{
 while(win.has_pending_event())
  {
    Event event = win.poll_for_event();
    if (event.get_type()==Event::KEY_PRESS)
    click = event.get_pressed_key();
  }
}

void print_standing_mario(vector<string> v_map,Window &win,int& show_from,Obstacle* obstacle,Mario* mario)
{
 print_background(win,show_from);
 obstacle->print_all(v_map,win,show_from);
 if(mario->show_direction()==RIGHT)
   mario->show_mario(v_map,win,show_from,STANDING_RIGHT,obstacle);
 else
   mario->show_mario(v_map,win,show_from,STANDING_LEFT,obstacle);  
 mario->show_mario_coins(win);
 win.update_screen();
}

int main(int argc, char* argv[])
{
  int show_from=0,type_right=1,type_left= 1;
  string direction=RIGHT;
  vector<string> v_map=read_map(v_map, argv[1]);;
  Window win(MAP_ROW,MAP_COLUMN, WINDOW_NAME);
  Mario *mario=new Mario(v_map,win);
  Obstacle *obstacle=new Obstacle(v_map,win,show_from);
  bool quit=false;
  win.play_music(THEME_MUSIC);

  while(1){
   char click = 0;
   get_click(win,click);
   if (click == 'q')
     return 0;
   if(click == 'd')
   {
    mario->set_speed_x(20);
    obstacle->print_all(v_map,win,show_from);
    vector<Rectangle> goomba=mario->return_little_goomba();
    mario->move_right(v_map,win,show_from,obstacle,type_right);
    mario->set_direction(RIGHT);
    mario->check_falling_down(v_map,win,show_from,obstacle)  ;
   }
   if(click == 'a')
   {
    mario->set_speed_x(20);
    obstacle->print_all(v_map,win,show_from);
    mario->move_left(v_map,win,show_from,obstacle,type_left);
    mario->set_direction(LEFT);
    mario->check_falling_down(v_map,win,show_from,obstacle)  ;
   }
   if(click == 'w')
   {
    mario->jump(v_map,win,show_from,obstacle);  
    mario->check_falling_down(v_map,win,show_from,obstacle)  ;
   }
   if(click==0)
    mario->set_speed_x(0);
    
   print_standing_mario(v_map,win,show_from,obstacle,mario);
   check_gameover(mario,win);
  }
}
