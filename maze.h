typedef enum {
    ONE_PLAYER,
    TOW_PLAYERS
}game_type;

typedef enum {
    DFS,
    NONE
} maze_generator_type;

typedef enum {
    SPACE = 0,
    WALL = 1,
    PLAYER_1 = 2,
    PALYER_2 = 3,
    GOOL = 4,
}maze_display;

typedef enum {
    RIGHT = 'R',
    LEFT = 'L',
    UP = 'U',
    CLUE = 'C',
    SOLUTION = 'S',
    EXIT = 'E'
}move_type;

/*
* generate maze by type
*/
char *maze_generator(size_t height, size_t width, game_type game_type, maze_generator_type generator_type);

/*
* solver the maze by (x,y) and type to solve
*/
char *solver(char *maze, size_t height, size_t width, size_t pos_x, size_t pos_y, size_t *result_size);

/*
* print maze
*/
void print_map(char **maze, size_t height, size_t width);