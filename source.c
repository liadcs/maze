#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

#define ACCESS_SLOT(maze , row , col, _width)  (*(char*)((char*)(maze) + col + row * _width))

void print_maze(char* maze, size_t height, size_t width) {
    printf("\n");
    for (size_t iRow = 0; iRow < height; iRow++) {
        for (size_t iCol = 0; iCol < width; iCol++) {
            printf("%hhx ", ACCESS_SLOT(maze, iRow, iCol, width));
        }
        printf("\n");
    }
}

void print_path(char* maze, size_t height, size_t width) {
    printf("\n");
    for (size_t iRow = 0; iRow < height; iRow++) {
        for (size_t iCol = 0; iCol < width; iCol++) {
            printf("%c ", ACCESS_SLOT(maze, iRow, iCol, width));
        }
        printf("\n");
    }
}

// BFS recursive
char BFS_recursive_solver_aux(char* maze, char* was_here, char* correct_path, size_t height, size_t width, size_t pos_x, size_t pos_y) {
    if (ACCESS_SLOT(maze, pos_x, pos_y, width) == TARGET) {
        ACCESS_SLOT(correct_path, pos_x, pos_y, width) = SOLUTION;
        return 1;
    }
    if (ACCESS_SLOT(was_here, pos_x, pos_y, width) == 1 || ACCESS_SLOT(maze, pos_x, pos_y, width) == 1) {
        return 0;
    }
    ACCESS_SLOT(was_here, pos_x, pos_y, width) = 1;

    if (pos_x != 0) {
        if (BFS_recursive_solver_aux(maze, was_here, correct_path, height, width, pos_x - 1, pos_y) != 0) {
            ACCESS_SLOT(correct_path, pos_x, pos_y, width) = UP;
            return UP;
        }
    }

    if (pos_x != height - 1) {
        if (BFS_recursive_solver_aux(maze, was_here, correct_path, height, width, pos_x + 1, pos_y) != 0) {
            ACCESS_SLOT(correct_path, pos_x, pos_y, width) = DOWN;
            return DOWN;
        }
    }

    if (pos_y != 0) {
        if (BFS_recursive_solver_aux(maze, was_here, correct_path, height, width, pos_x, pos_y - 1) != 0) {
            ACCESS_SLOT(correct_path, pos_x, pos_y, width) = LEFT;
            return LEFT;
        }
    }

    if (pos_y != width - 1) {
        if (BFS_recursive_solver_aux(maze, was_here, correct_path, height, width, pos_x, pos_y + 1) != 0) {
            ACCESS_SLOT(correct_path, pos_x, pos_y, width) = RIGHT;
            return RIGHT;
        }
    }
    return 0;
}

char* BFS_recursive_solver(char* maze, size_t height, size_t width, size_t pos_x, size_t pos_y) {
    char* was_here = malloc(height * width * sizeof(char));
    if (was_here == NULL) {
        return NULL;
    }

    char* correct_path = malloc(height * width * sizeof(char));
    if (correct_path == NULL) {
        free(was_here);
        return NULL;
    }

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            ACCESS_SLOT(was_here, row, col, width) = 0;
            ACCESS_SLOT(correct_path, row, col, width) = '0';
        }
    }
    BFS_recursive_solver_aux(maze, was_here, correct_path, height, width, pos_x, pos_y);
    free(was_here);
    return correct_path;
}


char* find_len(char* solution_maze, size_t width, size_t pos_x, size_t pos_y, size_t cur_int, size_t* len) {
    char* solution_array = NULL;
    switch (ACCESS_SLOT(solution_maze, pos_x, pos_y, width)) {
    case UP:
        solution_array = find_len(solution_maze, width, pos_x - 1, pos_y, cur_int + 1, len);
        break;
    case DOWN:
        solution_array = find_len(solution_maze, width, pos_x + 1, pos_y, cur_int + 1, len);
        break;
    case RIGHT:
        solution_array = find_len(solution_maze, width, pos_x, pos_y + 1, cur_int + 1, len);
        break;
    case LEFT:
        solution_array = find_len(solution_maze, width, pos_x, pos_y - 1, cur_int + 1, len);
        break;
    default:
        solution_array = malloc(sizeof(char) * cur_int);
        if (solution_array == NULL) {
            return NULL;
        }
        *len = cur_int + 1;
        solution_array[cur_int] = SOLUTION;
        return solution_array;
    }
    solution_array[cur_int] = ACCESS_SLOT(solution_maze, pos_x, pos_y, width);
    return solution_array;
}


char* solver(char* maze, size_t height, size_t width, size_t pos_x, size_t pos_y, size_t* result_size) {

    /*
    
        char demo_maze[5][7] = {
                                0,1,1,1,0,1,1,
                                0,0,1,0,0,0,0,
                                1,0,1,1,0,1,0,
                                1,0,1,1,0,1,0,
                                1,0,0,0,0,1,4
                                };
    
    */


    char *solution_maze = BFS_recursive_solver(maze, height, width, pos_x, pos_y);
    //print_path(solution_maze, height, width);
    char* solution_array = find_len(solution_maze, width, pos_x, pos_y, 0, result_size);
    free(solution_maze);
    return solution_array;
}
