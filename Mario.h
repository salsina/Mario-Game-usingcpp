#ifndef MARIO_H
#define MARIO_H

#include <vector>
#include <string>
#include "src/rsdl.hpp"
#include "Obstacle.h"
#include "Config.h"
#include "Functions.h"

using namespace std;

class Mario
{
public:

Mario(vector<string> v_map,Window &win);
Rectangle show_mario_position();
vector<Rectangle> return_little_goomba();
string show_direction();
void set_direction(string direct);
void fall_down(vector<string> v_map,Window &win,int &show_from,Obstacle* obs);
void check_falling_down(vector<string> v_map,Window &win,int &show_from,Obstacle* obs);
int show_speed_x();
int return_mario_lives();

void set_speed_x(int speed);
int show_speed_y();
void set_speed_y(int speed);
void check_under(vector<string> v_map,Window &win,int &show_from,Obstacle* obs);
void check_front(vector<string> v_map,Window &win,int &show_from,Obstacle* obs);
void print_jump_image(Window &win,int &show_from);
void check_question_coin(vector<string> &v_map,Window &win,int& show_from,Obstacle* obs);
void show_mario_coins(Window &win);
void show_mario(vector<string> v_map,Window &win,int &show_from,string address,Obstacle* obs);
void print_walk_image(vector<string> v_map,Window &win,int &show_from,Obstacle* obs,string address);
void move_right(vector<string> v_map,Window &win,int &show_from,Obstacle* obs, int &type_right);
void move_left(vector<string> v_map,Window &win,int &show_from,Obstacle* obs,int &type_left);
void check_jump_direction(int &show_from);
void jump_down(vector<string> v_map,Window &win,int &show_from,Obstacle* obs);
void jump_up(vector<string> &v_map,Window &win,int &show_from,Obstacle* obs);
void jump(vector<string> &v_map,Window &win,int &show_from,Obstacle* obs);
void set_window(vector<string> &v_map,Window &win,int &show_from,Obstacle* obs);
void check_question_health(vector<string> &v_map,Window &win,int& show_from,Obstacle* obs);
void check_click(vector<string> &v_map,Window &win,int &show_from,char click,Obstacle* obs);
void find_enemy(vector<string> v_map,char ch,vector<Rectangle> &v_enemy);
void print_enemy(vector<string> &v_map,vector<Rectangle> &v_enemy,Window &win,int &show_from,string address,Obstacle* obs);
void move_enemy(vector<Rectangle> &v_enemy,vector<string> &v_map,int i,Window &win,string address,int &show_from,Obstacle* obs);
void print_dead_mario(vector<string> v_map,Window &win,int &show_from,Obstacle* obs);

private:

Rectangle mario_position=Rectangle(1,1,SCALE,SCALE);
int mario_vx=0;
int mario_vy=0;
string direction="RIGHT";
int mario_coins=0;
int mario_lives=3;
vector<Rectangle> little_goomba;
vector<Rectangle> koopa_troopa;
};



#endif