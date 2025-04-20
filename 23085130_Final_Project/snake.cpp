#include <iostream>
#include <conio.h>          //for handeling input
#include <windows.h>        //for color and crussor
#include <ctime>            // for random time
#include <cstdlib>          // for rand
#include <fstream>          // for saving score to file
#include <cmath>            // for power function

using namespace std;

// constsants for game dimensions and symbols

const int WIDTH = 30;
const int HEIGHT = 20;
const char WALL = 219;
const char PATH = ' ';
const char SNAKE_HEAD = 'p';
const char SNAKE_BODY = 219;
const char FRUIT = '*';
const char ENEMY = 'X';

//implementation of variables in game

int x, y, fruitX, fruitY, score, lives, speed, level;

int tailX[100], tailY[100];        //array to attach tail after eating *
int nTail;

bool gameOver;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

Direction dir;

// console for handeling crusor

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursorPos;

struct Enemy                // tructure for enemy entity

    {

        int x, y;

    };


    // move console crusor to a specific coordinate

Enemy enemies[10];

    // move console crusor to a specific coordinate

void SetCursorPosition(int x, int y)

{
    cursorPos.X = x;
    cursorPos.Y = y;
    SetConsoleCursorPosition(console, cursorPos);
}
//set color in console

void SetColor(int color)

{
    SetConsoleTextAttribute(console, color);
}

// Hides the blinking console cursor

void HideCursor()

{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);
}

// Initializes game variables and places fruit/enemies

void Setup()

{
    gameOver = false;
    dir = RIGHT;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
    lives = 3;
    level = 1;
    speed = 100;


    // Place enemies at valid positions


    for (int i = 0; i < level; i++)

        {
            bool validPosition = false;

            while (!validPosition)

            {
                enemies[i].x = rand() % WIDTH;
                enemies[i].y = rand() % (HEIGHT - 2) + 1;

            if ((enemies[i].x != x || enemies[i].y != y) && (enemies[i].x != fruitX || enemies[i].y != fruitY))
                {
                    validPosition = true;
                }
        }
    }
}

// Renders the game screen

void Draw(char gameScreen[HEIGHT][WIDTH + 2])

{

    // Clear screen buffer

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH + 2; j++)
            gameScreen[i][j] = ' ';

    // Top wall (Chocolate color)

    SetColor(6);  // Chocolate color

    for (int i = 0; i < WIDTH + 2; i++) gameScreen[0][i] = WALL;

    // Bottom wall (Chocolate color)

    for (int i = 0; i < WIDTH + 2; i++) gameScreen[HEIGHT - 1][i] = WALL;

    // Side walls and path (Chocolate color)

    for (int i = 1; i < HEIGHT - 1; i++)

        {
            gameScreen[i][0] = WALL;
            gameScreen[i][WIDTH + 1] = WALL;
        }

    // Snake head and body (White color)

    SetColor(7);  // White color for the snake

    gameScreen[y][x + 1] = SNAKE_HEAD;

    for (int i = 0; i < nTail; i++)

        {

            gameScreen[tailY[i]][tailX[i] + 1] = SNAKE_BODY;
        }

    // Fruit (Green color)

    SetColor(10);  // Green color

    gameScreen[fruitY][fruitX + 1] = FRUIT;

    // Enemies (Red color)

    SetColor(12);  // Red color

    for (int i = 0; i < level; i++)
        {

            gameScreen[enemies[i].y][enemies[i].x + 1] = ENEMY;
        }

    // DrawING screen

    SetCursorPosition(0, 0);
    for (int i = 0; i < HEIGHT; i++)

        {

            for (int j = 0; j < WIDTH + 2; j++)
                {
                    SetColor(7);  // Default color for empty spaces

                    cout << gameScreen[i][j];
                }

            cout << "\n";
    }

    SetColor(14);  // Yellow for score and lives

    cout << "Score: " << score << "  Lives: " << lives << "  Level: " << level << "\n";
}

void Input()

{
    if (_kbhit())

        {
            switch (_getch()) {
                case 'a':if (dir != RIGHT) dir = LEFT;break;

                case 'd':if (dir != LEFT)  dir = RIGHT;break;

                case 'w':if (dir != DOWN)  dir = UP;break;

                case 's':if (dir != UP)    dir = DOWN;break;

                case 'x':gameOver = true;break;
        }
    }
}

