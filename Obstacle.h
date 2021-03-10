#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <vector>
#include <string>
#include "src/rsdl.hpp"
#include "Config.h"
#include "Functions.h"

using namespace std;

class Obstacle{
public:

Obstacle(vector<string> &v_map,Window &win,int show_from);
void find_obstacles(vector<string> v_map,char ch,vector<Rectangle> &v_obstacle,Window &win);
void find_coin();
void print_obstacle(vector<string> v_map,vector<Rectangle> &v_obstacle,Window &win,int show_from,string address);
void find_pipe(vector<string> v_map,Window &win);
void print_pipe(vector<string> v_map,Window &win,int &show_from);
void find_flag(vector<string> v_map,Window &win);
void print_flag(vector<string> v_map,Window &win,int &show_from);
void find_enemy(vector<string> &v_map,char ch,vector<Rectangle> &v_enemy);
void print_question(vector<string> v_map,Window &win,int show_from);
void print_all(vector<string> &v_map,Window &win,int show_from);

private:

  vector<Rectangle> clays;
  vector<Rectangle> blocks;
  vector<Rectangle> bricks;
  vector<Rectangle> question_coin;
  vector<Rectangle> question_flower;
  vector<Rectangle> question_health;
  vector<Rectangle> pipes;
  vector<Rectangle> flag;
  int frame = 1;
};

#endif