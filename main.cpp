#include <iostream>
#include <conio.h>
#include <string>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

using namespace std;
//initialize colours
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

bool check(int a[6][7]);
bool space (int a[6][7]);

void print(char a[6][7], int b[6][7], int pOne, int pTwo)
{
    cout << endl;
    for (int i = 0 ; i < 6 ; i++)
    {
        cout << "\t\t||";
        for(int j = 0 ; j < 7 ; j++)
        {
            if(b[i][j] == 1)
                SetConsoleTextAttribute(h,pOne);
            else if(b[i][j] == 2)
                SetConsoleTextAttribute(h,pTwo);
            cout << a[i][j];
            SetConsoleTextAttribute(h,15);

            if(j <6)
                cout << "|";
        }
        cout << "||" <<endl;
    }
    cout << "\t\t-----------------\n";
    cout << "\t\t  1 2 3 4 5 6 7\n";
}

void drop (int person, char board[6][7], int layout[6][7])
{

    int column;
    do
    {
        cout << "\nPlayer " << person << " select a column (1-7): ";
        cin >> column;
    } while(column > 7 || column < 1 || board[0][column-1] == 'o');

    for(int i = 5 ; i >= 0 ; i--)
    {
        if(board[i][column-1] == ' ')
        {
            board[i][column-1] = 'o';

            if(person == 1)
                layout[i][column-1] = 1;
            else if(person == 2)
                layout[i][column-1] = 2;

            i = -1;
        }
    }

}


void printB (int a[6][7])
{
    for(int i = 0 ; i < 6 ; i++)
    {
        for(int j = 0; j < 7 ; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    SetConsoleTextAttribute(h,15);
    string col1, col2;
    cout << "Player 1\nEnter your colour (blue, red, yellow, green, purple): ";
    do
    {
        cin >> col1;
    }while(col1 != "green" && col1 != "blue" && col1 != "red" && col1 != "yellow" && col1 != "purple");

    cout << "\n\nPlayer 2\nEnter your colour, do not pick the same as Player 1 (blue, red, yellow, green, purple): ";
    do
    {
        cin >> col2;
    }while(col2 != "green" && col2 != "blue" && col2 != "red" && col2 != "yellow" && col2 != "purple" || col1 == col2);

    int c, d;
    //colour for player 1
    if (col1 == "green")
        c = 10;
    else if (col1== "blue")
        c = 11;
    else if (col1 == "red")
        c = 12;
    else if (col1 == "purple")
        c = 13;
    else if (col1 == "yellow")
        c = 14;

    //colour for player 2
    if (col2 == "green")
        d = 10;
    else if (col2== "blue")
        d = 11;
    else if (col2 == "red")
        d = 12;
    else if (col2 == "purple")
        d = 13;
    else if (col2 == "yellow")
        d = 14;

    cout <<endl;
    SetConsoleTextAttribute(h,c);
    cout << "Player 1";
    SetConsoleTextAttribute(h,d);
    cout << "\nPlayer 2";
    SetConsoleTextAttribute(h,15);

    //initialize empty board
    char board[6][7] = {{' ', ' ', ' ',' ', ' ', ' ', ' '},
                        {' ', ' ', ' ',' ', ' ', ' ', ' '},
                        {' ', ' ', ' ',' ', ' ', ' ', ' '},
                        {' ', ' ', ' ',' ', ' ', ' ', ' '},
                        {' ', ' ', ' ',' ', ' ', ' ', ' '},
                        {' ', ' ', ' ',' ', ' ', ' ', ' '}};

    int layout[6][7];
    for(int i = 0 ; i < 6 ; i++)
        for (int j = 0 ; j < 7 ; j++)
            layout[i][j] = 0;

    //display board
    print(board, layout, c ,d);

    //driver loop
    bool win1 = false, win2 = false, full = false;
    while (!win1 && !win2 && !full)
    {
        drop(1, board, layout);
        print(board, layout, c, d);
        //printB(layout);
        win1 = check(layout);
        if(win1 == true)
        {
            cout << "Player 1 wins!";
            break;
        }

        drop(2, board, layout);
        print(board, layout, c, d);
        //printB(layout);
        win2 = check(layout);
        if(win2 == true)
        {
            cout << "Player 2 wins!";
        }
        full = space(layout);
    }
    if(full)
        cout << "Board is full, play again!";

    SetConsoleTextAttribute(h,0);
    return 0;
}

bool check(int a[6][7])
{
    //check horizontal
    for(int i = 0 ; i < 6 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            if(a[i][j] == 1 && a[i][j+1] == 1 && a[i][j+2] == 1 && a[i][j+3] == 1)
                return true;
            if(a[i][j] == 2 && a[i][j+1] == 2 && a[i][j+2] == 2 && a[i][j+3] == 2)
                return true;
        }
    }

    //check vertical
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 7 ; j++)
        {
            if(a[i][j] == 1 && a[i+1][j] == 1 && a[i+2][j] == 1 && a[i+3][j] == 1)
                return true;
            if(a[i][j] == 2 && a[i+1][j] == 2 && a[i+2][j] == 2 && a[i+3][j] == 2)
                return true;
        }
    }

    //check diagonal top left to bottom right
    for(int i = 0 ; i < 3 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            if(a[i][j] == 1 && a[i+1][j+1] == 1 && a[i+2][j+2] == 1 && a[i+3][j+3] == 1)
                return true;
            if(a[i][j] == 2 && a[i+1][j+1] == 2 && a[i+2][j+2] == 2 && a[i+3][j+3] == 2)
                return true;
        }
    }

    //check diagonal bottom left to top right
    for(int j = 6 ; j >= 3 ; j--)
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            if(a[i][j] == 1 && a[i+1][j-1] == 1 && a[i+2][j-2] == 1 && a[i+3][j-3] == 1)
                return true;
            if(a[i][j] == 2 && a[i+1][j-1] == 2 && a[i+2][j-2] == 2 && a[i+3][j-3] == 2)
                return true;
        }
    }
    return false;

}

bool space (int a[6][7])
{
    for(int i = 0 ; i < 6 ; i++)
        for(int j = 0 ; j < 7 ; j++)
            if(a[i][j] == 0)
                return false;
    return true;
}

