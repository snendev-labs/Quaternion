#ifndef MENUDESIGNER_H
#define MENUDESIGNER_H
#include <vector>
#include <ctime>
#include "goodguy.h" //should only need goodguy, maybe leveldesigner
using namespace std;

class MenuDesigner{
public:
    int progression; //tracks user progress thru game ("tier" of nodes), to scale difficulty
    //isn't needed since we can code this into nodes themselves
    int questsComplete;
    int bossesBeat;
    int portalsPassed; //probably should just be per-node, rather than persistent
    int playerMoneys; //better to put this elsewhere i think


    //but maybe people like to know that stat!

    /*
    two parts of the menuDesigner:
        1) upgrades/store (as one thing)
        2) path map
    these can appear at once, or with a state-swap "tabs" type setup
    */

    //vector<Level *> nodes;
    //"level *" just describes some struct of seeds to give to leveldesigner
    //Level * currentNode;

    //some references to a data-type containing our total inventory of possible "items" n shit
    //"items" are just bullet dmg/speed upgrades and new bullet types for the player
    //check in with me if you need to know how this looks from a design perspective
    //very likely a counter is the better way to go for anything except for bullet types
    //though maybe we implement boosters and other mobility-oriented things, warpers ("flash" from LoL), etc.

    //maybe the player's actual "inventory", you pick where that goes tho
    //some vector of the buttons you can press i guess
    /**
        Function to render the menu
        @param void
        @reuturn void
    */
    void render();
    /**
    */
    void addMenuButton();
    void getMenuButton();
    void highlight(); //changes a value in a struct or something, basically for "onmousehover" button highlighting
    int onMenuHover(); //some "where is the mouse" type shit
    int onMenuClick(); //above + onMouseDown()
    //obviously per-frame we call

    //some getShipStats or getPlayerStats thing, i don't think we need anything here because we have the goodguy class...w/e
    int initMap(); //creates node-map for gameplay, with seeds n shit, returns success bool
    void execLevel(); //sets up level initial shit, then starts the level

    void getQuestStats(); //gets info about user quest data from levels
    //prob also an "int isQuestComplete" type thing
    void generateReward(); //generates what rewards the user should gets
    void rewardPlayer(); //actually give the player the reward
    void initQuestResponse(); //generates message for quest completion, and reward

    void generateTextWindow(); //exactly what it sounds like, should be "over" the main menu
    void closeTextWindow(); //on click of an "ok" button

}
