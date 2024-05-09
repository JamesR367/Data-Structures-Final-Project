#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <string>
#include <random>

using namespace std;

struct BTnode
{
    int data;
    BTnode *left;
    BTnode *right;
};

class Dungeon
{
private:
    string player;
    int health, armor, money;
    int arrows, BHarrows, Marrows;
    int Bstrength, accuracy;
    int Wpot, Apot, Mpot;
    BTnode *root = new BTnode{0, nullptr, nullptr};

    // basically a while loop to check if an integer is in range for options
    int intcheck(int min, int max, int input)
    {
        while ((input < min || input > max) || !input)
        {
            clearInput();
            cout << "Invalid, choose a number between " << min << " and " << max << endl;
            cin >> input;
        }
        return input;
    }

    void clearInput()
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

    //Creates the dungeon using a binary tree
    int genDungeon(int level, int size, BTnode *root)
    {
        int Lnum = rand() % 4 + 1;
        int Rnum = rand() % 4 + 1;

        root->left = new BTnode{Lnum, nullptr, nullptr};
        root->right = new BTnode{Rnum, nullptr, nullptr};
        if (root == nullptr)
        {
            return 0;
        }
        else if (level == size)
        {
            return 1;
        }
        else
        {
            return genDungeon(level + 1, size, root->left) + genDungeon(level + 1, size, root->right);
        }
    }

    //This is the UI for the entrance of the dungeon 
    int entranceRoom()
    {
        int Choice;

        cout << "You are at the entrance of the dungeon where would you like to go?" << endl;
        drawLine();

        cout << "1. Go left" << endl;
        cout << "2. Go right" << endl;
        cout << "3. Leave" << endl;

        cin >> Choice;
        Choice = intcheck(1, 3, Choice);

        switch (Choice)
        {
        case 1:
            return 0;
            break;
        case 2:
            return 1;
            break;
        default:
            break;
        }
        return -1;
    }

    //This is the UI for an empty room in the dungeon
    int emptyRoom()
    {

        int Choice;

        cout << "This room is empty where would you like to go next?" << endl;
        drawLine();

        cout << "1. Go left" << endl;
        cout << "2. Go right" << endl;
        cout << "3. Leave dungeon" << endl;

        cin >> Choice;
        Choice = intcheck(1, 3, Choice);

        switch (Choice)
        {
        case 1:
            return 0;
            break;
        case 2:
            return 1;
            break;
        default:
            break;
        }
        return 2;
    }

    //This is the UI for the upgrade screen 
    void upgradePlayer()
    {
        int choice;
        cout << "What would you like to upgrade" << endl;
        cout << "1. Health" << endl;
        cout << "2. Armor" << endl;
        cout << "3. Bow strenth (Makes attacks stronger)" << endl;
        cout << "4. Accuracy" << endl;
        cin >> choice;
        choice = intcheck(1, 4, choice);

        switch (choice)
        {
        case 1:
            health += 2;
            break;
        case 2:
            if (armor >= 95)
            {
                cout << "You have max armor please choose a separate stat" << endl;
                return upgradePlayer();
            }
            else
            {
                armor += 5;
            }
            break;
        case 3:
            Bstrength += 1;
            break;
        case 4:
            if (accuracy >= 95)
            {
                cout << "You have max accuracy please choose a separate stat" << endl;
                return upgradePlayer();
            }
            else
            {
                accuracy += 2;
            }
            break;

        default:
            break;
        }
    }

    //A random integer chooses what the player gets when they defeat an enemy
    void mobRewards()
    {
        int reward = rand() % 5 + 1;

        switch (reward)
        {
        case 1:
            cout << "You found 15 gold" << endl;
            money += 15;
            system("pause");
            break;
        case 2:
            cout << "You found 10 arrows" << endl;
            arrows += 10;
            system("pause");
            break;
        case 3:
            cout << "You found 3 broad head arrows" << endl;
            BHarrows += 3;
            system("pause");
            break;
        case 4:
            cout << "You found 1 magic arrow" << endl;
            BHarrows += 1;
            system("pause");
            break;
        case 5:
            cout << "You found 25 gold" << endl;
            money += 25;
            system("pause");
            break;
        default:
            break;
        }
    }

    //A random integer chooses what the player gets when they defeat a boss
    void bossRewards()
    {
        int reward = rand() % 5 + 1;

        switch (reward)
        {
        case 1:
            cout << "You found 50 gold" << endl;
            money += 50;
            system("pause");
            break;
        case 2:
            cout << "You found an upgrade template" << endl;
            upgradePlayer();
            system("pause");
            break;
        case 3:
            cout << "You found 10 magic arrows" << endl;
            Marrows += 10;
            system("pause");
            break;
        default:
            break;
        }
    }

