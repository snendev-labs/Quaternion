#ifndef GOODGUY_H
#define GOODGUY_H
#include <vector>
using namespace std;
class Goodguy {
public:
    double shipx;
    double shipy;
    double renderDirection; // in radians
    double moveDirection;
    double stepsize; // in relative frame at 60 fps (?)
    double pixsize;
    vector<vector<bool> > spriteshape;
    vector<vector<vector<double> > > spriteskin;
    bool onup;
    bool ondown;
    bool onleft;
    bool onright;
    bool tomove;
    /**
        Default constructor, does nothing
        @param void
        @return a pointer to a new Goodguy
    */
    Goodguy();
    /**
        Render the space ship
        @param void
        @return void
    */
    void render();
    /**
        Get the ship's x postition
        @param void
        @return a x position
    */
    double x();
    /**
        Get the ship's y postition
        @param void
        @return a y position
    */
    double y();
    /**
        Get the ship's direction
        @param void
        @return the ships direction in radians
    */
    double getDirection();
    /**
        Set the x coordiate of the ship
        @param x the new coordinate
        @return void
    */
    void setX(double x);
    /**
        Set the y coordinate of the ship
        @param y the new coordinate
        @return void
    */
    void setY(double y);
    /**
        Set the direction of the ship
        @param theta the new direction
        @return void
    */
    void setDirection(double theta);
    /**
        Set the stepsize of the ship
        @param x the new stepsize
        @return void
    */
    void setStepSize(double x);
    /**
        Set the spriteshape
        @param dat the new sprite
        @return void
    */
    void setSpriteData(vector<vector<bool> > dat1,vector<vector<vector<double> > > dat2);
    /**
        Move the guy foward
        @param d the time elapsed between frames
        @return void
    */
    void forwardmove(double d);
    /**
        Check the guy is on screen and take action if not
        @param void
        @return void
    */
    void checkonscreen();
    /**
        Modify the sprite's move direction
        @param d the direction code
        @param b whether to turn on or off the direction d
        @return void
    */
    void modifyDirection(int d, bool b);
};
#endif
