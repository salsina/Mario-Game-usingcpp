#include "Mario.h"


Mario::Mario(vector<string> v_map,Window &win)
{
 for (int i=0;i<v_map.size();i++)
   for (int j=0;j<v_map[i].size();j++)
     if (v_map[i][j] == 'M')
     {
      mario_position=(Rectangle(j*SCALE, MAP_COLUMN-SCALE*(v_map.size()-i),SCALE,SCALE));   
      change_map(v_map,i,j,'.');
     }  
  find_enemy(v_map,'l',little_goomba);
  find_enemy(v_map,'k',koopa_troopa);
}

Rectangle Mario::show_mario_position()
{
  return mario_position;
}

void Mario::set_direction(string direct)
{
direction=direct;
}

string Mario::show_direction()
{
return direction;
}

void Mario::fall_down(vector<string> v_map,Window &win,int &show_from,Obstacle* obs)
{
  int t=0;
  while(t<3)
 {
  set_speed_y(10);
  set_window(v_map,win,show_from,obs);
  mario_position.y+=show_speed_y();
  win.draw_img(DEAD,Rectangle(mario_position.x-show_from,mario_position.y,SCALE,SCALE));
  win.update_screen();
  delay(20);
  t++;
 }
}

void Mario::check_falling_down(vector<string> v_map,Window &win,int &show_from,Obstacle* obs)
{
  if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)]=='.' && v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)-1]=='#')
    print_dead_mario(v_map,win,show_from,obs);
}

vector<Rectangle> Mario::return_little_goomba()
{
  return little_goomba;
}

int Mario::return_mario_lives()
{
return mario_lives;
}

int Mario::show_speed_x()
{
  return mario_vx;
}

void Mario::set_speed_x(int speed)
{
  mario_vx=speed;
}

int Mario::show_speed_y()
{
  return mario_vy;
}

void Mario::set_speed_y(int speed)
{
  mario_vy=speed;
}

void Mario::check_under(vector<string> v_map,Window &win,int &show_from,Obstacle* obs)
{
  if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)]=='.')
  {  
    for(int i=0;i>-10;i--)
    {
      set_speed_y(i);
      set_window(v_map,win,show_from,obs);
      mario_position.y-=show_speed_y();
      if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)]!='.' ){
       break;
       }
      if(direction==RIGHT) 
       win.draw_img(JUMPING_RIGHT,Rectangle(mario_position.x-show_from,mario_position.y+30,SCALE,SCALE));
      else
        win.draw_img(JUMPING_LEFT,Rectangle(mario_position.x-show_from,mario_position.y+30,SCALE,SCALE));
      win.update_screen();
      delay(5);
    }
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)]=='.' ){
    mario_position.y+=27;
    }
  }
}

void Mario::print_dead_mario(vector<string> v_map,Window &win,int &show_from,Obstacle* obs)
{
  win.play_sound_effect(DEATH_SOUND);
  win.clear();
  print_background(win,show_from);
  obs->print_all(v_map,win,show_from);
  win.draw_img(DEAD,Rectangle(mario_position.x-show_from,mario_position.y,SCALE,SCALE));
  win.update_screen();
  delay(3000);
  fall_down(v_map,win,show_from,obs);
  mario_lives--;
}

void Mario::check_front(vector<string> v_map,Window &win,int &show_from,Obstacle* obs)
{
  if(direction==RIGHT)
  { 
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)+1]!='.')
      set_speed_x(0);
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)+1]=='l'
    ||v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)+1]=='k')
      print_dead_mario(v_map,win,show_from,obs) ; 
  }
  else
  {
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)-1]!='.')
    set_speed_x(0);
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)-1]=='l'
    ||v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)-1]=='k')
      print_dead_mario(v_map,win,show_from,obs) ; 
  }
}

void Mario::print_jump_image(Window &win,int &show_from)
{
  if(direction==RIGHT)
    win.draw_img(JUMPING_RIGHT,Rectangle(mario_position.x-show_from,mario_position.y,SCALE,SCALE));
  else
    win.draw_img(JUMPING_LEFT,Rectangle(mario_position.x-show_from,mario_position.y,SCALE,SCALE)); 
}

void Mario::check_question_coin(vector<string> &v_map,Window &win,int& show_from,Obstacle* obs)
{
  if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())-1][((show_mario_position().x)/SCALE)]=='?')
    {
      for(int i=30;i<60;i+=3)
      {
        set_window(v_map,win,show_from,obs);
        print_jump_image(win,show_from);
        win.draw_img(COIN,Rectangle(mario_position.x-show_from,mario_position.y-i,SCALE,SCALE));
        win.update_screen();
        delay(1);
      }
      mario_coins++;
      change_map(v_map,((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())-1,((show_mario_position().x)/SCALE),'/');
      win.play_sound_effect(COIN_SOUND);
    }
}

