// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<time.h>
#include<windows.h>
#include<conio.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

typedef struct point {
    int x;
    int y;
}Point;

bool foodConsumed = false, gameOver = false;
int width = 25, height = 25, totalPoints = 0;
Point snake_head = Point{ 1, height/2 };
Point snake_tail = snake_head;
vector<Point>snake_points;
int direction = 0, prevDirection = 0;

void displayInstructions();

vector<vector <int>> initializeBoard(int width, int height)
{
    int i, j;
    vector<vector<int>>gameBoard(width);
    for (i = 0; i < height; i++)
    {
        gameBoard[i] = vector<int>(width);
        for (j = 0; j < width; j++)
        {
            if (i == 0 || i == (height - 1) || (j == 0) || (j == width - 1))
                gameBoard[i][j] = 1;
        }
   }
    return gameBoard;
}

void displayBoard(vector<vector<int>> &gameBoard, int width, int height)
{
    int i, j;
    system("cls");
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (gameBoard[j][i] == 1)
            {
                cout << "+ ";
            }

            else if (gameBoard[j][i] == 2)
            {
                cout << "o ";
            }

            else if (gameBoard[j][i] == 3)
            {
                cout << "* ";
            }

            else
                cout << "  ";
        }
        cout << endl;
    }

}

void foodGenerator(vector<vector<int>>&gameBoard, int width, int height)
{
    Point foodPoint = Point{ 0,0 };
    srand(time(NULL));
    while (gameBoard[foodPoint.x][foodPoint.y] != 0)
    {
        foodPoint.x = rand() % (width - 1) + 1;
        foodPoint.y = rand() % (height - 1) + 1;
        if (gameBoard[foodPoint.x][foodPoint.y] == 0)
        {
            gameBoard[foodPoint.x][foodPoint.y] = 3;
            break;
        }
    }
}

void refreshSnake(vector<vector<int>>& gameBoard, int width, int height)
{
    gameBoard[snake_points[0].x][snake_points[0].y] = 0;
    for (int i = snake_points.size() - 1; i > 0 ; i--)
    {
        if (i == snake_points.size() - 1)
        {
            gameBoard[snake_points[i].x][snake_points[i].y] = 0;
        }
        snake_points[i].x = snake_points[i - 1].x;
        snake_points[i].y = snake_points[i - 1].y;
        gameBoard[snake_points[i].x][snake_points[i].y] = 2;
    }
    snake_tail = snake_points[snake_points.size() - 1];
    switch (direction)
    {
        case 0: snake_points[0].x++; break;
        case 1: snake_points[0].y++; break;
        case 2: snake_points[0].x--; break;
        case 3: snake_points[0].y--; break;
    }

    if (snake_points[0].x == 0 || snake_points[0].x == width - 1 || snake_points[0].y == 0 || snake_points[0].y == height - 1)
        gameOver = true;
    
    else if (gameBoard[snake_points[0].x][snake_points[0].y] == 2 || gameBoard[snake_points[0].x][snake_points[0].y] == 1)
        gameOver = true;

    else if (gameBoard[snake_points[0].x][snake_points[0].y] == 3)
    {
        totalPoints++;
        snake_points.push_back(snake_tail);
        gameBoard[snake_tail.x][snake_tail.y] = 2;
        foodGenerator(gameBoard, width, height);
    }
    gameBoard[snake_points[0].x][snake_points[0].y] = 2;
}

void playGame(vector<vector<int>>&gameBoard, int width, int height)
{
    foodGenerator(gameBoard, width, height);
    snake_points.push_back(snake_head);
    gameBoard[snake_points[0].x][snake_points[0].y] = 2;
    displayBoard(gameBoard, width, height);

    int x;

    while (!gameOver)
    {
        while (_kbhit())
        {
            x = _getch();
            if (x == 224)
            {
                x = _getch();
                switch (x)
                {
                case KEY_UP:
                    direction = 3;
                    break;
                case KEY_LEFT:
                    direction = 2;
                    break;
                case KEY_RIGHT:
                    direction = 0;
                    break;
                case KEY_DOWN:
                    direction = 1;
                    break;
                }
            }
        }
        refreshSnake(gameBoard, width, height);
        displayBoard(gameBoard, width, height);
        if (gameOver)
        {
            system("cls");
            cout << "Total Points : " << totalPoints << "\n";
            cout << "GAME OVER!\n";
            return;
        }
        Sleep(100);
    
    }
}

void startGame(int width, int height)
{

    vector<vector<int>> gameBoard =  initializeBoard(width,height);
    playGame(gameBoard, width, height);

}

void displayMainMenu()
{
    int ch;
    system("cls");
    cout << "Please choose one of the above:\n 1.Help\n 2.Start new Game\n 3.Quit\n";
    do {
        cin >> ch;
        switch (ch)
        {
        case 1: displayInstructions();
            break;
        case 2: startGame(width, height);
            break;
        case 3: break;
        }
    } while (ch != 3);
}

void displayInstructions()
{
    char ch;
    system("cls");
    cout << "Objective : Try to get as many points as possible\n";
    cout << " Rules : \n 1. Don't bump into the walls. \n 2 . Don't bump into your own body \n 3. Eat as many fruits as possible to earn points.";
    cout << "Keys : Use the up, down , left and right arrow keys to move.\n";
    cout << "Press B to go back to main menu.\n";
    do {
        cin >> ch;
        if (ch == 'B')
        {
            displayMainMenu();
        }
    } while (ch != 'B');
}

int main()
{
    displayMainMenu();
}
