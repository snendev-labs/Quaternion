#ifndef LEVELDESIGNER_H
#define LEVELDESIGNER_H
#include <vector>
#include <ctime>
#include "badguy.h"
#include "bullet.h"
#include "badguy.h"
#include "goodguy.h"
#include "shield.h"
using namespace std;
class LevelDesigner {
public:
    vector<vector<Badguy *> > flocks;
    vector<Badguy *> singlebadguys;
    vector<Bullet *> * goodguybullets;
    vector<Bullet *> * badguybullets;
    Goodguy * goodguy;
    Shield * shield;
    int equippedBullet;
    int minStageNumBadGuys;
    bool onResetStage;
    bool onResetFlee;
    double goodguyFireRate;
    int goodguydirection;
    double timeSinceLastGoodguyFire;
    int stageNum;
    int readyFire;
    int shieldUp;
    int paused;
    // TIME STUFF
    clock_t currenttime;
    clock_t lasttime;
    double deltatime;

    /**
        Default constructor
        @param void
        @return a refernece to a LevelDesigner
    */
    LevelDesigner();
    /**
        Initialize the state of the level
        @param void
        @return void
    */
    void begin();
    /**
        Checks the state of the game and performs any level designing functions
        @param void
        @return void
    */
    void notes();
    /**
        Move the state of the game forward one step
        @param void
        @return void
    */
    void step();
    /**
        Check if the level-stage is done
        @param void
        @return if the stage is complete
    */
    bool checkstagedone();
    /**
        Create a bit design for a spaceship
        @param void
        @return the design of the spaceship as an bool matrix
    */
    vector<vector<bool> > createSpaceship();
    /**
        Colorlize a spaceship design
        @param design the output of createSpaceship()
        @return a matrix of vectors representing the color values of each of
        the pixels
    */
    vector<vector<vector<double> > > monoColorizeShipDesign(vector<vector<bool> > design);
    /**
        Add the external edges to the ship for non-transaprent rendering
        @param the edgeless design of the ship
        @return a design with edges
    */
    vector<vector<bool> > addEdgesToDesign(vector<vector<bool> > design);
    /**
        Function to render to the screen
        @param void
        @return void
    */
    void render();
    /**
        Calculate a stochastic number of flocks that should be on screen for a
        given stage
        @param x the stage number
        @return a number of flocks
    */
    int getNumFlocksAtStage(int x);
    /**
        Calculate a stochastic number of badguys in a flock for a given stage
        @param x the stage number
        @return a number of badguys
    */
    int getFlockSizeAtStage(int x);
    /**
        Calculate a stochastic number of single badguys for a given stage
        @param x the stage number
        @return a number of badguys
    */
    int getNumSingleBadGuysAtStage(int x);
    /**
        Check for collisions and take action
        @param void
        @reurn void
    */
    void checkcollisions();
    /**
        Force the stage to reset
        @param void
        @return void
    */
    void resetStage();
    /**
        Set the direction of the good guy ship
        @param d the numeric code for the direction
        @param b whether to turn direction d on or off
        @return void
    */
    void setDirection(int d,bool b);

    void changeBulletNext();
    void changeBulletLast();
    
    void summonShield();
};
#endif