    //The UI for the fight for mobs and bosses
    int battle(int Ehealth, int Eattack, int Phealth, string name)
    {
        int choice, Achoice, Hchoice;
        int hitMob = rand() % 100;
        int mobHit = rand() % 100;

        if (Phealth <= 0)
        {
            return -1;
        }
        else if (Ehealth <= 0)
        {
            if (root->right == nullptr && root->left == nullptr)
            {
                bossRewards();
            }
            else
            {
                mobRewards();
            }
            return 0;
        }

        cout << player << "'s health:" << Phealth;
        for (int i = 0; i < 55; i++)
        {
            cout << " ";
        }
        cout << name << "'s health:" << Ehealth << endl;
        drawLine();
        cout << "1.Attack" << endl;
        cout << "2.Heal" << endl;
        cout << "3.Flee dungeon" << endl;
        cin >> choice;
        choice = intcheck(1, 3, choice);

        switch (choice)
        {
        case 1:
            cout << "Which arrow would you like to use" << endl;
            cout << "1. Arrow: " << arrows << endl;
            cout << "2. Broad head arrow: " << BHarrows << endl;
            cout << "3. Magic arrow: " << Marrows << endl;
            cin >> Achoice;
            Achoice = intcheck(1, 3, Achoice);
            switch (Achoice)
            {
            case 1:
                if (arrows > 0)
                {
                    if (accuracy < hitMob)
                    {
                        Ehealth -= 5 + Bstrength;
                        arrows -= 1;
                        cout << "You hit the " << name << endl;
                    }
                    else
                    {
                        cout << "You missed the " << name << endl;
                        arrows -= 1;
                    }

                    if (mobHit > armor)
                    {
                        Phealth -= Eattack;
                        cout << "The " << name << " hit you" << endl;
                    }
                    else
                    {
                        cout << "The " << name << " missed you" << endl;
                    }
                }
                else
                {
                    cout << "No arrows in inventory" << endl;
                }
                system("pause");
                system("cls");
                return battle(Ehealth, Eattack, Phealth, name);
                break;
            case 2:
                if (BHarrows > 0)
                {
                    if (accuracy < hitMob)
                    {
                        Ehealth -= 7 + Bstrength;
                        BHarrows -= 1;
                        cout << "You hit the " << name << endl;
                    }
                    else
                    {
                        cout << "You missed the " << name << endl;
                        BHarrows -= 1;
                    }

                    if (mobHit > armor)
                    {
                        Phealth -= Eattack;
                        cout << "The " << name << " hit you" << endl;
                    }
                    else
                    {
                        cout << "The " << name << " missed you" << endl;
                    }
                }
                else
                {
                    cout << "No Broad head arrows in inventory" << endl;
                }
                system("pause");
                system("cls");
                return battle(Ehealth, Eattack, Phealth, name);
                break;
            case 3:
                if (Marrows > 0)
                {
                    if (accuracy < hitMob)
                    {
                        Ehealth -= 9 + Bstrength;
                        Marrows -= 1;
                        cout << "You hit the " << name << endl;
                    }
                    else
                    {
                        cout << "You missed the " << name << endl;
                        Marrows -= 1;
                    }

                    if (mobHit > armor)
                    {
                        Phealth -= Eattack;
                        cout << "The " << name << " hit you" << endl;
                    }
                    else
                    {
                        cout << "The " << name << " missed you" << endl;
                    }
                }
                else
                {
                    cout << "No magic arrows in inventory" << endl;
                }
                system("pause");
                system("cls");
                return battle(Ehealth, Eattack, Phealth, name);
                break;

            default:
                break;
            }

            break;
        case 2:
            cout << "Which health potion would you like to use" << endl;
            cout << "1. Weak potion: " << Wpot << endl;
            cout << "2. Average potion: " << Apot << endl;
            cout << "3. Max potion: " << Mpot << endl;
            cin >> Hchoice;
            Hchoice = intcheck(1, 3, Hchoice);
            switch (Hchoice)
            {
            case 1:
                if (Wpot > 0)
                {
                    if (Phealth + 5 > health)
                    {
                        Phealth = health;
                    }
                    else
                    {
                        Phealth += 5;
                        cout << "You healed 5 health" << endl;
                        if (mobHit > armor)
                        {
                            Phealth -= Eattack;
                            cout << "The " << name << " hit you" << endl;
                        }
                        else
                        {
                            cout << "The " << name << " missed you" << endl;
                        }
                    }
                }
                else
                {
                    cout << "There are weak potions in your inventory" << endl;
                }

                system("pause");
                system("cls");
                return battle(Ehealth, Eattack, Phealth, name);
                break;
            case 2:
                if (Apot > 0)
                {
                    if (Phealth + 7 > health)
                    {
                        Phealth = health;
                    }
                    else
                    {
                        Phealth += 7;
                        cout << "You healed 7 health" << endl;
                        if (mobHit > armor)
                        {
                            Phealth -= Eattack;
                            cout << "The " << name << " hit you" << endl;
                        }
                        else
                        {
                            cout << "The " << name << " missed you" << endl;
                        }
                    }
                }
                else
                {
                    cout << "There are average potions in your inventory" << endl;
                }

                system("pause");
                system("cls");
                return battle(Ehealth, Eattack, Phealth, name);
                break;
            case 3:
                if (Mpot > 0)
                {
                    Phealth += health;
                    cout << "You healed 7 health" << endl;
                    if (mobHit > armor)
                    {
                        Phealth -= Eattack;
                        cout << "The " << name << " hit you" << endl;
                    }
                    else
                    {
                        cout << "The " << name << " missed you" << endl;
                    }
                }
                else
                {
                    cout << "There are max potions in your inventory" << endl;
                }

                system("pause");
                system("cls");
                return battle(Ehealth, Eattack, Phealth, name);
                break;

            default:
                break;
            }

            break;
        case 3:
            return -1;
            break;

        default:
            break;
        }
        return 0;
    }

