enum maze_type {
    DFS,
    NONE
};

char **maze_generator(size_t height, size_t width, maze_type type);