void Mario::check_question_health(vector<string> &v_map,Window &win,int& show_from,Obstacle* obs)
{
  if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())-1][((show_mario_position().x)/SCALE)]=='h')
  {
    for(int i=30;i<60;i+=3)
     {
      set_window(v_map,win,show_from,obs);
      print_jump_image(win,show_from);
      win.draw_img(MUSHROOM_HEALTH,Rectangle(mario_position.x-show_from,mario_position.y-i,SCALE,SCALE));
      win.update_screen();
      delay(1);
     }
      mario_lives++;
      change_map(v_map,((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())-1,((show_mario_position().x)/SCALE),'/');
  }
}

void Mario::show_mario_coins(Window &win)
{
  win.show_text("coins ", Point(350, 50), WHITE, FONT, FONT_SIZE);
  win.show_text(to_string(mario_coins), Point(375, 100), WHITE, FONT, FONT_SIZE);
  win.show_text("lives ", Point(450, 50), WHITE, FONT, 30);
  win.show_text(to_string(mario_lives), Point(475, 100), WHITE, FONT, FONT_SIZE);
}

void Mario::show_mario(vector<string> v_map,Window &win,int &show_from,string address,Obstacle* obs)
{
  win.draw_img(address,Rectangle(mario_position.x-show_from,mario_position.y,SCALE,SCALE));
  print_enemy(v_map,little_goomba,win,show_from,LITTLE_GOOMBA_2,obs);
  print_enemy(v_map,koopa_troopa,win,show_from,KOOPA_TROOPA_1,obs);
  
  if (mario_position.x - show_from > 500)
   show_from = mario_position.x - 500;
  check_under(v_map,win,show_from,obs);
}

void Mario::find_enemy(vector<string> v_map,char ch,vector<Rectangle> &v_enemy)
{
  for (int i=0;i<v_map.size();i++)
    for (int j=0;j<v_map[i].size();j++)
      if (v_map[i][j] == ch)
      {
        v_enemy.push_back(Rectangle(j*SCALE, MAP_COLUMN-SCALE*(v_map.size()-i),SCALE,SCALE));
        change_map(v_map,i,j,'.');
      }
}

void Mario::move_enemy(vector<Rectangle> &v_enemy,vector<string> &v_map,int i,Window &win,string address1,int &show_from,Obstacle* obs)
{
  while(v_map[(v_enemy[i].y-MAP_COLUMN)/SCALE+v_map.size()][v_enemy[i].x/SCALE]=='.')
    {
    win.clear();
    print_background(win,show_from);
    win.draw_img(address1,Rectangle(v_enemy[i].x-show_from,v_enemy[i].y,SCALE,SCALE));
    obs->print_all(v_map,win,show_from);
    v_enemy[i].x--;
    change_map(v_map,(v_enemy[i].y-MAP_COLUMN)/SCALE+v_map.size(),v_enemy[i].x/SCALE,'l');
    win.update_screen();
    delay(1); 
    }
}

void Mario::print_enemy(vector<string> &v_map,vector<Rectangle> &v_enemy,Window &win,int &show_from,string address1,Obstacle* obs)
{
  for(int i=0;i<v_enemy.size();i++)
    win.draw_img(address1,Rectangle(v_enemy[i].x-show_from,v_enemy[i].y,SCALE,SCALE));
}

void Mario::print_walk_image(vector<string> v_map,Window &win,int &show_from,Obstacle* obs,string address)
{
  set_window(v_map,win,show_from,obs);
  win.draw_img(address,Rectangle(mario_position.x-show_from ,mario_position.y,SCALE,SCALE));
  print_enemy(v_map,little_goomba,win,show_from,LITTLE_GOOMBA_2,obs);
  print_enemy(v_map,koopa_troopa,win,show_from,KOOPA_TROOPA_1,obs);

  win.update_screen();
  delay(50);
}

void Mario::move_right(vector<string> v_map,Window &win,int &show_from,Obstacle* obs, int &type_right)
{
  check_front(v_map,win,show_from,obs);
  mario_position.x+=show_speed_x();
  print_walk_image(v_map,win,show_from,obs,"assets/sprites/mario/normal/walking-right-" + to_string(type_right) + ".png");
  type_right++;
  if(type_right > 3)
    type_right = 1;
}

