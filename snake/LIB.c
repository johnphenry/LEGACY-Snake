/*
When porting this game to other platforms, this is the only code that needs to be modified if the platform is not supported by SDL2.
Note that headers for libraries such as SDL2 are not incuded in other headers, only here in this file.
This speeds up compilation times by a lot because headers are only included where they are needed.
The actual implementation of the functions in this file does not matter to any of the other files in the game.
This forces that only the dependent code can be used here, and nowhere else.
I consider even the usage of that standard library to be dependent code.
For instance, when using libGCCVB, a virtual boy compiler, the standard library actually has not been implemented for that platform!
*/
#include<stdlib.h>
#include<time.h>
#include<SDL2/SDL.h>
#include "data.h"
int w=640;
int h=480;
SDL_Window*win;
SDL_Renderer*ren;
int wasPressed;
static struct{
    unsigned char r,g,b;
}food_col;
unsigned char BGcol;
void SetBGCol(unsigned char col){
    BGcol = col;
}
int KeyWasPressed(void){
    return wasPressed;
}
void Init(){
	srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);
    win=SDL_CreateWindow("Snake",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
}
void Quit(){
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
	SDL_Quit();
    exit(0);
}
unsigned Random(unsigned range){
    return rand()%range;
}
void SetFoodCol(void){
    food_col.r=Random(128);
    food_col.g=Random(128);
    food_col.b=Random(128);
}

static enum dir newDir = DIR_NONE;
enum dir GetDirection(enum dir input){
    if((newDir+2)%4==input || newDir == DIR_NONE )
        return input;
    return newDir;
}
void Frame(struct tile grid[][GRID_SIZE], struct point head){
    unsigned startTime = SDL_GetTicks();
    int tilew = w/GRID_SIZE;
    int tileh = h/GRID_SIZE;
    for( int y=0;y<GRID_SIZE;++y)
        for(int x=0;x<GRID_SIZE;++x){
            switch(grid[x][y].state){
                case EMPTY:
                    SDL_SetRenderDrawColor(ren,BGcol,BGcol,BGcol,255);
                    break;
                case BODY:
                    SDL_SetRenderDrawColor(ren,0,0,255,255);
                    break;
                default:
                    SDL_SetRenderDrawColor(ren,food_col.r,food_col.g,food_col.b,255);
                    break;
            }
            unsigned char inverseBG = 255-BGcol;
            SDL_Rect r = {x*tilew,y*tileh, tilew, tileh };
            SDL_RenderFillRect(ren,&r);
            SDL_SetRenderDrawColor(ren,inverseBG,inverseBG,inverseBG,255);
            SDL_RenderDrawRect(ren,&r);
        }
        {
            SDL_Rect r = {head.x*tilew,head.y*tileh, tilew, tileh };
            SDL_SetRenderDrawColor(ren,0,255,0,255);
            SDL_RenderFillRect(ren,&r);
        }
    SDL_RenderPresent(ren);
    
    int delay;
    static const unsigned wait = 1000/10;
    wasPressed = 0;
    {
    unsigned time = SDL_GetTicks();
    delay = time - startTime;
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type==SDL_QUIT){
            Quit();
        }else if( e.type == SDL_KEYDOWN ) {
            wasPressed = 1;
            switch( e.key.keysym.sym ) {
                case SDLK_RIGHT:
                    newDir = RIGHT;
                    break;
                case SDLK_DOWN:
                    newDir = DOWN;
                    break;
                case SDLK_LEFT:
                    newDir = LEFT;
                    break;
                case SDLK_UP:
                    newDir = UP;
                    break;
            }
            
        }
    }
    }
    if(delay<wait){
        SDL_Delay(wait-delay);
    }
}
