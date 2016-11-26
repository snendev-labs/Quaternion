#include <GL/gl.h>
#include "shield.h"
#include <vector>
#include <iostream>
#include "math.h"
using namespace std;

Shield::Shield(){}

Shield::Shield(double x, double y, double w, double h, double dur){
    shieldx = x;
    shieldy = y;
    shieldw = w;
    shieldh = h;
    duration = dur;
}

Shield::Shield(const Shield *other){
    shieldx = other->shieldx;
    shieldy = other->shieldy;
    shieldw = other->shieldw;
    shieldh = other->shieldh;
    duration = other->duration;
}

void Shield::forwardmove(double dir, double d, double sp){
    cout << "BarrierDir: " << dir << endl;
    shieldx+=cos(dir)*sp*d/60.0;
    shieldy+=sin(dir)*sp*d/60.0;
}
    
void Shield::supershittyrender(){
    glBegin(GL_POLYGON);
        glVertex3f(shieldx+shieldw/2,shieldy+shieldh/2,0.0);
        glVertex3f(shieldx+shieldw/2,shieldy-shieldh/2,0.0);
        glVertex3f(shieldx-shieldw/2,shieldy-shieldh/2,0.0);
        glVertex3f(shieldx-shieldw/2,shieldy+shieldh/2,0.0);
    glEnd();
}



