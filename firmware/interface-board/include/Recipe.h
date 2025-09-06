// John Gilcreast
// December 15th 2024
// Recipe class header file
// For use with Arduino Driver for Automatic Rebar Bender machine

#ifndef RECIPE_H
#define RECIPE_H

class Recipe{
protected:
  int id = 0; // Id of 0 is invalid
  int lines[20][5] = {}; // all elements = 0
  u
  int rebarSize = 0;
  char *name = nullptr;
  char *desc = nullptr; //description
  char *note = nullptr;

public:
  bool getlines(int[20][5]);
  bool getline(int[5]);
  bool setlines(int[20][5]);
  void setline(int x, int y[5]){for (int i=0;i<5;i++) this->lines[x][i]=y[i];};
  char* getName(){return name;};
  void setName(char *name){this->name = name;};
  char* getDesc(){return desc;};
  void setDesc(char *description){this->desc = description;};

};

#endif //RECIPE_H