// Updates game logic: movement, collisions, level progression

void Logic()

    // Update tail positions

{
    int prevX = tailX[0];

    int prevY = tailY[0];

    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)

        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

    switch (dir) //Movement of snake

    {
        case LEFT:  x--;
            break;

        case RIGHT: x++;
            break;

        case UP:    y--;
            break;

        case DOWN:  y++;
            break;

        default:
            break;
    }

        // Wrap around screen edges

    if (x >= WIDTH) x = 0;
    if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT - 1) y = 1;
    if (y <= 0) y = HEIGHT - 2;

    // Check for collisions with the snake's own body

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            lives--;
            if (lives > 0) {

                // Reset position

                x = WIDTH / 2;
                y = HEIGHT / 2;
                dir = STOP;
                nTail = 0;
            }
            else

                {

                gameOver = true;
            }
        }
    }

    // Check for collisions with fruit
    if (x == fruitX && y == fruitY)
        {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % (HEIGHT - 2) + 1;
        nTail++;

        if (score / 10 >= 4 * level)


        // Level up logic

        {
            level++;
            speed = 100 - (int)(5 * pow(1.5, level - 1));
            if (speed < 20) speed = 20;

            // Add new enemies at each level

            for (int i = level - 1; i < level; i++)

                {

                bool validPosition = false;
                while (!validPosition) {
                    enemies[i].x = rand() % WIDTH;
                    enemies[i].y = rand() % (HEIGHT - 2) + 1;
                    if ((enemies[i].x != x || enemies[i].y != y) && (enemies[i].x != fruitX || enemies[i].y != fruitY))

                    {
                        validPosition = true;
                    }
                }
            }
        }
    }

    // Check for collisions with enemies

    for (int i = 0; i < level; i++)

        {
            if (x == enemies[i].x && y == enemies[i].y)

            {
                lives--;

                if (lives > 0)

                {
                    x = WIDTH / 2;
                    y = HEIGHT / 2;
                    dir = STOP;
                    nTail = 0;

                }

             else

                {
                    gameOver = true;
            }
        }
    }
}

void SaveScore() // function for saving the score

{
    ofstream scoreFile("score.txt", ios::app);

    if (scoreFile.is_open())

        {
            scoreFile << "Final Score: " << score << "\n";
            scoreFile.close();
        }
}

void RestartOrExit()

{
    SetColor(15);  // White for the prompt
    cout << "Do you want to restart? (y/n): ";

    char choice;

    cin >> choice;
    if (choice == 'y' || choice == 'Y')

        {
            Setup();

        while (!gameOver)

        {
            char gameScreen[HEIGHT][WIDTH + 2];

            Draw(gameScreen);
            Input();
            Logic();
            Sleep(speed);
        }

        SaveScore();
        }

        else

        {

            gameOver = true;
        }
}

// Display main menu before starting the game

void ShowMainMenu()

{
    SetColor(10);

    cout << "Welcome to Snake Game!" << endl;
    cout << "1. Start The Game" << endl;
    cout << "2. Exit" << endl;

    cout << "Select an option: ";

    int option;
    cin >> option;
    if (option == 1)

        {
            Setup();

            while (!gameOver)

            {
                char gameScreen[HEIGHT][WIDTH + 2];
                Draw(gameScreen);

                Input();
                Logic();
                Sleep(speed);
            }

        SaveScore();
        RestartOrExit();  // Ask if they want to restart
    }

     else

        {
            gameOver = true;
        }
}

// Saves the score to a file after game ends

void GameOver()         // // Final game over screen

{
    SetCursorPosition(0, HEIGHT + 3);
    SetColor(12);

    cout << "Game Over!" << endl;
    SetColor(7);

    cout << "Final Score: " << score << "\n";

    RestartOrExit();                        // Ask if they want to restart
}

int main()

{
    srand(time(0));
    HideCursor();
    ShowMainMenu();

    if (gameOver)

        {

            GameOver();
        }

    return 0;
}
