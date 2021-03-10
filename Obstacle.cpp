#include "Obstacle.h"



void Obstacle::print_question(vector<string> v_map,Window &win,int show_from)
 {  
   frame++;
   if(frame > 3) frame = 1;
   string address = "assets/sprites/objects/bricks_blocks/question-";
   address += to_string(frame);
   address += ".png";
  for(int i=0;i<question_coin.size();i++)
  {
    win.draw_img(address,Rectangle(question_coin[i].x-show_from,question_coin[i].y,SCALE,SCALE));    
    delay(1);
  }
  for(int j=0;j<question_flower.size();j++)
   {
    win.draw_img(address,Rectangle(question_flower[j].x-show_from,question_flower[j].y,SCALE,SCALE));
    delay(1);
   }
  for(int k=0;k<question_health.size();k++)
   {
    win.draw_img(address,Rectangle(question_health[k].x-show_from,question_health[k].y,SCALE,SCALE));
    delay(1);
   }
   win.update_screen();
  
 }
void Obstacle::find_obstacles(vector<string> v_map,char ch,vector<Rectangle> &v_obstacle,Window &win)
{
  for (int i=0;i<v_map.size();i++)
    for (int j=0;j<v_map[i].size();j++)
      if (v_map[i][j] == ch)
      v_obstacle.push_back(Rectangle(j*SCALE, MAP_COLUMN-SCALE*(v_map.size()-i),SCALE,SCALE));
}

void Obstacle::find_coin()
{
  for(int i=0;i<question_coin.size();i++)
    question_coin[i];
}


void Obstacle ::print_obstacle(vector<string> v_map,vector<Rectangle> &v_obstacle,Window &win,int show_from,string address)
{
  for(int i=0;i<v_obstacle.size();i++)
  {
  if(v_map[((v_obstacle[i].y- MAP_COLUMN)/SCALE+v_map.size())][((v_obstacle[i].x)/SCALE)]!='/') 
    win.draw_img(address,Rectangle(v_obstacle[i].x-show_from,v_obstacle[i].y,SCALE,SCALE));
  // else
  //   win.draw_img(QUESTION_EMPTY,Rectangle(v_obstacle[i].x-show_from,v_obstacle[i].y,SCALE,SCALE));    
  }
    
}

void Obstacle:: find_pipe(vector<string> v_map,Window &win)
{
  for(int i=0;i<v_map.size();i++)
  {
   for (int j=0;j<v_map[i].size();j++)
     if(v_map[i][j]=='|' && v_map[i][j+1]=='|'&& v_map[i+1][j]!='|')
        pipes.push_back(Rectangle(j*SCALE, MAP_COLUMN-SCALE*(v_map.size()-i),SCALE,SCALE));
  }
}

void Obstacle::print_pipe(vector<string> v_map,Window &win,int &show_from)
{
  for(int i=0;i<pipes.size();i++)
  {
    int counter=1;
     while(v_map[((pipes[i].y- MAP_COLUMN)/SCALE+v_map.size())-counter][((pipes[i].x)/SCALE)]!='.')
     { 
      win.draw_img(PIPE_LEFT,Rectangle(pipes[i].x-show_from,pipes[i].y-(counter-1)*SCALE,SCALE,SCALE));
      win.draw_img(PIPE_RIGHT,Rectangle(pipes[i].x-show_from+SCALE,pipes[i].y-(counter-1)*SCALE,SCALE,SCALE));
      counter++;
     } 
      win.draw_img(PIPE_HEAD_LEFT,Rectangle(pipes[i].x-show_from,pipes[i].y-(counter-1)*SCALE,SCALE,SCALE));
      win.draw_img(PIPE_HEAD_RIGHT,Rectangle(pipes[i].x-show_from+SCALE,pipes[i].y-(counter-1)*SCALE,SCALE,SCALE));
  }
}

void Obstacle::find_flag(vector<string> v_map,Window &win)
{
  for(int i=0;i<v_map.size();i++)
    for(int j=0;j<v_map[i].size();j++)
      if(v_map[i][j]=='f' && v_map[i+1][j]!='f')
        flag.push_back(Rectangle(j*SCALE, MAP_COLUMN-SCALE*(v_map.size()-i),SCALE,SCALE));
}

void Obstacle:: print_flag(vector<string> v_map,Window &win,int& show_from)
{
  int counter=1;       
  while(v_map[((flag[0].y- MAP_COLUMN)/SCALE+v_map.size())-counter][((flag[0].x)/SCALE)]!='.' )
  {
    win.draw_img(FLAG_BODY,Rectangle(flag[0].x-show_from,flag[0].y-(counter-1)*SCALE,SCALE,SCALE));
    counter++;
  }
  win.draw_img(FLAG_HEAD,Rectangle(flag[0].x-show_from,flag[0].y-(counter-1)*SCALE,SCALE,SCALE));
}

void Obstacle:: print_all(vector<string> &v_map,Window &win,int show_from)
{
  print_obstacle(v_map,clays,win,show_from,CLAY);
  print_obstacle(v_map,blocks,win,show_from,BLOCK);
  print_obstacle(v_map,bricks,win,show_from,BRICK);
  print_pipe(v_map,win,show_from);
  print_flag(v_map,win,show_from);
  print_question(v_map,win,show_from);
}

Obstacle:: Obstacle(vector<string> &v_map,Window &win,int show_from)
{
  find_obstacles(v_map,'#',clays,win);
  find_obstacles(v_map,'@',blocks,win);
  find_obstacles(v_map,'b',bricks,win);
  find_obstacles(v_map,'?',question_coin,win);
  find_obstacles(v_map,'m',question_flower,win);
  find_obstacles(v_map,'h',question_health,win);
  find_pipe(v_map,win);
  find_flag(v_map,win);
}
