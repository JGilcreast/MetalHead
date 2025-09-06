// John Gilcreast
// December 15th 2024
// Recipe class header file
// For use with Arduino Driver for Automatic Rebar Bender machine

#ifndef RECIPE_H
#define RECIPE_H

#define MAX_RECIPE_LINES 20
#define MAX_RECIPE_BENDS 5

class Recipe{
protected:
  int id = 0; // Id of 0 is invalid
  int lines[MAX_RECIPE_LINES][MAX_RECIPE_BENDS] = {}; // all elements = 0
  uint8_t linesCompleted = 0;
  int rebarSize = 0;
  char *name = nullptr;
  char *desc = nullptr; //description
  char *note = nullptr;

public:
  bool getlines(int[MAX_RECIPE_LINES][MAX_RECIPE_BENDS]);
  bool getline(int[MAX_RECIPE_BENDS]);
  bool setlines(int[MAX_RECIPE_LINES][MAX_RECIPE_BENDS]);
  void setline(int x, int y[MAX_RECIPE_BENDS]){for (int i=0;i<MAX_RECIPE_BENDS;i++) this->lines[x][i]=y[i];};
  char* getName(){return name;};
  void setName(char *name){this->name = name;};
  char* getDesc(){return desc;};
  bool completeLine() {this->linesCompleted++;};
  void setDesc(char *description){this->desc = description;};

};

#endif //RECIPE_H
