#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void drawChars(int n, char ch)
{
    for(int i = 0; i < n; ++i)
        cout << ch;
}
// size from 2 to 20
void drawTriangle(int size)
{
    int j = 1, x;
    for(int i = 0; i < size; ++i)
    {
        x = j;
        while(x > 0)
        {
            cout << "X";
            x--;
        }
        cout << endl;
        j++;
    }
}

// size from 2 to 20
void drawSquare(int size)
{
    char ch = 'X';
    char ch2 = ' ';
    int x = 0;
    drawChars(size, ch);
    cout << endl;
    while(x < size-2)
    {
        cout << "X";
        drawChars(size-2, ch2);
        cout << "X" << endl;
        x++;
    }
    drawChars(size, ch);
    cout << endl;
}

// size from 1 to 20
void drawPyramid(int size)
{
    int x = 0;
    char ch = 'X';
    char ch2 = ' ';
    for(int i = 0; i < size; ++i)
    {
        drawChars(size - i - 1, ch2);
        drawChars(2*x+1, ch);
        cout << endl;
        x++;
    }
}

void drawPyramidChanged(int size, int shift)
{
    int x = 0;
    char ch = 'X';
    char ch2 = ' ';
    for(int i = 0; i < size; ++i)
    {
        drawChars(size - i - 1 + shift, ch2);
        drawChars(2*x+1, ch);
        cout << endl;
        x++;
    }
}

// size from 1 to 20
void drawChristmasTree(int size)
{
    for(int i = 0; i <= size; ++i)
    {
        drawPyramidChanged(i, size-i);
    }

}

// size from 1 to 20
/*void drawChristmasTree(int size)
{
    for(int i = 0; i <= size; ++i)
    {
        int x = 0;
        char ch = 'X';
        char ch2 = ' ';
        for(int i = 0; i < size; ++i)
        {
            drawChars(size - i - 1, ch2);
            drawChars(2*x+1, ch);
            cout << endl;
            x++;
        }
    }
}*/

// size from 2 to 20
void drawFigureX(int size)
{
}

// size from 2 to 20
void drawFigureY(int size)
{
}

// size from 3 to 20
void drawFigureZ(int size)
{
}

// size from 2 to 20
void drawFigureW(int size)
{
}

bool isCommand(const string command,const char *mnemonic)
{
    return command==mnemonic;
}

int main()
{
    string line;
    string command;
    int value;
    cout << "START" << endl;
    while(true)
    {
//		cin.getline(line, MAXLINE);
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }

        // copy line on output with exclamation mark
        cout << "!" << line << endl;;

        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);

        if(isCommand(command,"HA"))
        {
            cout << "END OF EXECUTION" << endl;
            break;
        }

        // read next argument, one int value
        stream >> value;

        if(isCommand(command,"TR"))
        {
            drawTriangle(value);
            continue;
        }
        if(isCommand(command,"SQ"))
        {
            drawSquare(value);
            continue;
        }
        if(isCommand(command,"PY"))
        {
            drawPyramid(value);
            continue;
        }
        if(isCommand(command,"CT"))
        {
            drawChristmasTree(value);
            continue;
        }
        if(isCommand(command,"FX"))
        {
            drawFigureX(value);
            continue;
        }
        if(isCommand(command,"FY"))
        {
            drawFigureY(value);
            continue;
        }
        if(isCommand(command,"FZ"))
        {
            drawFigureZ(value);
            continue;
        }
        if(isCommand(command,"FW"))
        {
            drawFigureW(value);
            continue;
        }

        cout << "wrong argument in test: " << command << endl;
    }

}
