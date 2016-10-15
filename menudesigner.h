#ifndef MENUDESIGNER_H
#define MENUDESIGNER_H
#include <vector>
#include <string>
#include <algorithm>
#include "button.h"
#include "levelstats.cpp"
using namespace std;

class MenuDesigner{
public:
    int progression;
    int questsComplete;
    int bossesBeat;
    int portalsPassed; //probably should just be per-node, rather than persistent
    int playerMoneys; //better to put this elsewhere i think
    vector<Button> menuButtons;
    vector<TextBox>
    vector<LevelStat> nodeStats;
    map<int,vector<int> > nodeGraph;
    /**
        Default constructor, returns a pointer to an empty MenuDesigner object
        @param void
        @return a pointer to a new MenuDesigner object
    */
    MenuDesigner();
    /**
        Fuction to call the renderer for the current state of the menu
        @param void
        @param void
    */
    void render();
    /**
        @param x1 the x coordinate of the top left corner of the button
        @param y1 the y coordinate of the top left corner of the button
        @param x2 the x coordinate of the bottom right corner of the button
        @param y2 the y coordinate of the bottom right corner of the button
        @param buttonText the text displayed on the button
        @param style the style the button should be rendered in
    */
    void addMenuButton(double x1, double y1, double x2, double y2, string buttonText, int style);
    /**
        Function to set a button's on-hover function
        @param btn a pointer to the button to modify
        @param onHoverFunc the function to execute when the mouse hovers over
        btn
        @return void
    */
    void onButtonHover(Button * btn, void (*onHoverFunc)(void));
    /**
        Function to set a button's on-click function
        @param btn a pointer to the button to modify
        @param onClickFunc the function to execute when the mouse clicks on btn
        @return void
    */
    void onButtonClick(Button btn, void (*onClickFunc)(void));
    /**
        Function to generate a map for the rest of the game to occur on
        @param void
        @param void
    */
    void initMap();
    /**
        Begin level, should transfer control to level designer
        @param void
        @reutrn void
    */
    void execLevel();
    /**
        Access LevelStats for a given node
        @param i the index of the level from which to read
        @return a copy of the seed information about the level
    */
    LevelStats getQuestStats(int i);
    /**
        Function to add a text window to the menu
        @param x1 the x coordinate of the top left corner of the text box
        @param y1 the y coordinate of the top left corner of the tect box
        @param x2 the x coordinate of the bottom right corner of the text box
        @param y2 the y coordinate of the bottom right corner of the text box
        @param text the text displayed on the test box
        @param style the style in which the text box should be rendered
    */
    void generateTextWindow((double x1, double y1, double x2, double y2, string buttonText, int style););
    /**
        Function to close a text window by a given index
        @param void
        @param void
    */
    void closeTextWindow();
}
#endif
