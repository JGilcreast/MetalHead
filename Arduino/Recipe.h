// John Gilcreast
// December 15th 2024
// Recipe class header file
// For use with Arduino Driver for Automatic Rebar Bender machine

#pragma once
#include <string>
using namespace std;

class Recipe{
    protected:
        int lines[20][5] = {}; // all elements = 0
        int rebarSize;
        string name;
        string desc; //description
        string note;
        //date saved

    public:
        Recipe();
        bool getlines(int[20][5]);
        bool getline(int[5]);
        bool setlines(int[20][5]);
        bool setline(int, int[5]);
        string getName();
        bool setName();
        string getDesc(string);
        bool setDesc(string);
        string getDesc(string);
        bool setDesc(string);
        //getDate();


};