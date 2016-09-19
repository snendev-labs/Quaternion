#ifndef SHIELD_H
#define SHIELD_H
class Shield {
protected:
public:
    double shieldx;
    double shieldy;
    double shieldw;
    double shieldh;
    double duration;

    Shield();
    Shield(double x, double y, double w, double h, double dur);
    Shield(const Shield *other);

    void suicide();
    
    void forwardmove(double dir, double d, double sp);
    
    void supershittyrender();
};
#endif