void Mario::move_left(vector<string> v_map,Window &win,int &show_from,Obstacle* obs,int &type_left)
{
  check_front(v_map,win,show_from,obs);
  mario_position.x-=show_speed_x();
  print_walk_image(v_map,win,show_from,obs,"assets/sprites/mario/normal/walking-left-" + to_string(type_left)+ ".png");
  type_left++;
  if(type_left>3)
    type_left=1;
}

void Mario::check_jump_direction(int &show_from)
{
 if(show_speed_x()!=0)
  {
   if(direction=="RIGHT")
    mario_position.x+=5;
   else
    mario_position.x-=5;
  }
    if (mario_position.x - show_from > 500)
   show_from = mario_position.x - 500;
}

void Mario::jump_down(vector<string> v_map,Window &win,int &show_from,Obstacle* obs)
{
  for(int speed=0;speed>-30;speed--)
  {
  set_speed_y(speed);
  check_front(v_map,win,show_from,obs);
  set_window(v_map,win,show_from,obs);
  mario_position.y-=show_speed_y();
  check_jump_direction(show_from);
  if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)]!='.'
  || v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)+1]!='.'){
    mario_position.y-=mario_position.y%30-30;
    break;
  }
  print_jump_image(win,show_from);
  win.update_screen();
  delay(5);
  }
}

void Mario::set_window(vector<string> &v_map,Window &win,int &show_from,Obstacle* obs)
{
  win.clear();
  print_background(win,show_from);
  obs->print_all(v_map,win,show_from);
  print_enemy(v_map,little_goomba,win,show_from,LITTLE_GOOMBA_2,obs);
  print_enemy(v_map,koopa_troopa,win,show_from,KOOPA_TROOPA_1,obs);
  show_mario_coins(win);
}

void Mario::check_click(vector<string> &v_map,Window &win,int &show_from,char click,Obstacle* obs)
{
int type_right=1,type_left= 1;
 if(click == 'd')
 {
   set_speed_x(20);
   obs->print_all(v_map,win,show_from);
   move_right(v_map,win,show_from,obs,type_right);
   set_direction(RIGHT);
   check_falling_down(v_map,win,show_from,obs)  ;
   }

 if(click == 'a')
  {
    set_speed_x(20);
    obs->print_all(v_map,win,show_from);
    move_left(v_map,win,show_from,obs,type_left);
    set_direction(LEFT);
    check_falling_down(v_map,win,show_from,obs)  ;
   }
}

void Mario::jump_up(vector<string> &v_map,Window &win,int &show_from,Obstacle* obs)
{
  for(int speed =17;speed>-1;speed--)
  {
   char click3 = 'b';
   while(win.has_pending_event())
   {           
    Event event = win.poll_for_event();
    if (event.get_type()==Event::KEY_PRESS){
     click3 = event.get_pressed_key();
   }
  }
  check_click(v_map,win,show_from,click3,obs);
  set_window(v_map,win,show_from,obs);
  set_speed_y(speed);
  check_front(v_map,win,show_from,obs);
  mario_position.y-=show_speed_y();
  check_jump_direction(show_from);
  if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())-1][((show_mario_position().x)/SCALE)]!='.'
  || v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())-1][((show_mario_position().x)/SCALE)+1]!='.')
  {  
    check_question_coin(v_map,win,show_from,obs);
    check_question_health(v_map,win,show_from,obs);
    for(int i=0;i>-30;i--)
    {
    char click2 = 'b';
    int type_right=1,type_left= 1;
    while(win.has_pending_event())
    {           
     Event event = win.poll_for_event();
     if (event.get_type()==Event::KEY_PRESS){
     click2 = event.get_pressed_key();
     }
    }
    check_click(v_map,win,show_from,click2,obs);
    set_speed_y(i);
    set_window(v_map,win,show_from,obs);
    mario_position.y-=show_speed_y();
    check_jump_direction(show_from);
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)]!='.' 
    ||v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())+1][((show_mario_position().x)/SCALE)+1]!='.'){
    mario_position.y-=mario_position.y%30;
    break;
    }
    print_jump_image(win,show_from);
    win.update_screen();
    delay(5);
    }
    if(v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)]!='.' 
    ||v_map[((show_mario_position().y- MAP_COLUMN)/SCALE+v_map.size())][((show_mario_position().x)/SCALE)+1]!='.'){
      mario_position.y-=30;
      }
    break;
  }
  print_jump_image(win,show_from);
  win.update_screen();
  delay(5);
  }
}

void Mario::jump(vector<string> &v_map,Window &win,int &show_from,Obstacle* obs)
{
  win.play_sound_effect(JUMP_SUPER_SOUND);
  jump_up(v_map,win,show_from,obs);
  jump_down(v_map,win,show_from,obs);
}
