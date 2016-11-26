// spacetechdemo.cpp
#include "math.h"
#include <GL/gl.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <GL/glu.h>
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
//SDL SHIT
SDL_Window* displayWindow;

void initdisplay()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,1.0,0.0,1.0,-1.0,1.0);
}

void ev_handler(SDL_Event *event, int *gameover){
    switch((*event).type) {
        case SDL_KEYDOWN:
            cout << "Key down..." << (char) (*event).key.keysym.sym << endl;   
            switch((*event).key.keysym.sym) {
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
                case SDLK_r:
                    ld.resetStage();
                    break;
                case SDLK_w:
                    ld.setDirection(1,true);
                    break;
                case SDLK_a: 
                    ld.setDirection(2,true);
                    break;
                case SDLK_s:
                    ld.setDirection(3,true);
                    break;
                case SDLK_d:
                    ld.setDirection(4,true);
                    break;
                case SDLK_e:
                    ld.changeBulletNext();
                    break;
                case SDLK_q:
                    ld.changeBulletLast();
                    break;
                case SDLK_SPACE:
                    ld.readyFire = 1;
                    break;
                case SDLK_c:
                    ld.autoFire = !(ld.autoFire);
                    break;
                case SDLK_f:
                    ld.summonShield();
                    break;
                case SDLK_p:
                    ld.paused = ld.paused;
                    break;
                case SDLK_ESCAPE:
                    *gameover = 1;
                    break;
                default:
                    ld.setDirection(0,true);
                    break;
            }
            break;
       case SDL_KEYUP:
            cout << "Key up..." << (char) (*event).key.keysym.sym << endl;  
            switch((*event).key.keysym.sym) {
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
                case SDLK_w:
                    ld.setDirection(1,false);
                    break;
                case SDLK_a: 
                    ld.setDirection(2,false);
                    break;
                case SDLK_s:
                    ld.setDirection(3,false);
                    break;
                case SDLK_d:
                    ld.setDirection(4,false);
                    break;
                case SDLK_SPACE:
                    ld.readyFire = 0;
                    break;
                default:
                    ld.setDirection(0,false);
                    break;
            }
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    cout << "SDL_INIT_VIDEO" << endl;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "Nope" << endl;
        return 1;
    }

    cout << "ld.begin()..." << endl;
    ld.begin();
    cout << "Create SDL Window, OpenGL Context..." << endl;
    displayWindow = SDL_CreateWindow("Quaternion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 1024, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (displayWindow == NULL)    {
        std::cout << "Cannot create window with error " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(displayWindow);
    if (glContext == NULL)    {
        std::cout << "Cannot create OpenGL context with error " << SDL_GetError() << std::endl;
        return 1;
    }
    cout << "Init GL display and viewport..." << endl;
    initdisplay();

    //main loop
    cout << "[GL] Begin main loop..." << endl;
    ld.render();
    SDL_GL_SwapWindow(displayWindow);
    int gameover = 0;
    unsigned int i = 0;
    SDL_Event event;
    while (!gameover){
        cout << "------------" << i++ << "------------" << endl;
        while(SDL_PollEvent(&event)) {
            ev_handler(&event, &gameover);
        }
        ld.notes();
        ld.step();
        ld.render();
        // Update window with OpenGL rendering
        SDL_GL_SwapWindow(displayWindow);
    }

    SDL_DestroyWindow(displayWindow);
    SDL_Quit();

    return 0;

}









//
