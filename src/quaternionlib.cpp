// spacetechdemo.lib
#include "badguy.h"
#include "bullet.h"
#include <cstdlib>
#include <vector>
using namespace std;
vector<vector<bool> > createSpaceship() {
    vector<vector<bool> > interiorpixels;
    vector<int> greenwidth={0,2,2,3,3,4,5,5,5,5,3,0};
    for(int row=0;row<12;row++) {
        vector<bool> temp={false,false,false,false,false,false};
        for(int col=12-greenwidth[row];col<12;col++) {
            if(rand()%2==0) {
                temp[col]=true;// random bit
            }
        }
        if(row<10 && row>1) {
            temp[5]=false;
        }
        interiorpixels.push_back(temp);
    }
    vector<vector<bool> > blackpixels;
    for(int k=0;k<12;k++) {
        vector<bool> temp={false,false,false,false,false,false};
        blackpixels.push_back(temp);
    }
    for(int k=0;k<12;k++) {
        for(int k1=0;k1<6;k1++) {
            if(interiorpixels[k][k1]) {
                if(k>0) {
                    if(!interiorpixels[k-1][k1]) {
                        blackpixels[k-1][k1]=true;
                    }
                }
                if(k<11) {
                    if(!interiorpixels[k+1][k1]) {
                        blackpixels[k+1][k1]=true;
                    }
                }
                if(k1>0) {
                    if(!interiorpixels[k][k1-1]) {
                        blackpixels[k][k1-1]=true;
                    }
                }
                if(k1<5) {
                    if(!interiorpixels[k][k1+1]) {
                        blackpixels[k][k1+1]=true;
                    }
                }
            }
        }
        if(k<10 && k>1) {
            blackpixels[k][11]=true;
        }
    }
    vector<vector<bool> > toret=blackpixels;
    for(int k=0;k<12;k++) {
        for(int k1=0;k<6;k++) {
            toret[k].push_back(blackpixels[k][5-k1]);
        }
    }
    return toret;
}
