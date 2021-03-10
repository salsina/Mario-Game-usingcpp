#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include "src/rsdl.hpp"
#include "Config.h"
#include <fstream>

using namespace std;

void change_map(vector<string> &v_map,int i,int j,char ch);
void print_background(Window &win,int &show_from);
vector<string> read_map( vector<string> v_map, string mapAddress);

#endif