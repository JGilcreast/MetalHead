// John Gilcreast
// December 15th 2024
// Arduino driver for Automatic Rebar Bender

#include <iostream>
//#include "Interface.cpp" //Operations between the UI and the machine 
using namespace std;

int main(){
    //Startup process

    //Interface interface;
    //interface.loadLast(); // Get last settings
    //load saved global settings into memory

    //Main loop

    bool exit = false;
    while(exit != true){
        //User Selections
        //Change recipe values / name / description / note
        // - Call getter/setter loadedRecipe.___() methods
        //Save Recipe
        // - Call interface.save(slot)
        //Load Recipe
        // - Call interface.load(slot)
        // - Update display with new values
        //Test Run
        // - Call interface.run(1)
        //Normal Run
        // - Call interface.run(n)
        //--Settings Menu--
        //Diagnostics
        // - Show sensor status
        // - trigger solenoids individually
        //Machine Settings
        // - Rebar size
        // - Date/Time adjust
        
        //wait
        //loop
    }
    //Cleanup, powerdown, and exit
    return 0;
}