#include <stdio.h> // Подключаем стандартную библиотеку ввода-вывода для использования функций printf и getchar.

int fPScore = 0;
int sPScore = 0;
// Объявляем переменные для хранения очков первого и второго игрока, инициализируем их нулями.

void cross_and_toe_display(int flag);
// Объявляем прототип функции cross_and_toe_display, которая будет отображать игровое поле.

int handle_key(char key, int *rStart, int *rEnd, int min_pos_y, int max_pos_y, char upKey, char downKey);
// Объявляем прототип функции handle_key, которая обрабатывает нажатия клавиш для управления ракетками.

void update_ball_position(int *pointX, int *pointY, int *pointSpeedX, int *pointSpeedY, int max_pos_x, int max_pos_y);
// Объявляем прототип функции update_ball_position, которая обновляет позицию мяча.

void check_collisions(int *pointSpeedX, int pointX, int pointY, int fRStart, int fREnd, int firstRacketX, int sRStart, int sREnd, int secondRacketX);
// Объявляем прототип функции check_collisions, которая проверяет столкновения мяча с ракетками.

int main(void) {
    // Главная функция программы.
    while (1) {
        // Бесконечный цикл, который поддерживает игру в активном состоянии.
        int flag = 1;
        // Переменная flag используется для управления состоянием игры.
        cross_and_toe_display(flag);
        // Вызываем функцию для отображения игрового поля и управления игрой.
    }
}

void cross_and_toe_display(int flag) {
    // Функция для отображения игрового поля и управления игрой.

    int fRStart = 5;
    int fREnd = 7;
    int firstRacketX = 3;
    // Начальные позиции первой ракетки.

    int sRStart = 17;
    int sREnd = 19;
    int secondRacketX = 76;
    // Начальные позиции второй ракетки.

    char vertical = '|';
    char horizontal = '-';
    char space = ' ';
    char point = '*';
    // Символы для отображения игрового поля.

    int pointX = 39;
    int pointY = 12;
    int pointSpeedX = 1;
    int pointSpeedY = 1;
    // Начальные координаты и скорость мяча.

    int max_pos_y = 25;
    int max_pos_x = 80;
    int min_pos_y = 1;
    // Границы игрового поля.

    char pole[max_pos_y][max_pos_x];
    // Массив для хранения состояния игрового поля.

    printf("\033[0d\033[2J");
    // Очистка экрана перед началом игры.

    while (flag) {
        // Основной игровой цикл.
        printf("\033[0d\033[2J");
        // Очистка экрана перед каждым новым кадром.

        // Обновление состояния игрового поля.
        for (int i = 0; i < max_pos_y; i++) {
            for (int j = 0; j < max_pos_x; j++) {
                if (j == 0 || j == max_pos_x - 1) {
                    pole[i][j] = vertical;
                    // Устанавливаем вертикальные границы поля.
                } else if (i == 0 || i == max_pos_y - 1) {
                    pole[i][j] = horizontal;
                    // Устанавливаем горизонтальные границы поля.
                } else if (i == pointY && j == pointX) {
                    pole[i][j] = point;
                    // Устанавливаем позицию мяча.
                } else if ((i >= fRStart && i <= fREnd && j == firstRacketX) ||
                           (i >= sRStart && i <= sREnd && j == secondRacketX)) {
                    pole[i][j] = vertical;
                    // Устанавливаем позиции ракеток.
                } else {
                    pole[i][j] = space;
                    // Устанавливаем пустое пространство.
                }
            }
        }

        update_ball_position(&pointX, &pointY, &pointSpeedX, &pointSpeedY, max_pos_x, max_pos_y);
        // Обновляем позицию мяча и проверяем столкновения с границами поля.

        check_collisions(&pointSpeedX, pointX, pointY, fRStart, fREnd, firstRacketX, sRStart, sREnd, secondRacketX);
        // Проверяем столкновения мяча с ракетками.

        // Отображение игрового поля.
        for (int i = 0; i < max_pos_y; i++) {
            for (int j = 0; j < max_pos_x; j++) {
                printf("%c", pole[i][j]);
                // Выводим символ из массива pole.
            }
            printf("\n");
            // Переходим на новую строку после вывода каждой строки поля.
        }

        printf("Points First's player: %d\n", fPScore);
        printf("Points Second's player: %d\n", sPScore);
        // Отображение текущих очков игроков.

        char key = getchar();
        // Чтение нажатой клавиши.

        handle_key(key, &fRStart, &fREnd, min_pos_y, max_pos_y, 'a', 'z');
        // Обработка нажатий клавиш для первого игрока.

        handle_key(key, &sRStart, &sREnd, min_pos_y, max_pos_y, 'k', 'm');
        // Обработка нажатий клавиш для второго игрока.

        if (key == '\n') {
            // Если нажата клавиша Enter, обновляем позицию мяча.
            pointX += pointSpeedX;
            pointY += pointSpeedY;
        }
    }
}

int handle_key(char key, int *rStart, int *rEnd, int min_pos_y, int max_pos_y, char upKey, char downKey) {
    // Функция обработки нажатий клавиш для управления ракетками.
    if (key == upKey && *rStart != min_pos_y) {
        // Если нажата клавиша для движения вверх и ракетка не в верхней границе, двигаем ракетку вверх.
        (*rStart)--;
        (*rEnd)--;
        return -1;
    }
    if (key == downKey && *rEnd != max_pos_y - 2) {
        // Если нажата клавиша для движения вниз и ракетка не в нижней границе, двигаем ракетку вниз.
        (*rStart)++;
        (*rEnd)++;
        return 1;
    }
    return 0;
}

void update_ball_position(int *pointX, int *pointY, int *pointSpeedX, int *pointSpeedY, int max_pos_x, int max_pos_y) {
    // Функция обновления позиции мяча и проверки столкновений с границами поля.
    if (*pointY == max_pos_y - 2)
        *pointSpeedY = -1;
        // Если мяч достиг нижней границы, меняем направление движения по оси Y.
    if (*pointY == 1)
        *pointSpeedY = 1;
        // Если мяч достиг верхней границы, меняем направление движения по оси Y.
    if (*pointX == max_pos_x - 1) {
        // Если мяч достиг правой границы, увеличиваем очки первого игрока.
        if (fPScore != 20) {
            fPScore++;
        } else {
            printf("Win First player!");
            // Если первый игрок набрал 20 очков, выводим сообщение о победе и завершаем игру.
            return;
        }
    }
    if (*pointX == 0) {
        // Если мяч достиг левой границы, увеличиваем очки второго игрока.
        if (sPScore != 20) {
            sPScore++;
        } else {
            printf("Win Second player!");
            // Если второй игрок набрал 20 очков, выводим сообщение о победе и завершаем игру.
            return;
        }
    }
}

void check_collisions(int *pointSpeedX, int pointX, int pointY, int fRStart, int fREnd, int firstRacketX, int sRStart, int sREnd, int secondRacketX) {
    // Функция проверки столкновений мяча с ракетками.
    if ((sRStart <= pointY && pointY <= sREnd && pointX == secondRacketX - 1))
        *pointSpeedX = -1;
        // Если мяч столкнулся с правой ракеткой, меняем направление движения по оси X.
    if (fRStart <= pointY && pointY <= fREnd && pointX == firstRacketX + 1)
        *pointSpeedX = 1;
        // Если мяч столкнулся с левой ракеткой, меняем направление движения по оси X.
}
