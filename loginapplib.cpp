// These are all the functions of the program from which
// the user choose one or more to apply to the file

#include <iostream>
#include <string>
#include <regex>
#include "functions.h"

using namespace std;

// Display the main menu for the user to choose from
void start(){
    string choice;
    while(choice != "4"){
        cout << "What do you want to do?\n"
                "1- Register\n2- Login\n"
                "3- Change Password\n4- Exit\n";
        cout << "Choose one of the above options: ";
        cin.clear();
        getline(cin, choice);
        if(choice == "1"){
            ; // some function
        }
        else if(choice == "2"){
            ; // some function
        }
        else if(choice == "3"){
            ; // some function
        }
        else if(choice == "4"){
            break;
        }
        else{
            cerr << "\nINVALID INPUT! Enter only numbers from 1 to 4.\n";
            continue;
        }
    }
    cout << "Thank You for using the Login Application!\n";
}