    //Makes a copy of the player's health for the fight as well as gets info for the enemy based on room number
    int mobRoom(int type)
    {
        int leave = 0;
        int Eattack, Ehealth;
        ifstream gob("mobs/goblin.txt");
        ifstream orc("mobs/orc.txt");
        ifstream skel("mobs/skeleton.txt");
        switch (type)
        {
        case 2:
            gob >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Goblin");
            break;
        case 3:
            orc >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Orc");
            break;
        case 4:
            skel >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Skeleton");
            break;
        }
        if (leave == -1)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    //Makes a copy of the player's health for the fight as well as gets info for the boss based on room number and the next rooms are null
    int bossRoom(int type)
    {
        int leave = 0;
        int Eattack, Ehealth;
        ifstream dragon("boss/dragon.txt");
        ifstream beholder("boss/beholder.txt");
        ifstream cyclops("boss/cyclops.txt");
        ifstream minotaur("boss/minotaur.txt");
        switch (type)
        {
        case 1:
            minotaur >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Minotaur");
            break;
        case 2:
            dragon >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Dragon");
            break;
        case 3:
            beholder >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Beholder");
            break;
        case 4:
            cyclops >> Eattack >> Ehealth;
            leave = battle(Ehealth, Eattack, health, "Cyclops");
            break;
        }
        if (leave == -1)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }

    //The player can go left or right if the next node is not null or they can leave
    int enterDungeon(BTnode *root)
    {
        int room = root->data;
        int direction;

        if (root->right != nullptr && root->left != nullptr)
        {
            switch (room)
            {
            case 0:
                system("cls");
                direction = entranceRoom();
                break;
            case 1:
                system("cls");
                direction = emptyRoom();
                break;
            default:
                system("cls");
                if (mobRoom(room) == -1)
                {
                    direction = -1;
                    break;
                }
                direction = emptyRoom();
                break;
            }
        }

        else if (root->right == nullptr && root->left == nullptr)
        {
            bossRoom(room);
            savePlayer();
            return 0;
        }

        switch (direction)
        {
        case 0:
            return enterDungeon(root->left);
            break;
        case 1:
            return enterDungeon(root->right);
            break;
        default:
            system("cls");
            savePlayer();
            break;
        }
        return 0;
    }

public:

    //This function draws a line to make the UI look neater
    void drawLine()
    {
        for (int i = 0; i < 120; i++)
        {
            cout << "-";
        }
        cout << endl;
    }

    // Writes the variable back to the character text file
    void savePlayer()
    {
        ofstream file("Characters/" + player + ".txt");
        file << health << " " << armor << " " << money << endl
             << arrows << " " << BHarrows << " " << Marrows << endl
             << Bstrength << " " << accuracy << endl
             << Wpot << " " << Apot << " " << Mpot << endl;
        file.close();
    }

    void getPlayerInfo(string name)
    {
        ifstream file("Characters/" + name + ".txt");
        player = name;
        file >> health >> armor >> money >> arrows >> BHarrows >> Marrows >> Bstrength >> accuracy >> Wpot >> Apot >> Mpot;
    }

    //Lets the player choose the length of the dungeon
    void DunType()
    {
        int Choice;

        cout << "What size dungeon would you like to explore?" << endl;
        cout << "1. Small" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Large" << endl;
        cin >> Choice;
        Choice = intcheck(1, 3, Choice);

        switch (Choice)
        {
        case 1:
            genDungeon(1, 4, root);
            enterDungeon(root);
            break;
        case 2:
            genDungeon(1, 5, root);
            enterDungeon(root);
            break;
        case 3:
            genDungeon(1, 6, root);
            enterDungeon(root);
            break;
        default:
            break;
        }
    }

    Dungeon() {}
};
