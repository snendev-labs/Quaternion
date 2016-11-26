#include "leveldesigner.h"
#include <GL/gl.h>
#include <vector>
#include <random>
#include <ctime>
#include "stdlib.h"
#include "math.h"
#include "badguy.h"
#include "bullet.h"
#include "goodguy.h"
#include "shield.h"
#include <iostream>
using namespace std;

// RANDOM ENGINE
random_device r;
default_random_engine e1(r());
uniform_int_distribution<int> uniform_dist(0,100);
LevelDesigner::LevelDesigner() {}
void LevelDesigner::begin() {
    stageNum=0;
    onResetStage=true;
    currenttime=0;
    lasttime=0;
    goodguy=new Goodguy();
    shield=new Shield();
    shieldUp=0;
    goodguybullets = new vector<Bullet *>;
    badguybullets = new vector<Bullet *>;
    equippedBullet=0;
    goodguy->setX(.5);
    goodguy->setY(.5);
    vector<vector<bool> > shipdesign=createSpaceship();
    vector<vector<vector<double>>> shipskin=monoColorizeShipDesign(shipdesign);
    shipdesign=addEdgesToDesign(shipdesign);
    goodguy->setSpriteData(shipdesign,shipskin);
    paused=0;
    readyFire=0;
    autoFire=0;
    goodguydirection=0;
    goodguyFireRate=4.0;
    timeSinceLastGoodguyFire=0.0;
}
void LevelDesigner::notes() {
    if(checkstagedone()) {
        onResetStage=true;
        onResetFlee=false;
        stageNum++;
    }
}
void LevelDesigner::step() {
    currenttime=clock();
    deltatime=double(currenttime-lasttime)/CLOCKS_PER_SEC;
    lasttime=currenttime;
    if(!paused){
        if(onResetStage) {
            if(onResetFlee) {
                bool offscreenyet=true;
                for(int k=0;k<flocks.size() && offscreenyet;k++) {
                    for(int k1=0;k1<flocks[k].size() && offscreenyet;k1++) {
                        double fx=flocks[k][k1]->x();
                        double fy=flocks[k][k1]->y();
                        if(fx<1.0 && fx>0.0 && fy<1.0 && fy>0.0) {
                            offscreenyet=false;
                        }
                    }
                }
                for(int k=0;k<singlebadguys.size();k++) {
                    double fx=singlebadguys[k]->x();
                    double fy=singlebadguys[k]->y();
                    if(fx<1.0 && fx>0.0 && fy<1.0 && fy>0.0) {
                        offscreenyet=false;
                    }
                }
                if(offscreenyet) {
                    onResetFlee=false;
                }
                else {
                    for(int k=0;k<flocks.size();k++) {
                        for(int k1=0;k1<flocks[k].size();k1++) {
                            flocks[k][k1]->flee(deltatime);
                        }
                    }
                    for(int k=0;k<singlebadguys.size();k++) {
                        singlebadguys[k]->flee(deltatime);
                    }
                }
            }
            else {
                for(int k=0;k<flocks.size();k++) {
                    for(int k1=0;k1<flocks[k].size();k1++) {
                        delete flocks[k][k1];
                    }
                }
                for(int k=0;k<singlebadguys.size();k++) {
                    delete singlebadguys[k];
                }
                flocks.clear();
                singlebadguys.clear();
                vector<vector<bool> > shipdesign=createSpaceship();
                vector<vector<vector<double> > > shipskin=monoColorizeShipDesign(shipdesign);
                shipdesign=addEdgesToDesign(shipdesign);
                int totalbgs=0;
                int gnfas=getNumFlocksAtStage(stageNum);
                for(int k=0;k<gnfas;k++) {
                    vector<vector<bool> > shipdesign1=createSpaceship();
                    vector<vector<vector<double> > > shipskin1=monoColorizeShipDesign(shipdesign1);
                    shipdesign=addEdgesToDesign(shipdesign1);
                    int gfsas=getFlockSizeAtStage(stageNum);
                    totalbgs+=gfsas;
                    vector<Badguy *> temp;
                    for(int k1=0;k1<gfsas;k1++) {
                        temp.push_back(new Badguy());
                        temp[k1]->setSpriteData(shipdesign1,shipskin1);
                        temp[k1]->setX((double) uniform_dist(e1)/100.0);
                        temp[k1]->setY(.5+(double) uniform_dist(e1)/200.0);
                        temp[k1]->setDirection(M_PI*1.5+((double) uniform_dist(e1)-50)/50.0*.1);
                    }
                    flocks.push_back(temp);
                }
                int gnsbgas=getNumSingleBadGuysAtStage(stageNum);
                for(int k=0;k<gnsbgas;k++) {
                    singlebadguys.push_back(new Badguy());
                    singlebadguys[k]->setSpriteData(shipdesign,shipskin);
                    singlebadguys[k]->setX((double) uniform_dist(e1)/100.0);
                    singlebadguys[k]->setY(1.0);
                }
                onResetStage=false;
            }
        }
        else {
            for(int k=0;k<flocks.size();k++) {
                for(int k1=0;k1<flocks[k].size();k1++) {
                    flocks[k][k1]->flockmove(flocks[k],deltatime);
                }
            }
            for(int k=0;k<singlebadguys.size();k++) {
                double direction=singlebadguys[k]->getDirection();
                direction+=.01*M_PI*((double) uniform_dist(e1)-50)/50.0;
                singlebadguys[k]->directionandmove(direction,deltatime);
            }
        }
        checkcollisions();
        // BADGUY BULLETS
        for(int k=0;k<badguybullets->size();k++) {
            (*badguybullets)[k]->forwardmove(deltatime);
            (*badguybullets)[k]->health -= deltatime;
        }
        // GOODGUY BULLETS
        timeSinceLastGoodguyFire+=deltatime;
        if(timeSinceLastGoodguyFire>1.0/goodguyFireRate && (readyFire == 1 || autoFire == 1)) {
            Bullet * temp;
            if(equippedBullet == 4){ //shotgun
                temp=new Bullet(goodguy->x(),goodguy->y(),goodguy->getDirection(), 0.3, equippedBullet);
                goodguybullets->push_back(temp);
                temp=new Bullet(goodguy->x(),goodguy->y(),goodguy->getDirection()-0.5, 0.3, equippedBullet);
                goodguybullets->push_back(temp);
                temp=new Bullet(goodguy->x(),goodguy->y(),goodguy->getDirection()+0.5, 0.3, equippedBullet);
                goodguybullets->push_back(temp);
            } else if(equippedBullet == 5 || equippedBullet == 6){ //circle
                temp=new Bullet(goodguy->x()+0.1,goodguy->y()+0.1,goodguy->getDirection(),0.5, equippedBullet);
                goodguybullets->push_back(temp);
                temp=new Bullet(goodguy->x()-0.1,goodguy->y()+0.1,goodguy->getDirection(),0.5, equippedBullet);
                goodguybullets->push_back(temp);
                temp=new Bullet(goodguy->x()+0.1,goodguy->y()-0.1,goodguy->getDirection(),0.5, equippedBullet);
                goodguybullets->push_back(temp);
                temp=new Bullet(goodguy->x()-0.1,goodguy->y()-0.1,goodguy->getDirection(),0.5, equippedBullet);
                goodguybullets->push_back(temp);
            } else {
                temp=new Bullet(goodguy->x(),goodguy->y(),goodguy->getDirection(), 5.0, equippedBullet);
                goodguybullets->push_back(temp);
            }
            timeSinceLastGoodguyFire=0.0;
        }
        for(int k=0;k<goodguybullets->size();k++) {
            if((*goodguybullets)[k]->type == 0  || (*goodguybullets)[k]->type == 4){
                (*goodguybullets)[k]->forwardmove(deltatime);
            } else if((*goodguybullets)[k]->type == 1){
                (*goodguybullets)[k]->swirlmove(deltatime);
            } else if((*goodguybullets)[k]->type == 2){
                (*goodguybullets)[k]->swirlreversemove(deltatime);
            } else if((*goodguybullets)[k]->type == 3){
                (*goodguybullets)[k]->wandermove(deltatime);
            } else if((*goodguybullets)[k]->type == 5){
                (*goodguybullets)[k]->circlemove(deltatime, goodguy->x(), goodguy->y(), goodguy->stepsize, goodguy->moveDirection);
            } else if((*goodguybullets)[k]->type == 6){
                (*goodguybullets)[k]->circlelazymove(deltatime, goodguy->x(), goodguy->y());
            }
            (*goodguybullets)[k]->health -= deltatime;
        }
        //bullet death
        vector<Bullet *> * temp = new vector<Bullet *>;
        for(int k=0;k<goodguybullets->size();k++) {
            if((*goodguybullets)[k]->health > 0){
                temp->insert(temp->begin()+temp->size(), (*goodguybullets)[k]);
            }
        }
        vector<Bullet *> *temp2 = goodguybullets;
        goodguybullets = temp;
        delete temp2;
        // GOODGUY MOVE
        if(goodguy->tomove){
            goodguy->forwardmove(deltatime);
            if(shieldUp == 1){
                shield->duration -= deltatime;
                if(shield->duration < 0){
                    shieldUp = 0;
                } else {
                    shield->forwardmove(goodguy->moveDirection, deltatime, goodguy->stepsize);
                }
            }
        }
    }
}
bool LevelDesigner::checkstagedone() {
    if(!onResetStage) {
        int numbgs=0;
        for(int k=0;k<flocks.size();k++) {
            numbgs+=flocks[k].size();
        }
        numbgs+=singlebadguys.size();
        if(numbgs<minStageNumBadGuys) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
vector<vector<bool> > LevelDesigner::createSpaceship() {
    vector<vector<bool> > toret;
    vector<vector<bool> > interiorpixels;
    vector<int> greenwidth={0,2,2,3,3,4,5,5,5,5,3,0};
    for(int row=0;row<12;row++) {
        vector<bool> temp={false,false,false,false,false,false};
        for(int col=6-greenwidth[row];col<6;col++) {
            if(uniform_dist(e1)<75) {
                //cout<<"Made true"<<endl;
                temp[col]=true;// random bit
            }
        }
        if(row<10 && row>3) {
            temp[5]=false;
        }
        interiorpixels.push_back(temp);
    }
    toret=interiorpixels;

    for(int k=0;k<12;k++) {
        for(int k1=0;k1<6;k1++) {
            toret[k].push_back(interiorpixels[k][5-k1]);
        }
    }
    /*
    for(int k=0;k<toret.size();k++) {
        //cout<<"Line: ";
        for(int k1=0;k1<toret[k].size();k1++) {
            if(toret[k][k1]) {
                //cout<<"1 ";
            }
            else{
                cout<<"0 ";
            }
        }
        cout<<endl;
    }
    */
    return toret;
}
vector<vector<bool> > LevelDesigner::addEdgesToDesign(vector<vector<bool> > design) {
    vector<vector<bool> > toret=design;
    for(int k=0;k<toret.size();k++) {
        for(int k1=0;k1<toret[k].size();k1++) {
            toret[k][k1]=false;
        }
    }
    for(int k=0;k<toret.size();k++) {
        for(int k1=0;k1<toret[k].size();k1++) {
            //cout<<"Here"<<endl;
            if(!design[k][k1]) {
                if(k>0) {
                    if(design[k-1][k1]) {
                        toret[k][k1]=true;
                    }
                }
                if(k<design.size()-1) {
                    if(design[k+1][k1]) {
                        toret[k][k1]=true;
                    }
                }
                if(k1>0) {
                    if(design[k][k1-1]) {
                        toret[k][k1-1]=true;
                    }
                }
                if(k1<design.size()-1) {
                    if(design[k][k1+1]) {
                        toret[k][k1]=true;
                    }
                }
            }
        }
    }
    return toret;
}

vector<vector<vector<double>>> LevelDesigner::monoColorizeShipDesign(vector<vector<bool> > design) {
    vector<double> base={(double) uniform_dist(e1),(double) uniform_dist(e1),(double) uniform_dist(e1)};
    vector<vector<vector<double> > > toret;
    int numOnPix=0;
    for(int k=0;k<design.size();k++) {
        for(int k1=0;k1<design[k].size();k1++) {
            if(design[k][k1]) {
                numOnPix++;
            }
        }
    }
    int center_x=0;
    int center_y=0;
    double grabPix=(double) uniform_dist(e1)/100.0*numOnPix;
    numOnPix=0;
    bool foundcenter=false;
    for(int k=0;k<design.size() && !foundcenter;k++) {
        for(int k1=0;k1<design[k].size() && !foundcenter;k1++) {
            if(design[k][k1]) {
                numOnPix++;
                if(numOnPix>grabPix) {
                    foundcenter=true;
                }
                else {
                    center_y=k;
                    center_x=k1;
                }
            }
        }
    }
    for(int k=0;k<design.size();k++) {
        vector<vector<double> > temp;
        for(int k1=0;k1<design[k].size();k1++) {
            vector<double> temp1;
            if(design[k][k1]) {
                temp1={base[0]/(1.0+abs(k-center_y)+abs(k1-center_x)),
                    base[1]/(1.0+abs(k-center_y)+abs(k1-center_x)),
                    base[2]/(1.0+abs(k-center_y)+abs(k1-center_x))};
            }
            else {
                temp1={0,0,0};
            }
            temp.push_back(temp1);
        }
        toret.push_back(temp);
    }
    for(int k=0;k<toret.size();k++) {
        for(int k1=0;k1<toret[k].size();k1++) {
            for(int k2=0;k2<toret[k][k1].size();k2++) {
                toret[k][k1][k2]=0.10+0.9*toret[k][k1][k2]/100.0;
            }
        }
    }
    return toret;
}
void LevelDesigner::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,0.0,0.0);
    for(int k=0;k<flocks.size();k++) {
        for(int k1=0;k1<flocks[k].size();k1++) {
            flocks[k][k1]->render();
        }
    }
    for(int k=0;k<singlebadguys.size();k++) {
        singlebadguys[k]->render();
    }
    for(int k=0;k<badguybullets->size();k++) {
        (*badguybullets)[k]->shittyrender(0.01);
    }
    for(int k=0;k<goodguybullets->size();k++) {
        (*goodguybullets)[k]->shittyrender(0.01);
    }
    goodguy->render();
    if(shieldUp == 1){
        shield->supershittyrender();
    }
}
void LevelDesigner::checkcollisions() {
    // GOODGUY BULLETS
    bool delmember=false;
    for(int k=0;k<flocks.size();k++) {
        for(int k1=0;k1<flocks[k].size();k1++) {
            delmember=false;
            for(int k2=0;k2<goodguybullets->size() && !delmember;k2++) {
                double distance=(flocks[k][k1]->x()-(*goodguybullets)[k2]->x())*(flocks[k][k1]->x()-(*goodguybullets)[k2]->x())+
                    (flocks[k][k1]->y()-(*goodguybullets)[k2]->y())*(flocks[k][k1]->y()-(*goodguybullets)[k2]->y());
                if(distance<(flocks[k][k1]->getHitRadius())*(flocks[k][k1]->getHitRadius())) {
                    delete (*goodguybullets)[k2];
                    goodguybullets->erase(goodguybullets->begin()+k2);
                    k2--;
                    delete flocks[k][k1];
                    flocks[k].erase(flocks[k].begin()+k1);
                    k1--;
                    delmember=true;
                }
            }
            if(flocks[k].size()==0) {
                flocks.erase(flocks.begin()+k);
                k--;
            }
        }
    }
    for(int k=0;k<goodguybullets->size();k++) {
        bool tokill=((*goodguybullets)[k]->x()<0.0)||((*goodguybullets)[k]->x()>1.0)||((*goodguybullets)[k]->y()<0.0)||((*goodguybullets)[k]->y()>1.0);
        if(tokill) {
            delete (*goodguybullets)[k];
            goodguybullets->erase(goodguybullets->begin()+k);
            k--;
        }
    }
}
void LevelDesigner::resetStage() {
    onResetStage=true;
    onResetFlee=true;
}
void LevelDesigner::setDirection(int d, bool b) {
    cout<<"Direction: "<<d<<endl;
    goodguy->modifyDirection(d,b);
}
int LevelDesigner::getNumFlocksAtStage(int x) {
    return 2;
}// TODO
int LevelDesigner::getFlockSizeAtStage(int x) {
    return 20;
}// TODO
int LevelDesigner::getNumSingleBadGuysAtStage(int x) {
    return 10;
}// TODO

void LevelDesigner::changeBulletNext(){
    equippedBullet = (equippedBullet+1)%7;
}

void LevelDesigner::changeBulletLast(){
    if(equippedBullet == 0){
        equippedBullet = 6;
    } else{
        equippedBullet = (equippedBullet-1);
    }
}

void LevelDesigner::summonShield(){
    double dist = 0.04;
    double dur = 0.6;
    double w = 0.06;
    double h = 0.01;
    shieldUp = 1;
    shield = new Shield(goodguy->x(), goodguy->y()+dist, w, h, dur);
}







