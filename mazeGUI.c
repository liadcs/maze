#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct Player{
    int x;
    int y;
} player;

void print_maze(char* maze, int width, int height) {
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            switch (maze[y * width + x]) {
            case 0:             // free
                printf("   ");
                break;

            case 1:             // wall
                printf("|||");
                break;

            case 2:             // player
                printf(" X ");
                break;
            }
        }
        printf("\n");
    }
}

void clearScreen()
{
    system("cls");
}

void move_player(char* maze, int width, int height, player*player1, char next_move) {
    switch (next_move) {
    case 'w':
    case 'W':
        if (player1->y - 1 >= 0) {
            if (maze[(player1->y - 1) * height + player1->x] == 0) {
                
                maze[player1->y * height + player1->x] = 0;
                player1->y -= 1;
                maze[player1->y * height + player1->x] = 2;
            }
        }
        break;
    case 'a':
    case 'A':
        if (player1->x - 1 >= 0) {
            if (maze[(player1->y) * height + player1->x - 1] == 0) {

                maze[player1->y * height + player1->x] = 0;
                player1->x -= 1;
                maze[player1->y * height + player1->x] = 2;
            }
        }
        break;
    case 's':
    case 'S':
        if (player1->y + 1 < height) {
            if (maze[(player1->y + 1) * height + player1->x] == 0) {

                maze[player1->y * height + player1->x] = 0;
                player1->y += 1;
                maze[player1->y * height + player1->x] = 2;
            }
        }
        break;
    case 'd':
    case 'D':
        if (player1->x + 1 < width) {
            if (maze[(player1->y) * height + player1->x + 1] == 0) {

                maze[player1->y * height + player1->x] = 0;
                player1->x += 1;
                maze[player1->y * height + player1->x] = 2;
            }
        }
        break;
    default:
        printf("\nWrong input, please enter (W,A,S,D)\n");
        break;
    }
}


void CarveMaze(char* maze, int width, int height, int x, int y) {

    int x1, y1;
    int x2, y2;
    int dx, dy;
    int dir, count;

    dir = rand() % 4;
    count = 0;
    while (count < 4) {
        dx = 0; dy = 0;
        switch (dir) {
        case 0:  dx = 1;  break;
        case 1:  dy = 1;  break;
        case 2:  dx = -1; break;
        default: dy = -1; break;
        }
        x1 = x + dx;
        y1 = y + dy;
        x2 = x1 + dx;
        y2 = y1 + dy;
        if (x2 > 0 && x2 < width && y2 > 0 && y2 < height
            && maze[y1 * width + x1] == 1 && maze[y2 * width + x2] == 1) {
            maze[y1 * width + x1] = 0;
            maze[y2 * width + x2] = 0;
            x = x2; y = y2;
            dir = rand() % 4;
            count = 0;
        }
        else {
            dir = (dir + 1) % 4;
            count += 1;
        }
    }

}

void GenerateMaze(char* maze, int width, int height) {

    int x, y;

    /* Initialize the maze. */
    for (x = 0; x < width * height; x++) {
        maze[x] = 1;
    }

    maze[width + 1] = 0;

    /* Seed the random number generator. */
    srand(time(0));

    /* Carve the maze. */
    for (y = 1; y < height; y += 2) {
        for (x = 1; x < width; x += 2) {
            CarveMaze(maze, width, height, x, y);
        }
    }

    /* Set up the entry and exit. */
    maze[1] = 0;                                    // top left corner.
    maze[(height - 1) * width + (width - 2)] = 0;   // bottom right corner.

}

int main(int argc, char* argv[]) {

    int width, height;
    char* maze;
    player player1;
    char next_move;

    printf("Hello! Welcome to the best maze game ever.\n");

    printf("Enter maze hight:\n");
    scanf_s("%d", &height);
    
    printf("Enter maze width:\n");
    scanf_s("%d", &width);

    height = height * 2 + 1;    // double the size for better look
    width = width * 2 + 1;      // double the size for better look

    maze = (char*)malloc(width * height * sizeof(char));

    if (maze == NULL) {
        printf("error: not enough memory\n");
        exit(EXIT_FAILURE);
    }

    GenerateMaze(maze, width, height);

    
    player1.x = 1;
    player1.y = 0;
    maze[player1.y * height + player1.x] = 2;

    print_maze(maze, width, height);

    while (1) {
        printf("Enter your next move (W,A,S,D)");
        scanf_s(" %c", &next_move);
        move_player(maze, width, height, &player1,next_move);
        clearScreen();
        print_maze(maze, width, height);

    }

    print_maze(maze, width, height);

    /* Clean up. */
    free(maze);
    exit(EXIT_SUCCESS);

}
