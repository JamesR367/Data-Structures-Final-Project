#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <string>
#include "Menus.cpp"
// remove some includes when finished

void clearInput();
void startMenu();

using namespace std;
using namespace std::filesystem;

int main()
{
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL)
    {
        // This sets the size and position of the console window
        MoveWindow(hwnd, 340, 550, 680, 150, TRUE);
    }

    startMenu();
    return 0;
}

void startMenu()
{
    Menus menu;
    int Choice;
    do
    {
        try
        {
            cout << "Welcome to Archer's Dungeon!" << endl;
            cout << "1. Start quest"
                 << "\n2. Options"
                 << "\n3. Quit" << endl;
            cin >> Choice;
            if ((Choice != 1 && Choice != 2 && Choice != 3) || !Choice)
            {
                throw(Choice);
            }
        }
        catch (int choice)
        {
            while ((choice != 1 && choice != 2 && choice != 3) || !choice)
            {
                clearInput();
                cout << "Please Enter 1, 2, or 3" << endl;
                cout << "1. Start"
                     << "\n2. Options"
                     << "\n3. Quit" << endl;
                cin >> choice;
            }
            Choice = choice;
        }

        switch (Choice)
        {
        case 1:
            system("cls");
            menu.characterMenu();
            break;
        case 2:
            system("cls");
            menu.optionsMenu();
            break;
        default:
            break;
        }
    } while (Choice != 3);
}

void clearInput()
{
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}