#include <stdio.h>
#include <graphics.h>
#include <time.h>

struct Snake {
    int x;
    int y;
};

struct Food {
    int x;
    int y;
};

int checkCollision(struct Snake snake[], int length, int size) {

    if (snake[0].x <= size || snake[0].x >= 595 || snake[0].y <= size || snake[0].y >= 445)
        return 1;

    for (int i = 1; i < length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return 1;
    }
    return 0;
}

void showGameOverMessage(int score) {
    setcolor(WHITE);
    char message[50];
    settextstyle(3, HORIZ_DIR, 2);
    sprintf(message, "GAME OVER!");
    outtextxy(230, 200, message);
    sprintf(message, "PONTOS: %d", score);
    outtextxy(230, 230, message);
}

int main() {
    int i, gm, gd, l, d = 2, s = 10;
    srand(time(NULL));
    detectgraph(&gd, &gm);
    initgraph(&gd, &gm, NULL);

    struct Snake snake[100];
    struct Food food;

    setfillstyle(1, 1);
    bar(s - s / 2, s - s / 2, (s / 2) + s * (600 / s), s + s / 2);
    bar(s - s / 2, (-s / 2) + s * (450 / s), (s / 2) + s * (600 / s), (s / 2) + s * (450 / s));
    bar(s - s / 2, s - s / 2, s + s / 2, (s / 2) + s * (450 / s));
    bar((-s / 2) + s * (600 / s), s - s / 2, (s / 2) + s * (600 / s), (s / 2) + s * (450 / s));
    snake[0].x = s * (600 / (2 * s));
    snake[0].y = s * (450 / (2 * s));
    bar(snake[0].x - s / 2, snake[0].y - s / 2, snake[0].x + s / 2, snake[0].y + s / 2);
    l = 5;
    for (i = 1; i < l; i++) {
        snake[i].x = snake[0].x - (i * s);
        snake[i].y = snake[0].y;
        bar(snake[i].x - s / 2, snake[i].y - s / 2, snake[i].x + s / 2, snake[i].y + s / 2);
    }
    food.x = s;
    food.y = s;
    setfillstyle(1, 2);
    while (getpixel(food.x, food.y) != 0) {
        food.x = s * (1 + rand() % (600 / s - 1));
        food.y = s * (1 + rand() % (450 / s - 1));
    }
    bar(food.x - s / 2, food.y - s / 2, food.x + s / 2, food.y + s / 2);
    delay(2000);
    while (1) {
        setfillstyle(1, 0);
        bar(snake[l - 1].x - s / 2, snake[l - 1].y - s / 2, snake[l - 1].x + s / 2, snake[l - 1].y + s / 2);
        for (i = l - 1; i > 0; i--) {
            snake[i].x = snake[i - 1].x;
            snake[i].y = snake[i - 1].y;
        }
        if (d == 0)
            snake[0].x = snake[0].x - s;
        if (d == 1)
            snake[0].y = snake[0].y - s;
        else if (d == 2)
            snake[0].x = snake[0].x + s;
        else if (d == 3)
            snake[0].y = snake[0].y + s;


        if (checkCollision(snake, l, s))
            break;

        if ((GetAsyncKeyState(VK_RIGHT)) && (d != 0))
            d = 2;
        else if ((GetAsyncKeyState(VK_UP)) && (d != 3))
            d = 1;
        else if ((GetAsyncKeyState(VK_LEFT)) && (d != 2))
            d = 0;
        else if ((GetAsyncKeyState(VK_DOWN)) && (d != 1))
            d = 3;
        if (getpixel(snake[0].x, snake[0].y) == 2) {
            food.x = s;
            food.y = s;
            setfillstyle(1, 2);
            while (getpixel(food.x, food.y) != 0) {
                food.x = s * (1 + rand() % (600 / s - 1));
                food.y = s * (1 + rand() % (450 / s - 1));
            }
            bar(food.x - s / 2, food.y - s / 2, food.x + s / 2, food.y + s / 2);
            l = l + 1;
        }
        setfillstyle(1, 1);
        for (i = 0; i < l; i++)
            bar(snake[i].x - s / 2, snake[i].y - s / 2, snake[i].x + s / 2, snake[i].y + s / 2);
        delay(100);
    }
    showGameOverMessage(l - 5);
    while (!GetAsyncKeyState(VK_RETURN));
    closegraph();
    getch();
    return 0;
}
