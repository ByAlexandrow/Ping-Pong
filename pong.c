//
#include <stdio.h>

//
int left_score = 0;
int right_score = 0;

//
void display_game(int flag);
int keyboard(char key, int *rocket_start, int *rocket_end, int y_min_pos, int y_max_pos, char rocket_up, char rocket_down);
int ball_position(int *ball_x, int *ball_y, int *ball_speed_x, int *ball_speed_y, int x_max_pos, int x_min_pos);
int collision(
    int *ball_speed_x, int ball_x, int ball_y,
    int first_racket_start, int first_racket_end, int first_racket_x,
    int second_racket_start, int second_racket_end, int second_racket_x
);

//
int main(void) {
    while (1) {
        int flag = 1;
        display_game(flag);
    }
}

void display_game(int flag) {
    //
    int first_racket_start = 2;
    int first_racket_end = 4;
    int first_racket_x = 3;

    //
    int second_racket_start = 21;
    int second_racket_end = 23;
    int second_racekt_x = 77;

    //
    char vertical = '|';
    char horizontal = '-';
    char space = ' ';
    char ball = '*';

    //
    int ball_x = 40;
    int ball_y = 13;
    int ball_speed_x = 1;
    int ball_speed_y = 1;

    //
    int y_max_pos = 25;
    int y_min_pos = 1;
    int x_max_pos = 80;

    //
    char field[y_max_pos][x_max_pos];

    //
    printf("\033[0d\033[2J");

    //
    while (flag) {
        printf("\033[0d\033[2J"); //
        //
        for (int b = 0; b < y_max_pos; b++) { // вертикальная ось b
            for (int a = 0; a < x_max_pos; a++) { // горизонтальная ось a
                if (a == 0 || a == x_max_pos - 1) {
                    field[b][a] = vertical; //
                } else if (b == 0 || b == y_max_pos - 1) {
                    field[b][a] = horizontal; //
                } else if (b == ball_y && a == ball_x) {
                    field[b][a] == ball; //
                } else if (
                    (b >= first_racket_start && b <= first_racket_end && a == first_racket_x) ||
                    (b >= second_racket_start && b <= second_racket_end && a == second_racekt_x)
                ) {
                    field[b][a] == vertical; //
                } else {
                    field[b][a] = space; //
                }
            }
        }
        ball_position(&ball_x, &ball_y, &ball_speed_x, &ball_speed_y, x_max_pos, y_max_pos); //
        collision(
            &ball_speed_x, ball_x, ball_y,
            first_racket_start, first_racket_end, first_racket_x,
            second_racket_start, second_racket_end, second_racekt_x
        ); //

        for (int b = 0; b < y_max_pos; b++) {
            for (int a = 0; a < x_max_pos; a++) {
                printf("%c", field[b][a]);
            }
            printf("\n");
        }
        printf("First (left) player: %d\n", left_score); //
        printf("Second (right) player: %d\n", right_score); //

        char key = getchar(); //

        keyboard(key, &first_racket_start, &first_racket_end, y_min_pos, y_max_pos, 'a', 'z'); //
        keyboard(key, &second_racket_start, &second_racket_end, y_min_pos, y_max_pos, 'k', 'm'); //

        if (key == '\n') {
            ball_x += ball_speed_x;
            ball_y += ball_speed_y;
        }
    }
}
