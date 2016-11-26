#ifndef BADGUY_H
#define BADGUY_H
#include <vector>
using namespace std;
class Badguy {
public:
    double shipx;
    double shipy;
    double direction; // in radians
    double sightdistance;
    double stepsize; // in relative frame at 60 fps
    double pixsize;
    double hitradius;
    bool isAlive;
    vector<double> color;
    vector<vector<bool> > spriteshape;
    vector<vector<vector<double> > > spriteskin;
    /**
        Default constructor, to override in subclasses
        @param void
        @retun a pointer to a Badguy object
    */
    Badguy();
    /**
        Constructor with iitial parameters
        @param x the initial x-position
        @param y the initial y-position
        @param theta the intial direction
        @return a pointer to a Badguy object
    */
    Badguy(double x, double y, double theta);
    /**
        Get the ship's x postition
        @param void
        @return an x positon
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
        Get the hit radius of a badguy ship
        @param void
        @return the hit radius
    */
    double getHitRadius();
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
        Set to color of the ship
        @param c the RGB vector as doubles
        @return void
    */
    void setColor(vector<double> c);
    /**
        Set the spriteshape
        @param dat the new sprite
        @return void
    */
    void setSpriteData(vector<vector<bool> > dat1,vector<vector<vector<double> > > dat2);
    /**
        Renders the ship using GLUT
        @param void
        @return void
    */
    void render();
    /**
        Moves the ship forward given the amount of time that
        @param d the amount of time that has passed in seconds
        @return void
    */
    void forwardmove(double d);
    /**
        Implements Reynold's flock model, moves ship in with flock, given the
        amount of time that has passed
        @param flock the other bad guys in the flock
        @param d the aount of time that has passed
        @return void
    */
    void flockmove(vector<Badguy *> flock, double d);
    /**
        Broken, moves ship toward point (x, y)
        @param x first argument of target position
        @param y second argument of the target position
        @param
    */
    void trackmove(double x, double y, double d);
    /**
        Implement drunken walk, given the amount of time that has passed
        @param theta the direction to move
        @param d the aount of time that has passed in seconds
        @return void
    */
    void directionandmove(double theta, double d);
    /**
        Run away once the stage or level is over given an amaount of time that
        has passed
        @param d the amount of time that has passed in seconds
        @return void
    */
    void flee(double d);
    /**
        Generates arguments to generate a Bullet fired foward
        @param void
        @return the data needed to make a bullet (inital x, initial y,
        direction)
    */
    vector<double> fireforward();
    /** TODO optimize implementation
        Generated the arguments to generate Bullets fired in all directions
        @param x number of bullets to fire at a time
        @return array of bullet data (inital x, initial y, direction)
    */
    vector<vector<double> > firecircle(int x);
    /** TODO optimize implementation
        Generated the arguments to generate Bullets fired in all directions
        @param x number of bullets to fire at a time
        @param d radial offset
        @return array of bullet data (inital x, initial y, direction)
    */
    vector<vector<double> > firecircle(int x, double d);
    /**
        Generates bullet data for a bullet shot at (x, y) target given
        @param x first argument of target position
        @param y second argument of the target position
        @return the data needed to make a bullet (inital x, initial y, direction)
    */
    vector<double> firedirect(int goodguyx, int goodguyy);
    /**
        Check that the ship is on screen and teleport it if neccesary
        @param void
        @return void
    */
    void checkonscreen();
};
#endif
