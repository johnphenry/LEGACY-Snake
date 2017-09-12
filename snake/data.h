#define GRID_SIZE 20
enum state{
	EMPTY,
	BODY,
	FOOD,
};
enum dir{
	RIGHT,
	DOWN,
	LEFT,
	UP,
    DIR_NONE,
};
struct tile{
	enum dir dir;
	enum state state;
};
struct point{
	int x,y;
};
