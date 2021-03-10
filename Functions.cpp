#include "Functions.h"
#include "Config.h"


void change_map(vector<string> &v_map,int i,int j,char ch)
{
 v_map[i][j]=ch;
}

void print_background(Window &win,int &show_from)
{
 if(show_from% BACKGROUND_LENGTH <=BACKGROUND_LENGTH-MAP_ROW)
   win.draw_img(BACKGROUND,Rectangle(0,0,MAP_ROW,MAP_COLUMN),Rectangle(show_from % BACKGROUND_LENGTH,0,MAP_ROW,1600));
  else
  {
    win.draw_img(BACKGROUND,Rectangle(0,0,BACKGROUND_LENGTH-(show_from%BACKGROUND_LENGTH),MAP_COLUMN),Rectangle(show_from % BACKGROUND_LENGTH,0,BACKGROUND_LENGTH-(show_from%BACKGROUND_LENGTH),1700));
    win.draw_img(BACKGROUND,Rectangle(BACKGROUND_LENGTH-(show_from%BACKGROUND_LENGTH),0,(show_from%BACKGROUND_LENGTH)-BACKGROUND_LENGTH+MAP_ROW,MAP_COLUMN),Rectangle(0,0,(show_from%BACKGROUND_LENGTH)-BACKGROUND_LENGTH+MAP_ROW,1700));
  }
}

vector<string> read_map( vector<string> v_map, string mapAddress)
{
   string line;
   ifstream map(mapAddress);
   while(getline(map, line))
   {
     v_map.push_back(line);
   }
   map.close();
  return v_map;
}

