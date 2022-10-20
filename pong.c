#include <stdio.h>
#include <stdlib.h>

int player1_count = 0;  // Счетчик игрока 1
int player2_count = 0;  // Счетчик игрока 2
int ball_x = 39;         // координата мяча по x
int ball_y = 12;         // координата мяча по y
int vec_ball_x = 1;      // вектор движения мяча по оси x
int vec_ball_y = 1;      // вектор движения мяча по оси y
int racket1 = 11;        // положение ракетки 1
int racket2 = 11;        // положение ракетки 2


int menu();                                          // Начальное меню
void play_game();                                    // Игра
void field_of_play();                                // Игровое поле
int end_game(int player1_count, int player2_count);  // Конец игры
void rocket_movement();                              // движение ракеток
void ball_movement();                                // Движение мяча
void tablo();                                        // Счетчик

int main() {
    printf("Добро пожаловать в игру Пинг-Понг!\n\n");
    while (menu() == 1) {
        menu();
        if (menu() == 0) {
            break;
            }
    }
    return 0;
}

int menu() {
    int command;
    char c;
    printf("1 - старт игры!\n2 - Выход!\n3 - Управление.\n4 - Правила Игры.\n");
    printf("Введите команду: ");
    if (scanf("%d%c", &command, &c) != 2 || c != '\n' || (command >= 5 || command <= 0)) {
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
            printf("\nУправление: A/Z и K/M для перемещения ракеток.\n");
            printf("Space Bar для пропуска действия на очередном шаге игры.\n");
            break;
            case 4:
            printf("\nПосле достижения одним из игроков счета в 21 очко, ");
            printf("игра выводит поздравление победителя и завершается.\n");
            break;
            }
        if (command == 3 || command == 4) {
            return 1;
            }
    exit(0);
}

void field_of_play() {
    int HEIGHT = 26;
    int WIDTH = 81;
    int focus = -1;
    printf("                                   Счет Игры:\n");
    printf("                                     %d : %d\n", player1_count, player2_count);
    while (focus != HEIGHT) {
        focus++;
        for (int i = 0; WIDTH >= i; i++) {
            if ((focus == 0) || (focus == HEIGHT)) {
            printf("=");  // Верхняя и нижняя границы
            } else if ((i == ball_x) && focus == ball_y) {  // Мячик
                printf("0");
            } else if (i == 39) {
                printf("|");  // Середина поля
            } else if (i == 1 && (focus >= racket1 && focus <= racket1 + 2)) {
                printf("|");  // Ракетка 1
            } else if (i == 79 && (focus >= racket2 && focus <= racket2 + 2)) {
                printf("|");  // Ракетка 2
            } else {
                if (((i == 0) || (i == WIDTH))) {
                    printf("|");  // Боковые границы
                }
                printf(" ");  // Заполнение поля
            }
        }
        printf("\n");
    }
    }

int end_game(int player1_count, int player2_count) {
    if (player1_count == 21) {
        printf("Игрок 1 победил! %d : %d\n", player1_count, player2_count);
        return 1;
    } else if (player2_count == 21) {
        printf("Игрок 2 победил! %d : %d\n", player1_count, player2_count);
        return 1;
    }
    return 0;
}

void rocket_movement() {  // движение ракеток
char action;
int flag = 1;
printf("Введите команду для ракетки: ");
    scanf("%c",  &action);
    if  (action == 'A' || action == 'a') {
        if (racket1 > 1) {
            racket1--;
        }
    } else if  (action == 'Z' || action == 'z') {
        if (racket1 < 23) {
            racket1++;
        }
    } else if  (action == 'K' || action == 'k') {
        if (racket2 > 1) {
            racket2--;
        }
    } else if  (action == 'M' || action == 'm') {
        if (racket2 < 23) {
            racket2++;
            }
        } else if  (action == ' ') {
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
    if (ball_x == 1 && ball_y >= racket1 && ball_y <= racket1 + 2) {
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
        ball_x = 2;
        ball_y = racket1 + 1;
        } else if (ball_x == 0) {
        player2_count += 1;
        ball_x = 78;
        ball_y = racket2 + 1;
    }
    }

void play_game() {
    while (1) {
        printf("\e[H\e[2J\e[3J");
        field_of_play();
        rocket_movement();
        tablo();
        if (end_game(player1_count, player2_count))  {
            printf("Поздравляю!\n");
            break;
        }
    }
}



