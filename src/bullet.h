#ifndef BULLET_H
#define BULLET_H
class Bullet {
protected:
public:
    double bulletx;
    double bullety;
    double direction;
    double stepsize;
    double health;
    double maxhp;
    int type;
    /**
        Deafault constructor for a Bullet
        @param void
        @return reference to a new bullet
    */
    Bullet();

    /**
        Constructor with inital parameters
        @param x the initial x position of the-bullet
        @param y the initial y position of the-bullet
        @param theta the initial direction of the bullet
        @param the bullet move type
        @return a reference to a new bullet
    */
    Bullet(double x, double y, double theta, double hp, int t);
    /**
        Get the x position of the bullet
        @param void
        @return the x position
    */
    double x();
    /**
        Get the y position of the bullet
        @param void
        @return the y position
    */
    double y();
    /**
        Function to delete this Bullet
        @param void
        @return void
    */
    void suicide();
    /**
        Broken functon to move the bullet forward
        @param void
        @return void
    */
    void forwardmove();
    /**
        Funciton to move the bullet forward given a step time
        @param d the time difference in seconds
        @return void
    */
    void forwardmove(double d);
    /** TODO this is a little busted
        Function to make a bullet curve
        @param x the change in diection between frames
        @return void
    */
    void curvemove(double x);

    /**
        Funciton to move the bullet in a swirl given a step time
        @param d the time difference in seconds
        @return void
    */
    void swirlmove(double d);
    /**
        Funciton to move the bullet in a swirl given a step time
        @param d the time difference in seconds
        @return void
    */
    void swirlreversemove(double d);
    /**
        Funciton to move the bullet "wandering" given a step time
        @param d the time difference in seconds
        @return void
    */
    void wandermove(double d);
    /**
        Funciton to move the bullet around ship given a step time
        @param d the time difference in seconds
        @param sx the ship's x coordinate
        @param sy the ship's y coordinate
        @param pol the polarity of spin
        @return void
    */
    void circlelazymove(double d, double sx, double sy);

    void circlemove(double d, double sx, double sy, double sv, double sdir);

    // TODO replace
    void shittyrender(double x);
};
#endif
