#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define LINES 25
#define COLUMNS 80

int Paddle1Y, Paddle2Y, BallX, BallY;
int BallDirX = 1;
int BallDirY = 1;
int score_1 = 0;
int score_2 = 0;
char Input;

void view();

void initGame() {
    Paddle1Y = LINES / 2 - 1;
    Paddle2Y = LINES / 2 - 1;
    BallX = COLUMNS / 2 - 1;
    BallY = LINES / 2;
}

void view() {
    system("clear");

    if (score_1 < 10 && score_2 < 10) {
        printf("\n\nИгрок1:%d                                                                Игрок2:%d\n\n",
               score_1, score_2);
    } else if ((score_1 < 10 && score_2 > 9) || (score_1 > 9 && score_2 < 10)) {
        printf("\n\nИгрок1:%d                                                               Игрок2:%d\n\n",
               score_1, score_2);
    } else {
        printf("\n\nИгрок1:%d                                                              Игрок2:%d\n\n",
               score_1, score_2);
    }

    for (int x = 0; x < COLUMNS; x++) {
        printf("-");
    }
    printf("\n");
    for (int y = 0; y < LINES; y++) {
        for (int x = 0; x < COLUMNS + 1; x++) {
            if (x == BallX && y == BallY) {
                printf("O");
            } else if (x == 1 && y >= Paddle1Y && y < Paddle1Y + 3) {
                printf("|");
            } else if (x == COLUMNS - 2 && y >= Paddle2Y && y < Paddle2Y + 3) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    for (int x = 0; x < COLUMNS; x++) {
        printf("-");
    }
    printf("\n\n");
}
void moveBall() {
    BallX += BallDirX;
    BallY += BallDirY;

    if (BallY <= 0 || BallY >= LINES - 1) {
        BallDirY *= -1;
    }

    if (BallX == 1 && BallY >= Paddle1Y && BallY < Paddle1Y + 3) {
        BallDirX = 1;
    } else if (BallX == COLUMNS - 2 && BallY >= Paddle2Y && BallY < Paddle2Y + 3) {
        BallDirX = -1;
    }
    if (BallX <= 0) {
        BallX = COLUMNS / 2;
        BallY = LINES / 2;
    }
    if (BallX == 80) {
        score_1 += 1;
    }
    if (BallX == 0) {
        score_2 += 1;
    }
    if (score_1 == 21) {
        printf("Player 1 win");
        Input = 'q';
    } else if (score_2 == 21) {
        printf("Player 2 win");
        Input = 'q';
    }

    if (BallX >= COLUMNS) {
        BallX = COLUMNS / 2;
        BallY = LINES / 2;
    }
}

void controlPaddles() {
    char enter;

    if (scanf("%c%c", &Input, &enter) != 2) {
        Input = 'q';
    }

    if (enter != '\n') {
        Input = 'q';
    }

    if (Input == 'a') {
        if (Paddle1Y > 0) {
            Paddle1Y--;
        }
    } else if (Input == 'z') {
        if (Paddle1Y < LINES - 3) {
            Paddle1Y++;
        }
    } else if (Input == 'k') {
        if (Paddle2Y > 0) {
            Paddle2Y--;
        }
    } else if (Input == 'm') {
        if (Paddle2Y < LINES - 3) {
            Paddle2Y++;
        }
    } else if (Input == ' ') {
    } else {
        printf("n/a");
        Input = 'q';
    }
}

int main() {
    initGame();

    while (Input != 'q') {
        view();
        controlPaddles();
        moveBall();
        usleep(100000);
    }

    return 0;
}