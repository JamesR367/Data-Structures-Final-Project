#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <string>
#include "town.cpp"

using namespace std;
using namespace std::filesystem;

class Menus
{
private:
    //This function allows the player to delete any character file by typing it in
    void deleteCharacter()
    {
        string filelocation;
        string searchfilename;
        string path = "Characters/";
        cout << "Please enter the name of the character you want to delete or hit 3 to go back:" << endl;

        for (const auto &file : directory_iterator(path))
        {
            filelocation = file.path().string();
            filelocation.erase(0, 11);
            filelocation.erase(filelocation.end() - 4, filelocation.end() - 0);
            if (filelocation == "Enemy")
            {
                ;
            }
            else
            {
                cout << filelocation << endl;
            }
        }

        cin >> searchfilename;

        if (searchfilename == "3")
        {
            return;
        }
        else if (remove("Characters/" + searchfilename + ".txt"))
        {
            cout << "Your character " << searchfilename << " has been deleted." << endl;
        }
        else
        {
            cout << "Character " << searchfilename << " not found." << endl;
        }
    }

    // This allows the player to create a new character if it doesn't already exist
    string createCharacter()
    {
        string Name, fileName;
        try
        {
            cout << "Choose your character's name" << endl;
            cin >> Name;

            fileName = Name + ".txt";

            if (filesystem::exists("Characters/" + fileName))
            {
                throw(Name);
            }
            else
            {
                ofstream file("Characters/" + fileName);
                file << 10 << " " << 25 << " " << 0 << endl
                     << 15 << " " << 0 << " " << 0 << endl
                     << 1 << " " << 45 << endl
                     << 1 << " " << 0 << " " << 0 << endl;
                file.close();
            }
        }
        catch (string name)
        {
            while (filesystem::exists("Characters/" + fileName))
            {
                clearInput();
                cout << "This character name already exists, please choose another" << endl;
                cin >> name;
                Name = name;
                fileName = Name + ".txt";
            }

            ofstream file("Characters/" + fileName);
            file << 10 << " " << 25 << " " << 0 << endl
                 << 15 << " " << 0 << " " << 0 << endl
                 << 0 << " " << 45 << endl
                 << 1 << " " << 0 << " " << 0 << endl;
            file.close();
        }

        return Name;
    }

    //This function shows a list of character that the player can choose from
    string chooseCharacter()
    {
        string Name;
        string path = "Characters/";
        string filelocation;

        cout << "What is the character's name" << endl;

        for (const auto &file : directory_iterator(path))
        {
            filelocation = file.path().string();
            filelocation.erase(0, 11);
            filelocation.erase(filelocation.end() - 4, filelocation.end() - 0);
            if (filelocation == "Enemy")
            {
                ;
            }
            else
            {
                cout << filelocation << endl;
            }
        }
        cout << " " << endl;
        cin >> Name;
        if (exists("Characters/" + Name + ".txt") && Name != "Enemy")
        {
            return Name;
        }

        while (!exists("Characters/" + Name + ".txt") || Name == "Enemy")
        {
            clearInput();
            cout << "Character does not exist please choose from the list:" << endl;
            for (const auto &file : directory_iterator(path))
            {
                filelocation = file.path().string();
                filelocation.erase(0, 11);
                filelocation.erase(filelocation.end() - 4, filelocation.end() - 0);
                if (filelocation == "Enemy")
                {
                    ;
                }
                else
                {
                    cout << filelocation << endl;
                }
            }
            cin >> Name;
        }
        return Name;
    }

    void clearInput()
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }

public:
    //This function starts the game by asking the player to either choose or create a character
    void characterMenu()
    {
        int Choice, count;
        string Name;
        string path = "Characters";
        Game game;
        while (Choice != 3)
        {
            try
            {
                cout << "1. Create new character"
                     << "\n2. Choose a character"
                     << "\n3. Back" << endl;
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
                    cout << "1. Create new character"
                         << "\n2. Choose a character"
                         << "\n3. Back" << endl;
                    cin >> choice;
                }
                Choice = choice;
            }

            switch (Choice)
            {
            case 1:
                Name = createCharacter();
                system("cls");
                game.getPlayerInfo(Name);
                game.town();
                break;
            case 2:
                try
                {
                    for (const auto &file : directory_iterator(path))
                    {
                        count++;
                    }
                    if (count <= 1)
                    {
                        throw("empty");
                    }

                    else
                    {
                        Name = chooseCharacter();
                        system("cls");
                        game.getPlayerInfo(Name);
                        game.town();
                    }
                }
                catch (...)
                {
                    cout << "No characters have been created" << endl;
                }
                break;
            default:
                break;
            }
        }
        system("cls");
    }

    void optionsMenu()
    {
        string Text;
        int Choice;
        ifstream MyReadFile("HTP.txt");
        cout << "Options Menu" << endl;
        while (Choice != 3)
        {
            try
            {
                cout << "1. How to play"
                     << "\n2. Delete characters"
                     << "\n3. Back" << endl;
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
                    cout << "1. How to play"
                         << "\n2. Delete characters"
                         << "\n3. Back" << endl;
                    cin >> choice;
                }
                Choice = choice;
            }

            switch (Choice)
            {
            // Reads from the how to play text file
            case 1:
                system("cls");
                cout << " " << endl;
                while (getline(MyReadFile, Text))
                {
                    cout << Text << endl;
                }
                cout << " " << endl;
                break;
            case 2:
                deleteCharacter();
                break;
            default:
                break;
            }
        }
        system("cls");
    }

    Menus() {}
};
