#include <GL/gl.h>
#include "bullet.h"
#include <vector>
#include "math.h"
using namespace std;

Bullet::Bullet() {

}
Bullet::Bullet(double x,double y, double theta, double hp, int t) {
    bulletx=x;
    bullety=y;
    direction=theta;
    health=hp;
    maxhp=hp;
    type=t;
    if(t == 0){
      stepsize=100.0;
    } else if (t == 1){
      stepsize=100.0;
    } else if (t == 2){
      stepsize=100.0;
    } else if (t == 3){
      stepsize=100.0;
    } else if (t == 4){
      stepsize=100.0;
    } else if (t == 5){
      stepsize=100.0;
    } else if (t == 6){
      stepsize=100.0;
    }
}
double Bullet::x() {
    return bulletx;
}
double Bullet::y() {
    return bullety;
}
void Bullet::suicide() {
    delete this;
}
void Bullet::forwardmove() {
    bulletx+=cos(direction)*stepsize;
    bullety+=sin(direction)*stepsize;
}
void Bullet::forwardmove(double d) {
    bulletx+=cos(direction)*stepsize*d/60.0;
    bullety+=sin(direction)*stepsize*d/60.0;
}
void Bullet::curvemove(double x) {
    direction+=x;
    forwardmove(x);
}
void Bullet::swirlmove(double d) {
    bulletx+=cos((maxhp - health)*15.0)*d*2;
    bullety+=sin((maxhp - health)*15.0)*d*1.5;
    forwardmove(d);
}
void Bullet::swirlreversemove(double d) {
    bulletx-=cos((maxhp - health)*15.0)*d*2;
    bullety+=sin((maxhp - health)*15.0)*d*1.5;
    forwardmove(d);
}
void Bullet::wandermove(double d) {
    //direction+=rand;
    direction+=sin((maxhp-health)*1000.0)*d*stepsize;
    forwardmove(d);
}
void Bullet::circlelazymove(double d, double shipx, double shipy){
    double dx = bulletx-shipx;
    double dy = bullety-shipy;
    double tmp;
    if(dx >= 0 && dy >= 0){ //Quad 1
        tmp = atan(dy/dx) + M_PI/2;
    } else if(dx < 0 && dy >= 0){ //Quad 2
        tmp = atan(dy/dx) + 3*M_PI/2;
    } else if(dx < 0 && dy < 0){ //Quad 3
        tmp = atan(dy/dx) - M_PI/2;
    } else {
        tmp = atan(dy/dx) + M_PI/2;
    }
    direction = tmp;
    forwardmove(d);
}

void Bullet::circlemove(double d, double shipx, double shipy, double shipv, double shipdir, bool moving){
    double dx = bulletx-shipx;
    double dy = bullety-shipy;
    if(dx >= 0 && dy >= 0){ //Quadrant 1
        direction = atan(dy/dx) + M_PI/2;
    } else if(dx < 0 && dy >= 0){ //Q2
        direction = atan(dy/dx) + 3*M_PI/2;
    } else if(dx < 0 && dy < 0){ //Q3
        direction = atan(dy/dx) - M_PI/2;
    } else { //Q4
        direction = atan(dy/dx) + M_PI/2;
    }
    if(moving){
      bulletx+=shipv*cos(shipdir)*d/60.0;
      bullety+=shipv*sin(shipdir)*d/60.0;
    }
    forwardmove(d);
}

void Bullet::shittyrender(double x) {
    glBegin(GL_POLYGON);
        glVertex3f(bulletx+x/2,bullety+x/2,0.0);
        glVertex3f(bulletx+x/2,bullety-x/2,0.0);
        glVertex3f(bulletx-x/2,bullety-x/2,0.0);
        glVertex3f(bulletx-x/2,bullety+x/2,0.0);
    glEnd();
}
