#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "maze.h"


#define BLOCK_SIZE 4
#define GAP 2

#define SPACE_DISPLAY "|||"
#define WALL_DISPLAY "   "
#define PLAYER_1_DISPLY " X "
#define PLAYER_2_DISPLY " Y "
#define BOTH_PLYER_DISPLY " 2 "
#define TARGET_DISPLY " O "

/*
* clear GUI screen
*/
void clearScreen() {
    system("cls");
}

void print_maze_map(char *maze, int width, int height) {
    clearScreen();
    int x, y;
    char *disply = NULL;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            switch (maze[y * width + x]) {
                case SPACE: disply = SPACE_DISPLAY;  break;
                case WALL: disply = WALL_DISPLAY;  break;
                case PLAYER_1: disply = PLAYER_1_DISPLY;  break;
                case PALYER_2: disply = PLAYER_2_DISPLY;  break;
                case TWO_PLAYER_SAME_CELL: disply = PLAYER_2_DISPLY;  break;
                case TAEGET: disply = TARGET_DISPLY;  break;
                default:
                    disply = NULL;
            }
            printf("%s", disply);
        }
        printf("\n");
    }
}

/*  Carve the maze starting at x, y. */
void carve_maze(char *maze, int width, int height, int x, int y) {

    int x1, y1;
    int x2, y2;
    int dx, dy;
    int dir, count;

    dir = rand() % BLOCK_SIZE;
    count = 0;
    while (count < BLOCK_SIZE) {
        dx = 0; dy = 0;
        switch (dir) {
            case RIGHT:  dx = 1;  break;
            case UP:  dy = 1;  break;
            case LEFT:  dx = -1; break;
            default: dy = -1; break; // DOWN
        }
        x1 = x + dx;
        y1 = y + dy;
        x2 = x1 + dx;
        y2 = y1 + dy;
        if (x2 > 0 && x2 < width && y2 > 0 && y2 < height && maze[y1 * width + x1] == WALL && maze[y2 * width + x2] == WALL) {
            maze[y1 * width + x1] = SPACE;
            maze[y2 * width + x2] = SPACE;
            x = x2; y = y2;
            dir = rand() % BLOCK_SIZE;
            count = 0;
        } else {
            dir = (dir + 1) % BLOCK_SIZE;
            count++;
        }
    }

}

/*
* simple maze generator
*/
void generator_simple(char *maze, int height, int width) {

    int x, y;

    /* Seed the random number generator. */
    srand((unsigned int)time(NULL));

    memset(maze, WALL, width * height);
    maze[1 * width + 1] = SPACE;

    /* Carve the maze. */
    for (y = 1; y < height; y += 2) {
        for (x = 1; x < width; x += 2) {
            carve_maze(maze, width, height, x, y);
        }
    }

    /* Set up the entry and exit. */
    maze[1] = TWO_PLAYER_SAME_CELL;
    maze[1 * width + 1] = WALL;
    maze[(height - 1) * width + (width - 2)] = TAEGET;
}


char *maze_generator(int height, int width, void (*generator)(char *, int height, int width)) {

    char *maze = (char *)malloc(width * height * sizeof(char));

    if (!maze) {
        return NULL;
    }

    generator(maze, height, width);

    return maze;
}

/*
* check if given pos is type of
*/
bool check_if_cell_is(char *maze, int width, int pos_x, int pos_y, cell_type type) {
    return maze[pos_y * width + pos_x] == type;
}

/*
* move the player to pos
*/
bool move_player(char *maze, int height, int width, player *curent_player, char next_move) {
    maze[curent_player->y * width + curent_player->x] -= curent_player->player_type;
    bool res = true;
    switch (next_move) {
        case 'w':
        case 'W':
            if (curent_player->y - 1 >= 0) {
                if (!check_if_cell_is(maze, width, curent_player->x, curent_player->y - 1, WALL)) {
                    curent_player->y -= 1;
                }
            }
            break;
        case 'a':
        case 'A':
            if (curent_player->x - 1 >= 0) {
                if (!check_if_cell_is(maze, width, curent_player->x - 1, curent_player->y, WALL)) {
                    curent_player->x -= 1;
                }
            }
            break;
        case 's':
        case 'S':
            if (curent_player->y + 1 < height) {
                if (!check_if_cell_is(maze, width, curent_player->x, curent_player->y + 1, WALL)) {
                    curent_player->y += 1;
                }
            }
            break;
        case 'd':
        case 'D':
            if (curent_player->x + 1 < width) {
                if (!check_if_cell_is(maze, width, curent_player->x + 1, curent_player->y, WALL)) {
                    curent_player->x += 1;
                }
            }
            break;
        default:
            res = false;
            break;
    }
    maze[curent_player->y * height + curent_player->x] += curent_player->player_type;
    return res;
}

int main(int argc, char *argv[]) {

    int width, height;
    char *maze;
    player player1;
    char next_move;

    printf("Hello! Welcome to the best maze game ever.\n");

    while (true) {
        printf("Enter maze hight:\n");
        if (scanf("%d", &height) == 1) {
            break;
        }
    }

    while (true) {
        printf("Enter maze width:\n");
        if (scanf("%d", &width) == 1) {
            break;
        }
    }

    height = height * 2 + 1;    // double the size for better look
    width = width * 2 + 1;      // double the size for better look

    maze = maze_generator(width, height, generator_simple);

    if (!maze) {
        printf("error: not enough memory\n");
        exit(EXIT_FAILURE);
    }

    player1.x = 1;
    player1.y = 0;
    maze[player1.y * height + player1.x] = PLAYER_1;

    print_maze_map(maze, width, height);
    bool good_last_move;
    while (true) {
        printf("Enter your next move (W - UP ,A - LEFT ,S - DOWN, D - RIGHT, C - CLUE, R - SOLVE ): ");
        if (scanf("%c", &next_move) != 1) {
            continue;
        }
        good_last_move = move_player(maze, width, height, &player1, next_move);
        print_maze_map(maze, width, height);
        if (!good_last_move) {
            printf("Wrong input\n");
        }
    }

    print_maze_map(maze, width, height);

    /* Clean up. */
    free(maze);
    exit(EXIT_SUCCESS);
}
