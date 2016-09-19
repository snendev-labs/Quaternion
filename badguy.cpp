#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include "badguy.h"
#include "math.h"
using namespace std;

Badguy::Badguy() {
    shipx=0.0;
    shipy=0.0;
    direction=1.5*M_PI; // in radians
    sightdistance=.25;
    stepsize=25.0;
    pixsize=.0025;
    hitradius=6*pixsize;
    isAlive=true;
}
Badguy::Badguy(double x, double y, double theta) {
    shipx=x;
    shipy=y;
    direction=theta; // in radians
    sightdistance=50;
    stepsize=100.0;
    pixsize=.005;
    hitradius=6*pixsize;
    isAlive=true;
}
double Badguy::getHitRadius() {
    return hitradius;
}
double Badguy::x() {
    return shipx;
}
double Badguy::y() {
    return shipy;
}
double Badguy::getDirection() {
    return direction;
}
void Badguy::setX(double x) {
    shipx=x;
}
void Badguy::setY(double y) {
    shipy=y;
}
void Badguy::setDirection(double theta) {
    direction=theta;
}
void Badguy::setStepSize(double x) {
    stepsize=x;
}
void Badguy::render() {
    //cout<<"Rendering"<<endl;
    glColor3f(0,1,0);
    if(spriteshape.size()>0) {
        if(spriteshape[0].size()>0) {
            double length=spriteshape.size()*1.0;
            double width=spriteshape[0].size()*1.0;
            for(int k=0;k<spriteshape.size();k++) {
                double internal_y=1.0*k+0.5-length/2.0;
                for(int k1=0;k1<spriteshape[k].size();k1++) {
                    double internal_x=1.0*k1+0.5-width/2.0;
                    if(spriteshape[k][k1]) {
                        if(spriteskin.size()>k) {
                            if(spriteskin[k].size()>k1) {
                                glColor3f(spriteskin[k][k1][0],spriteskin[k][k1][1],spriteskin[k][k1][2]);
                            }
                        }
                        glBegin(GL_POLYGON);
                            glVertex3f(shipx+pixsize*((internal_x+.5)*sin(direction)+(internal_y+.5)*cos(direction)),
                                shipy+pixsize*((internal_x+.5)*cos(direction)-(internal_y+.5)*sin(direction)),
                                0.0);
                            glVertex3f(shipx+pixsize*((internal_x+.5)*sin(direction)+(internal_y-.5)*cos(direction)),
                                shipy+pixsize*((internal_x+.5)*cos(direction)-(internal_y-.5)*sin(direction)),
                                0.0);
                            glVertex3f(shipx+pixsize*((internal_x-.5)*sin(direction)+(internal_y-.5)*cos(direction)),
                                shipy+pixsize*((internal_x-.5)*cos(direction)-(internal_y-.5)*sin(direction)),
                                0.0);
                            glVertex3f(shipx+pixsize*((internal_x-.5)*sin(direction)+(internal_y+.5)*cos(direction)),
                                shipy+pixsize*((internal_x-.5)*cos(direction)-(internal_y+.5)*sin(direction)),
                                0.0);
                        glEnd();
                    }
                }
            }
        }
    }
}
void Badguy::forwardmove(double d) {
    shipx+=cos(direction)*stepsize*d/60.0;
    shipy+=sin(direction)*stepsize*d/60.0;
    checkonscreen();
}
void Badguy::flockmove(vector<Badguy *> flock, double d) { // TODO convert vector to &vector
    vector<Badguy *> visible;
    for(int k=0;k<flock.size();k++) {
        if(flock[k]!=this) {
            //cout<<"Not Me!"<<endl;
            if(abs(direction-atan2((flock[k]->y())-shipy,(flock[k]->x())-shipx))<.8*M_PI) {
                //cout<<"insight"<<endl;
                if(((flock[k]->x())-shipx)*((flock[k]->x())-shipx)+
                        ((flock[k]->y())-shipy)*((flock[k]->y())-shipy)<sightdistance*sightdistance) {
                    //cout<<"flock found"<<endl;
                    visible.push_back(flock[k]);
                }
            }
        }
    }
    if(visible.size()>0) {
        double newx=0, newy=0;
        for(int k=0;k<visible.size();k++) {
            newx+=visible[k]->x();
            newy+=visible[k]->y();
        }
        newx/=visible.size();
        newy/=visible.size();
        this->trackmove(newx,newy,d);
        //this->trackmove(0.5,0.5,d);
    }
    else {
        forwardmove(d);
    }
    checkonscreen();
    //this->forwardmove(d);
}
void Badguy::trackmove(double x, double y,double d) {
    direction=atan2(y-shipy,x-shipx);
    this->forwardmove(d);
    checkonscreen();
}
void Badguy::directionandmove(double theta, double d) { // slow, consider optimization
    direction=theta;
    this->forwardmove(d);
    checkonscreen();
}
vector<double> Badguy::fireforward() {
    vector<double> toret={shipx,shipy,direction};
    return toret;
}
vector<double> Badguy::firedirect(int x, int y) {
    vector<double> toret={shipx,shipy,atan2(y-shipy,x-shipx)};
    return toret;
}
vector<vector<double> > Badguy::firecircle(int x) {
    vector<vector<double> > toret;
    for(int k=0;k<x;k++) {
        vector<double> temp={shipx,shipy,2.0*k*M_PI/x};
        toret.push_back(temp);
    }
    return toret;
}
vector<vector<double> > Badguy::firecircle(int x, double d) {
    vector<vector<double> > toret;
    for(int k=0;k<x;k++) {
        vector<double> temp={shipx,shipy,k*M_2_PI/x+d};
        toret.push_back(temp);
    }
    return toret;
}
void Badguy::setSpriteData(vector<vector<bool> > dat1, vector<vector<vector<double> > > dat2) {
    spriteshape=dat1;
    spriteskin=dat2;
}
void Badguy::flee(double d) {
    direction=M_PI_2;
    shipx+=cos(direction)*stepsize*d/60.0;
    shipy+=sin(direction)*stepsize*d/60.0;
    //this->forwardmove(d);
}
void Badguy::checkonscreen() {
    if(shipx<0.0) {
        shipx=1.0+shipx;
    }
    else if(shipx>1.0) {
        shipx=shipx-1.0;
    }
    if(shipy<-1.0) {
        //cout<<"BLIP"<<endl;
        shipy=1.0;//+shipy;
    } else if(shipy>1.0) {
        shipy=shipy-1.0;
    }
}
