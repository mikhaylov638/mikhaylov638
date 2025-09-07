 #include <stdio.h>

#define ROWS_FIELD 25
#define COLS_FIELD 80

int DrawField(int pos_L, int pos_R, int score_L, int score_R, int ball_x,
              int ball_y);

int main() {
  int pos_L = 13;
  int pos_R = 13;
  int score_L = 0;
  int score_R = 0;
  int ball_x = 13;
  int ball_y = COLS_FIELD / 2;

  int vector_x = 1;
  int vector_y = 1;
  DrawField(pos_L, pos_R, score_L, score_R, ball_x, ball_y);
  while (score_L < 21 && score_R < 21) {
    char c = getchar();
    if (c == 'A' || c == 'a') {
      if (pos_L > 2) pos_L--;
    } else if (c == 'Z' || c == 'z') {
      if (pos_L < ROWS_FIELD - 1) pos_L++;
    } else if (c == 'K' || c == 'k') {
      if (pos_R > 2) pos_R--;
    } else if (c == 'M' || c == 'm') {
      if (pos_R < ROWS_FIELD - 1) pos_R++;
    } else if (c == ' ') {
      // skip
    } else if (c == '\n') {
      // ball double action fix
      continue;
    }
    printf("\033[0d\033[2J");
    // ball logic

    // proverki po visote
    if (ball_x == 25) vector_x = 0;
    if (ball_x == 1) vector_x = 1;
    if (vector_x == 1) {
      ball_x++;
    } else {
      ball_x--;
    }
    // po shirine
    if (ball_y == 78 &&
        (ball_x == pos_R || ball_x == pos_R - 1 || ball_x == pos_R + 1)) {
      vector_y = 0;
    }
    if (ball_y == 3 &&
        (ball_x == pos_L || ball_x == pos_L - 1 || ball_x == pos_L + 1)) {
      vector_y = 1;
    }
    if (ball_y == 79) {
      score_R++;
      ball_x = 13;
      ball_y = COLS_FIELD / 2;
      vector_y = 0;
    }
    if (ball_y == 2) {
      score_L++;
      ball_x = 13;
      ball_y = COLS_FIELD / 2;
      vector_y = 1;
    }
    if (ball_y == 1) vector_y = 1;
    if (vector_y == 1) {
      ball_y++;
    } else {
      ball_y--;
    }

    DrawField(pos_L, pos_R, score_L, score_R, ball_x, ball_y);
  }
  if (score_L == 21) {
    printf("Player 1 wins");
  } else if (score_R == 21) {
    printf("Player 2 wins");
  }
  return 0;
}
// ball logic

int DrawField(int pos_L, int pos_R, int score_L, int score_R, int ball_x,
              int ball_y) {
  printf("\033[0d\033[2J");
  printf("First to score 21 points wins!\n");
  printf(
      "Player 1: A - up, Z - down, Space - skip || Player 2: K - up, Z - down, "
      "Space - skip\n");
  printf("                                  Score: %d:%d\n", score_L, score_R);
  for (int i = 0; i <= ROWS_FIELD + 1; i++) {
    for (int j = 0; j <= COLS_FIELD + 1; j++) {
      if ((i == 0) || (i == ROWS_FIELD + 1)) {
        printf("-");
      } else if ((j == 0) || (j == COLS_FIELD + 1)) {
        printf("|");
      } else if ((i == pos_L - 1) && (j == 2)) {
        printf("|");
      } else if ((i == pos_L) && (j == 2)) {
        printf("|");
      } else if ((i == pos_L + 1) && (j == 2)) {
        printf("|");
      } else if ((i == pos_R - 1) && (j == 79)) {
        printf("|");
      } else if ((i == pos_R) && (j == 79)) {
        printf("|");
      } else if ((i == pos_R + 1) && (j == 79)) {
        printf("|");
      } else if ((i == ball_x) && (j == ball_y)) {
        printf("O");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
  return 0;
}
