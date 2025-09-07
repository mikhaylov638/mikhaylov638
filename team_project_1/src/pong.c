#include <stdio.h>

// размеры поля
#define WIDTH 80
#define HEIGHT 25

// начальные позиции
int ballX = WIDTH / 2;
int ballY = HEIGHT / 2;
int ballDX = 1; // направление по X
int ballDY = 1; // направление по Y

int leftY = HEIGHT / 2 - 1;  // центр левой ракетки
int rightY = HEIGHT / 2 - 1; // центр правой ракетки

int scoreLeft = 0;
int scoreRight = 0;

// отрисовка поля
void draw() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == 0 && (y == leftY || y == leftY+1 || y == leftY+2)) {
                printf("|"); // левая ракетка
            } else if (x == WIDTH - 1 && (y == rightY || y == rightY+1 || y == rightY+2)) {
                printf("|"); // правая ракетка
            } else if (x == ballX && y == ballY) {
                printf("O"); // мяч
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d - %d\n", scoreLeft, scoreRight);
}

// обновление мяча
void updateBall() {
    ballX += ballDX;
    ballY += ballDY;

    // отражение сверху/снизу
    if (ballY <= 0 || ballY >= HEIGHT - 1) {
        ballDY = -ballDY;
    }

    // отскок от левой ракетки
    if (ballX == 1 && ballY >= leftY && ballY <= leftY + 2) {
        ballDX = -ballDX;
    }

    // отскок от правой ракетки
    if (ballX == WIDTH - 2 && ballY >= rightY && ballY <= rightY + 2) {
        ballDX = -ballDX;
    }

    // гол левому игроку
    if (ballX <= 0) {
        scoreRight++;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
    }

    // гол правому игроку
    if (ballX >= WIDTH - 1) {
        scoreLeft++;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
    }
}

// управление
void moveLeft(char cmd) {
    if (cmd == 'a' && leftY > 0) leftY--;
    if (cmd == 'z' && leftY < HEIGHT - 3) leftY++;
}

void moveRight(char cmd) {
    if (cmd == 'k' && rightY > 0) rightY--;
    if (cmd == 'm' && rightY < HEIGHT - 3) rightY++;
}

int main() {
    char cmd;
    while (scoreLeft < 21 && scoreRight < 21) {
        draw();
        printf("Command (A/Z for left, K/M for right, Space = skip): ");
        cmd = getchar();
        getchar(); // съесть перевод строки

        if (cmd == 'a' || cmd == 'z') moveLeft(cmd);
        if (cmd == 'k' || cmd == 'm') moveRight(cmd);
        if (cmd == ' ') {
            // пропуск хода
        }

        updateBall();
    }

    draw();
    if (scoreLeft == 21) {
        printf("Left player wins!\n");
    } else {
        printf("Right player wins!\n");
    }

    return 0;
}
