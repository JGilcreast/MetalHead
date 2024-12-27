// John Gilcreast
// December 15th 2024
// Interface class header file
// For use with Arduino Driver for Automatic Rebar Bender machine

#pragma once
#include <string>
#include "Recipe.h"
using namespace std;

enum outputSignal{
    LOW,
    HIGH
};

class Interface{
    private:
        Recipe loadedRecipe;
    protected:
        bool updateUi(); //update screen with new information
        bool run(); // Do a single run of the loaded recipe
    public:
        Interface();
        bool loadLast();
        bool setLine();
        bool save(int); //save loadedRecipe into selected storage slot
        bool load(int); //load selected slot into loadedRecipe and updateUI
        bool shear();

};