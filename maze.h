enum maze_type {
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

char **maze_generator(size_t height, size_t width, maze_type type);

