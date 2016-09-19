// spacetechdemo.cpp
#include "math.h"
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
//#include <SDL.h>
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "badguy.h"
#include "bullet.h"
#include "leveldesigner.h"
#include "shield.h"
using namespace std;
// SPRITE HOLDERS
LevelDesigner ld;
// SDL SHIT
/*
SDL_Surface *screen;
SDL_Event event;
*/
// CONTROLER EVENT LISTENER
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
void letitsnow() {
    /*
    SDL_Event el;
    bool quit=true;
    while(!quit) {
        while(SDL_PollEvent(&el)) {
            cout<<"Hello"<<endl;
            if(el.type==SDL_KEYDOWN) {
                cout<<"Keydown..."<<endl;
                switch(el.key.keysym.sym) {
                    case SDLK_UP:
                        ld.setDirection(1,true);
                        break;
                    case SDLK_DOWN:
                        ld.setDirection(2,true);
                        break;
                    case SDLK_LEFT:
                        ld.setDirection(3,true);
                        break;
                    case SDLK_RIGHT:
                        ld.setDirection(4,true);
                        break;
                    default:
                        ld.setDirection(0,true);
                        break;
                }
            }
            if(el.type==SDL_KEYUP) {
                switch(el.key.keysym.sym) {
                    case SDLK_UP:
                        ld.setDirection(1,false);
                        break;
                    case SDLK_DOWN:
                        ld.setDirection(2,false);
                        break;
                    case SDLK_LEFT:
                        ld.setDirection(3,false);
                        break;
                    case SDLK_RIGHT:
                        ld.setDirection(4,false);
                        break;
                    default:
                        ld.setDirection(0,false);
                        break;
                }
            }
        }
    }
    */
    ld.notes();
    ld.step();
    // TO DELETE WHEN SDL2 fixed
    ld.setDirection(1,false);
    ld.setDirection(2,false);
    ld.setDirection(3,false);
    ld.setDirection(4,false);
    // END TO DELETE
}
void display(void) {
    ld.render();
}
void init(void) { // TODO
    // SDL
    //if(SDL_Init (SDL_INIT_VIDEO)<0) cout<<"asshole"<<endl;;
    //SDL_SetVideoMode (320, 200, 8, 0);
    // OpenGL
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
    ld.begin();
}
void keyboardControler(unsigned char key, int x, int y) {
    if(key=='r') {
        ld.resetStage();
    } else if(key=='w') {
        ld.setDirection(1,true);
    } else if(key=='a') {
        ld.setDirection(2,true);
    } else if(key=='s') {
        ld.setDirection(3,true);
    } else if(key=='d') {
        ld.setDirection(4,true);
    } else if(key=='e') {
        ld.changeBulletNext();
    } else if(key=='q') {
        ld.changeBulletLast();
    } else if(key==' ') {
        ld.readyFire = 1;
    } else if(key=='f') {
        ld.summonShield();
    } else if(key=='p') {
        ld.paused = !(ld.paused);
    } 
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1024,1024);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Quaternion");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(letitsnow);
    glutKeyboardFunc(keyboardControler);
    glutMainLoop();
    return 0;
}
