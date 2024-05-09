#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <random>
#include "dungeon.cpp"

using namespace std;

class Game
{
private:
    string player;
    int health, armor, money;
    int arrows, BHarrows, Marrows;
    int Bstrength, accuracy;
    int Wpot, Apot, Mpot;

    void clearInput()
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    void shop()
    {
        Dungeon dungeon;
        int choice = 0;
        cout << "Welcome to Dungeon Town's adventure shop!" << endl;
        cout << "What would you like to buy?";
        for (int i = 0; i < 75; i++)
        {
            cout << " ";
        }
        cout << "Total gold: " << money << endl;
        dungeon.drawLine();

        cout << "1. 10 Arrows - 1 Gold";
        for (int i = 0; i < 75; i++)
        {
            cout << " ";
        }
        cout << "Total arrows: " << arrows << endl;

        cout << "2. Weak health potion - 10 Gold";
        for (int i = 0; i < 65; i++)
        {
            cout << " ";
        }
        cout << "Total weak potions: " << Wpot << endl;

        cout << "3. Average health potion - 20 Gold";
        for (int i = 0; i < 62; i++)
        {
            cout << " ";
        }
        cout << "Total average potions: " << Apot << endl;

        cout << "4. Max health potion - 40 Gold";
        for (int i = 0; i < 66; i++)
        {
            cout << " ";
        }
        cout << "Total max potions: " << Mpot << endl;

        cout << "5. Leave" << endl;
        cin >> choice;
        while ((choice < 1 || choice > 5) || !choice)
        {
            cout << "Invalid, input must be between 1-5" << endl;
        }

        // Each option adds or subtracts from a variable then writes that variable back to the text file
        switch (choice)
        {
        case 1:
            money -= 1;
            arrows += 10;
            dungeon.savePlayer();
            system("cls");
            return shop();
            break;
        case 2:
            money -= 10;
            Wpot += 1;
            dungeon.savePlayer();
            system("cls");
            return shop();
            break;
        case 3:
            money -= 20;
            Apot += 1;
            dungeon.savePlayer();
            system("cls");
            return shop();
            break;
        case 4:
            money -= 40;
            Mpot += 1;
            dungeon.savePlayer();
            system("cls");
            return shop();
            break;
        default:
            system("cls");
            break;
        }
    }

    // Fun side game where you can double however much gold you throw into the well
    void Wwell()
    {
        Dungeon dungeon;
        int coins, odds = 15;
        int roller = rand() % 100;

        cout << "Welcome to the Dungeon Town's wishing well";
        for (int i = 0; i < 50; i++)
        {
            cout << " ";
        }
        cout << "Total gold: " << money << endl;
        dungeon.drawLine();

        cout << "Enter how many coins you would like to toss or -1 to leave. ";
        cin >> coins;
        cout << endl;
        while (!coins || coins > money || (coins <= 0 && coins != -1))
        {
            clearInput();
            cout << "Coins must be greater than 0 and less than the amount of money currently in inventory. ";
            cin >> coins;
            cout << endl;
        }
        if (coins == -1)
        {
            system("cls");
            return;
        }
        else
        {
            money -= coins;
        }

        if (roller <= odds)
        {
            money += (coins + (coins * 2));
            cout << "Congratulations!!! you won " << coins * 2 << " gold" << endl;
            dungeon.savePlayer();
            system("pause");
            system("cls");
            return Wwell();
        }
        else
        {
            cout << "Sorry you lost " << coins << ", better luck next time :(" << endl;
            dungeon.savePlayer();
            system("pause");
            system("cls");
            return Wwell();
        }
    }

    // Initiates the dungeon part of the game
    void dungeon()
    {
        Dungeon dungeon;
        dungeon.getPlayerInfo(player);
        dungeon.DunType();
    }
public:
    // Writes from the text file to the variable
    void getPlayerInfo(string name)
    {
        ifstream file("Characters/" + name + ".txt");
        player = name;
        file >> health >> armor >> money >> arrows >> BHarrows >> Marrows >> Bstrength >> accuracy >> Wpot >> Apot >> Mpot;
    }

    // The UI for the town and allows player to choose shop, wishing well, or dungeon
    void town()
    {
        int Choice = 0;
        do
        {
            try
            {
                cout << "Welcome to Dungeon Town " << player << "!" << endl;
                cout << "Where would you like to go?" << endl;
                cout << "1. Enter dungeon"
                     << "\n2. Enter shop"
                     << "\n3. Wishing well"
                     << "\n4. Leave" << endl;
                cin >> Choice;
                if ((Choice < 1 || Choice > 4) || !Choice)
                {
                    throw(Choice);
                }
            }
            catch (int choice)
            {
                while ((choice < 1 || choice > 4) || !choice)
                {
                    clearInput();
                    cout << "Please Enter 1, 2, 3, or 4" << endl;
                    cout << "1. Enter dungeon"
                         << "\n2. Enter shop"
                         << "\n3. Wishing well"
                         << "\n4. Leave" << endl;
                    cin >> choice;
                }
                Choice = choice;
            }
            switch (Choice)
            {
            case 1:
                system("cls");
                dungeon();
                break;
            case 2:
                system("cls");
                shop();
                break;
            case 3:
                system("cls");
                Wwell();
                break;
            default:
                break;
            }
        } while (Choice != 4);
    }

    Game() {}
};
