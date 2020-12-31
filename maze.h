enum game_type {
    ONE_PLAYER,
    TOW_PLAYERS
};

enum maze_generator_type {
    DFS,
    NONE
};

enum maze_display {
    SPACE = 0,
    WALL = 1,
    PLAYER_1 = 2,
    PALYER_2 = 3,
    GOOL = 4,
};

enum move_type {
    RIGHT = 'R',
    LEFT = 'L',
    UP = 'U',
    CLUE = 'C',
    SOLUTION = 'S',
    EXIT = 'E'
};

char **maze_generator(size_t height, size_t width, game_type game_type, maze_generator_type generator_type);

//solver(char **maze, move_type move)

void print_map(char **maze, size_t height, size_t width);