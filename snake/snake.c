/*John Henry
When porting this game to other platforms, this code does not need to be modified.
*/
#include "data.h"
#include "LIB.h"
struct point MOVE_DIR(struct point p, enum dir dir){
	switch(dir){
		case RIGHT:
			p.x+=1;
		break;
		case DOWN:
			p.y+=1;
		break;
		case LEFT:
			p.x-=1;
		break;
        default:
			p.y-=1;
		break;
	}
	#define WRAP(x) x = (x<0)?GRID_SIZE+x:x,x%=GRID_SIZE
	WRAP(p.x);
	WRAP(p.y);
	return p;
}
void place_food(struct tile playfield[][GRID_SIZE]){
    SetFoodCol();
    unsigned x,y;
	do{
		x=Random(GRID_SIZE);
		y=Random(GRID_SIZE);
	}while(playfield[x][y].state!=EMPTY);
	playfield[x][y].state=FOOD;
}
#define START_DIR RIGHT
#define BODY_LEN 5
#define HEIGHT (GRID_SIZE/2)
struct tile grid[GRID_SIZE][GRID_SIZE];
struct point head;
struct point tail;
enum dir player_dir;
void InitGame(void){
    struct tile*arr = (struct tile*)grid;
    for(int i =0; i<GRID_SIZE*GRID_SIZE; i++){
        arr[i].state=EMPTY;
    }
    head = (struct point){BODY_LEN,HEIGHT};
    tail = (struct point){0,HEIGHT};
    player_dir = START_DIR;
    for(int i=tail.x;i<head.x;i++){
        Frame(grid,head);
        grid[i][HEIGHT].state=BODY;
        grid[i][HEIGHT].dir=START_DIR;
    }

}
void removeBlock(void){
    grid[tail.x][tail.y].state=EMPTY;
    tail=MOVE_DIR(tail,grid[tail.x][tail.y].dir);
}
void game(){
    SetBGCol(0);
    InitGame();
    unsigned count = 0;
    unsigned iter = 0;
    for(;;){
        count++;
        if(count > 10){
            SetBGCol(200*iter);
            iter++;
            count=0;
        }
        Frame(grid,head);
        if(KeyWasPressed())
            break;
    }
    SetBGCol(255);
	place_food(grid);
    for(;;){
        Frame(grid,head);
        {
            enum dir old_dir = player_dir;
            player_dir = GetDirection(player_dir);
            struct point np = MOVE_DIR(head,player_dir);
            if(grid[np.x][np.y].state==BODY){
                player_dir = old_dir;
            }
        }
		grid[head.x][head.y].state=BODY;
		grid[head.x][head.y].dir=player_dir;
		head=MOVE_DIR(head,player_dir);
		if(grid[head.x][head.y].state==FOOD){
			place_food(grid);
            grid[head.x][head.y].state=EMPTY;
        }else{
            removeBlock();
        }
        if(grid[head.x][head.y].state!=BODY)
            goto GAME_OVER;
	}
GAME_OVER:
    SetBGCol(0);
    do{
        Frame(grid,head);
        removeBlock();
    }while(grid[tail.x][tail.y].state!=EMPTY);
    return;
}

int main(){
    Init();
    for(;;){
        game();
    }
}
