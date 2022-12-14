#include <stdio.h>

int player1_count = 0;  // Счетчик игрока 1
int player2_count = 0;  // Счетчик игрока 2
int ball_x = 39;        // координата мяча по x
int ball_y = 12;        // координата мяча по y
int vec_ball_x = 1;     // вектор движения мяча по оси x
int vec_ball_y = 1;     // вектор движения мяча по оси y
int racket1 = 11;       // положение ракетки 1
int racket2 = 11;       // положение ракетки 2

int menu();              // Начальное меню
void play_game();        // Игра
void field_of_play();    // Игровое поле
void rocket_movement();  // движение ракеток
void ball_movement();    // Движение мяча
void tablo();            // Счетчик
void clear();            // очистка экрана
int end_game(int player1_count, int player2_count);  // Конец игры

int main() {
    printf("Добро пожаловать в игру Пинг-Понг!\n\n");
    int res_menu = menu();
    while (res_menu) {
        res_menu = menu();
    }
    return 0;
}

int menu() {
    int command;
    char c;
    printf("1 - Старт игры!\n2 - Выход!\n3 - Управление.\n4 - Правила Игры.\n");
    printf("Введите команду: ");
    if (scanf("%d%c", &command, &c) != 2 || (command >= 5 || command <= 0)) {
        printf("\nНекорректный ввод. Попробуйте еще раз!\n");
        return 0;
    }
    switch (command) {
        case 1:
            play_game();
            break;
        case 2:
            printf("\nДо встречи!\n");
            break;
        case 3:
            clear();
            printf("Управление:\nA/Z и K/M для перемещения ракеток.\n");
            printf("Space Bar для пропуска действия на очередном шаге игры.\n\n");
            break;
        case 4:
            clear();
            printf("Правила Игры:");
            printf("\nПосле достижения одним из игроков счета в 21 очко, ");
            printf("игра выводит поздравление победителя и завершается.\n\n");
            break;
    }
    if (command == 3 || command == 4) {
        return 1;
    }
    return 0;
}

void field_of_play() {
    int HEIGHT = 26;
    int WIDTH = 81;
    int focus = -1;
    printf("%55s\n", "Счет Игры:");
    printf("%40d : %d\n", player1_count, player2_count);
    while (focus != HEIGHT) {
        focus++;
        for (int i = -1; WIDTH >= i; i++) {
            if ((focus == 0) || (focus == HEIGHT)) {
                printf("=");  // Верхняя и нижняя границы
            } else if ((i == ball_x) && focus == ball_y) {  // Мячик
                printf("0");
            } else if (i == 39) {
                printf("|");  // Середина поля
            } else if (i == 0 && (focus >= racket1 && focus <= racket1 + 2)) {
                printf("|");  // Ракетка 1
            } else if (i == 79 && (focus >= racket2 && focus <= racket2 + 2)) {
                printf("|");  // Ракетка 2
            } else {
                if (((i == -1) || (i == WIDTH))) {
                    printf("|");  // Боковые границы
                }
                printf(" ");  // Заполнение поля
            }
        }
        printf("\n");
    }
}

void rocket_movement() {  // движение ракеток
    char action;
    int flag = 1;
    printf("Введите команду для ракетки: ");
    scanf("%c", &action);
    if (action == 'A' || action == 'a') {
        if (racket1 > 1) {
            racket1--;
        }
    } else if (action == 'Z' || action == 'z') {
        if (racket1 < 23) {
            racket1++;
        }
    } else if (action == 'K' || action == 'k') {
        if (racket2 > 1) {
            racket2--;
        }
    } else if (action == 'M' || action == 'm') {
        if (racket2 < 23) {
            racket2++;
        }
    } else if (action == ' ') {
        flag = 1;
    } else {
        flag = 0;
    }
    if (flag == 1) {
        ball_movement();
    }
}

void ball_movement() {
    ball_x += vec_ball_x;
    ball_y += vec_ball_y;
    if (ball_y == 0 || ball_y == 26) {
        ball_y -= 2 * vec_ball_y;
        vec_ball_y = -vec_ball_y;
    }
    if (ball_x == 0 && ball_y >= racket1 && ball_y <= racket1 + 2) {
        ball_x -= 2 * vec_ball_x;
        vec_ball_x = -vec_ball_x;
    }
    if (ball_x == 79 && ball_y >= racket2 && ball_y <= racket2 + 2) {
        ball_x -= 2 * vec_ball_x;
        vec_ball_x = -vec_ball_x;
    }
}

void tablo() {
    if (ball_x == 80) {
        player1_count += 1;
        ball_x = 1;
        racket1 = 11;
        racket2 = 11;
        ball_y = racket1 + 1;
    } else if (ball_x == -1) {
        player2_count += 1;
        ball_x = 78;
        racket1 = 11;
        racket2 = 11;
        ball_y = racket2 + 1;
    }
}

int end_game(int player1_count, int player2_count) {
    if (player1_count == 21) {
        clear();
        printf("\nИгрок 1 победил! %d : %d\n", player1_count, player2_count);
        return 0;
    } else if (player2_count == 21) {
        clear();
        printf("\nИгрок 2 победил! %d : %d\n", player1_count, player2_count);
        return 0;
    }
    return 1;
}

void clear() { printf("\e[H\e[2J\e[3J"); }

void play_game() {
    while (end_game(player1_count, player2_count)) {
        clear();
        field_of_play();
        rocket_movement();
        tablo();
    }
    printf("Поздравляю!\n");
}
