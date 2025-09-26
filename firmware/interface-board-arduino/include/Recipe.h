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
  uint8_t totalLines = 0;
  int rebarSize = 0;
  char *name = nullptr;
  char *desc = nullptr; //description
  char *note = nullptr;

public:
  void getlines(uint8_t[MAX_RECIPE_LINES][MAX_RECIPE_BENDS]);
  bool getline(uint8_t lineNumber){return this->lines[lineNumber];};
  bool setlines(uint8_t[MAX_RECIPE_LINES][MAX_RECIPE_BENDS]);
  void setline(uint8_t x, uint8_t y[MAX_RECIPE_BENDS]){for (int i=0;i<MAX_RECIPE_BENDS;i++) this->lines[x][i]=y[i];}
  char* getName(){return name;}
  void setName(char *name){this->name = name;}
  char* getDesc(){return desc;}
  void completeLine() {this->linesCompleted++;}
  uint8_t getLinesCompleted(){return this->linesCompleted;}
  uint8_t getTotalLines(){return this->totalLines;}
  void completeBend(){}
  void setDesc(char *description){this->desc = description;}

};

#endif //RECIPE_H
