#include <ncursesw/ncurses.h>
#include <unistd.h> // для usleep()

#define WIDTH 80
#define HEIGHT 25

int ballX = WIDTH / 2;
int ballY = HEIGHT / 2;
int ballDX = 1;
int ballDY = 1;

int leftY = HEIGHT / 2 - 1;
int rightY = HEIGHT / 2 - 1;

int scoreLeft = 0;
int scoreRight = 0;

void draw() {
    clear();

    // отрисовка рамки
    for (int x = 0; x < WIDTH; x++) {
        mvprintw(0, x, "-");
        mvprintw(HEIGHT - 1, x, "-");
    }

    // левая ракетка
    for (int i = 0; i < 3; i++) {
        mvprintw(leftY + i, 1, "|");
    }

    // правая ракетка
    for (int i = 0; i < 3; i++) {
        mvprintw(rightY + i, WIDTH - 2, "|");
    }

    // мяч
    mvprintw(ballY, ballX, "O");

    // счет
    mvprintw(HEIGHT, 0, "Score: %d - %d", scoreLeft, scoreRight);

    refresh();
}

void updateBall() {
    ballX += ballDX;
    ballY += ballDY;

    if (ballY <= 1 || ballY >= HEIGHT - 2) ballDY = -ballDY;

    if (ballX == 2 && ballY >= leftY && ballY <= leftY + 2) ballDX = -ballDX;
    if (ballX == WIDTH - 3 && ballY >= rightY && ballY <= rightY + 2) ballDX = -ballDX;

    if (ballX <= 0) {
        scoreRight++;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
    }
    if (ballX >= WIDTH - 1) {
        scoreLeft++;
        ballX = WIDTH / 2;
        ballY = HEIGHT / 2;
    }
}

int main() {
    initscr();          // инициализация ncurses
    noecho();           // не выводить нажатые клавиши
    curs_set(FALSE);    // убрать курсор
    nodelay(stdscr, TRUE); // неблокирующий ввод
    keypad(stdscr, TRUE);

    while (scoreLeft < 21 && scoreRight < 21) {
        draw();

        int ch = getch();
        switch (ch) {
            case 'a':
                if (leftY > 1) leftY--;
                break;
            case 'z':
                if (leftY < HEIGHT - 4) leftY++;
                break;
            case 'k':
                if (rightY > 1) rightY--;
                break;
            case 'm':
                if (rightY < HEIGHT - 4) rightY++;
                break;
        }

        updateBall();
        usleep(50000); // задержка (50 мс) для плавности
    }

    clear();
    if (scoreLeft == 21) {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Left player wins!");
    } else {
        mvprintw(HEIGHT / 2, WIDTH / 2 - 5, "Right player wins!");
    }
    refresh();
    sleep(2);

    endwin(); // завершение ncurses
    return 0;
}
