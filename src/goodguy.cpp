#include "goodguy.h"
#include <GL/gl.h>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
Goodguy::Goodguy() {
    shipx=0.0;
    shipy=0.0;
    renderDirection=.5*M_PI; // in radians
    moveDirection=.5*M_PI; // in radians
    stepsize=100;
    pixsize=.0025; // expected
    onup=false;
    ondown=false;
    onleft=false;
    onright=false;
    tomove=false;
}
void Goodguy::render() {
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
                            glVertex3f(shipx+pixsize*((internal_x+.5)*sin(renderDirection)+(internal_y+.5)*cos(renderDirection)),
                                shipy+pixsize*((internal_x+.5)*cos(renderDirection)-(internal_y+.5)*sin(renderDirection)),
                                0.0);
                            glVertex3f(shipx+pixsize*((internal_x+.5)*sin(renderDirection)+(internal_y-.5)*cos(renderDirection)),
                                shipy+pixsize*((internal_x+.5)*cos(renderDirection)-(internal_y-.5)*sin(renderDirection)),
                                0.0);
                            glVertex3f(shipx+pixsize*((internal_x-.5)*sin(renderDirection)+(internal_y-.5)*cos(renderDirection)),
                                shipy+pixsize*((internal_x-.5)*cos(renderDirection)-(internal_y-.5)*sin(renderDirection)),
                                0.0);
                            glVertex3f(shipx+pixsize*((internal_x-.5)*sin(renderDirection)+(internal_y+.5)*cos(renderDirection)),
                                shipy+pixsize*((internal_x-.5)*cos(renderDirection)-(internal_y+.5)*sin(renderDirection)),
                                0.0);
                        glEnd();
                    }
                }
            }
        }
    }
}
double Goodguy::x() {
    return shipx;
}
double Goodguy::y() {
    return shipy;
}
double Goodguy::getDirection() {
    return renderDirection;
}
void Goodguy::setX(double x) {
    shipx=x;
}
void Goodguy::setY(double y) {
    shipy=y;
}
void Goodguy::setDirection(double theta) {
    renderDirection=theta;
}
void Goodguy::setStepSize(double x) {
    stepsize=x;
}
void Goodguy::setSpriteData(vector<vector<bool> > dat1, vector<vector<vector<double> > > dat2) {
    spriteshape=dat1;
    spriteskin=dat2;
}
void Goodguy::forwardmove(double d) {

    shipx+=cos(moveDirection)*stepsize*d/60.0;
    shipy+=sin(moveDirection)*stepsize*d/60.0;
    checkonscreen();

}
void Goodguy::checkonscreen() {
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
void Goodguy::modifyDirection(int d, bool b) {
    tomove = true;
    if(b) {
        switch(d) {
            case 1:
                onup=true;
                break;
            case 3:
                ondown=true;
                break;
            case 2:
                onleft=true;
                break;
            case 4:
                onright=true;
                break;
        }
    }
    else {
        switch(d) {
            case 1:
                onup=false;
                break;
            case 3:
                ondown=false;
                break;
            case 2:
                onleft=false;
                break;
            case 4:
                onright=false;
                break;
        }
    }
    int horz=0;
    if(onleft) {
        horz--;
    }
    if(onright) {
        horz++;
    }
    int vert=0;
    if(onup) {
        vert++;
    }
    if(ondown) {
        vert--;
    }
    if(horz==0 && vert==0) {
        tomove=false;
    }
    else {
        moveDirection=atan2(vert,horz);
    }
    if(tomove){
        cout << "Goodguy: Not moving" << endl;
    } else{
        cout<<"Goodguy direction: " << (moveDirection/M_PI) << endl;
    }
}
