enum maze_type {
    DFS,
    NONE
};

enum maze_desply {
    SPACE = 0,
    WALL = 1,
    PLAYER_1 = 2,
    PALYER_2 = 3
};
char **maze_generator(size_t height, size_t width, maze_type type);

