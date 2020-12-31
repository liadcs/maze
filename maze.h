typedef enum {
    ONE_PLAYER,
    TOW_PLAYERS
} game_type;



typedef enum {
    DFS,
    SIMPLE
} maze_generator_type;

typedef enum {
    SPACE = 0,
    WALL = 1,
    PLAYER_1 = 2,
    PALYER_2 = 3,
    TAEGET = 4,
    TWO_PLAYER_SAME_CELL = 5 // Need to be PLAYER_1 + PLAYER_2
} cell_type;

typedef enum {
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3,
    CLUE = 'C',
    SOLUTION = 'S',
    EXIT = 'E'
} move_type;

typedef struct player_pos_t {
    int x;
    int y;
    cell_type player_type;
} player;

/*
* generate maze by type
*/
char *maze_generator(int height, int width, void (*generator)(char *, int height, int width));

///*
//* solver the maze by (x,y) and type to solve
//*/
//char *solver(char *maze, size_t height, size_t width, size_t pos_x, size_t pos_y, size_t *result_size);

/*
* print maze
*/
void print_maze_map(char *maze, int height, int width);