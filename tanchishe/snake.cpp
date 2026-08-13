// snake.cpp - 贪吃蛇 (Windows 控制台版)
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 30;
const int HEIGHT = 20;

struct Point {
    int x, y;
};

class SnakeGame {
private:
    vector<Point> snake;
    Point food;
    int dx, dy;
    int score;
    bool gameOver;
    bool paused;
    int speed;

    void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void hideCursor() {
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 1;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    }

public:
    SnakeGame() { reset(); }

    void reset() {
        snake.clear();
        snake.push_back({WIDTH / 2, HEIGHT / 2});
        snake.push_back({WIDTH / 2 - 1, HEIGHT / 2});
        snake.push_back({WIDTH / 2 - 2, HEIGHT / 2});
        dx = 1; dy = 0;
        score = 0;
        gameOver = false;
        paused = false;
        speed = 300;
        spawnFood();
    }

    void spawnFood() {
        do {
            food.x = rand() % WIDTH;
            food.y = rand() % HEIGHT;
        } while (isOnSnake(food));
    }

    bool isOnSnake(Point p) {
        for (const auto& s : snake)
            if (s.x == p.x && s.y == p.y) return true;
        return false;
    }

    bool isHead(Point p) {
        return p.x == snake[0].x && p.y == snake[0].y;
    }

    void draw() {
        system("cls");
        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH + 2; j++) {
                if (j == 0 || j == WIDTH + 1) cout << "#";
                else {
                    Point p = {j - 1, i};
                    if (p.x == food.x && p.y == food.y) cout << "O";
                    else if (isHead(p)) cout << "@";
                    else if (isOnSnake(p)) cout << "*";
                    else cout << " ";
                }
            }
            cout << endl;
        }

        for (int i = 0; i < WIDTH + 2; i++) cout << "#";
        cout << endl;
        cout << "分数: " << score << "    空格暂停/继续, R 重新开始" << endl;
        cout << "方向键控制" << endl;
    }

    void input() {
        if (_kbhit()) {
            int key = _getch();
            if (key == 224) {
                key = _getch();
                switch (key) {
                    case 72: if (dy != 1) { dx = 0; dy = -1; } break;
                    case 80: if (dy != -1) { dx = 0; dy = 1; } break;
                    case 75: if (dx != 1) { dx = -1; dy = 0; } break;
                    case 77: if (dx != -1) { dx = 1; dy = 0; } break;
                }
            } else if (key == ' ') paused = !paused;
            else if (key == 'r' || key == 'R') reset();
        }
    }

    void logic() {
        if (paused) return;

        Point newHead = {snake[0].x + dx, snake[0].y + dy};

        if (newHead.x < 0 || newHead.x >= WIDTH ||
            newHead.y < 0 || newHead.y >= HEIGHT) {
            gameOver = true;
            return;
        }

        for (size_t i = 0; i < snake.size() - 1; i++) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                gameOver = true;
                return;
            }
        }

        snake.insert(snake.begin(), newHead);

        if (newHead.x == food.x && newHead.y == food.y) {
            score += 10;
            spawnFood();
            if (speed > 60) speed -= 5;
        } else {
            snake.pop_back();
        }
    }

    void run() {
        hideCursor();
        srand((unsigned)time(NULL));

        while (true) {
            input();
            if (gameOver) {
                draw();
                cout <<"真菜"<<endl;
                cout << "游戏结束! 最终分数: " << score << endl;
                cout << "按 R 重新开始, 按 Q 退出" << endl;
                while (true) {
                    if (_kbhit()) {
                        int key = _getch();
                        if (key == 'r' || key == 'R') { reset(); break; }
                        else if (key == 'q' || key == 'Q') { system("cls"); return; }
                    }
                }
                continue;
            }
            draw();
            logic();
            Sleep(speed);
        }
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);  
    cout << "=== 贪吃蛇 ===" << endl;
    cout << "按任意键开始..." << endl;
    _getch();

    SnakeGame game;
    game.run();
    return 0;
}
