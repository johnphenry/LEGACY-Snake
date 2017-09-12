void Init();
void Quit();
unsigned Random(unsigned);
void Frame(struct tile grid[GRID_SIZE][GRID_SIZE], struct point);
enum dir GetDirection(enum dir);
int KeyWasPressed(void);
void SetBGCol(unsigned char);
void SetFoodCol(void);
