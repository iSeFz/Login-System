// These are all the functions of the program from which
// the user choose one or more to apply to the file

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

#include "functions.h"

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
            cerr << "########## INVALID INPUT! ##########\n";
            cout << "Enter ONLY numbers from 1 to 4.\n";
            continue;
        }
    }
    cout << "Thank You for using the Login Application!\n";
}

// Create structure to register new user
struct UserData{
  	string userEmail;  
  	string userName;
  	string userPhone;
    string userPass;
  	UserData(string, string, string, string);
};

// Constructor function to assign each element of info of the user
UserData::UserData(string pass, string name, string email, string phone){
    userPass = pass;
    userName = name;
    userEmail = email;
    userPhone = phone;
}

// Overload the ostream operator to output all user data
ostream& operator << (ostream& out, UserData user){
  	out << "---------- New registered profile data ----------\n";
    out << "User Name: " << user.userName << endl;
    out << "Email: " << user.userEmail << endl;
  	out << "Phone number: " << user.userPhone << endl;
  	out << "-------------------------------------------------\n";
    return out;
}

// Overload the fstream operator to write all user data into files
ofstream& operator << (ofstream& app, UserData user){
    app << user.userName << '~' << user.userPass << '~';
    app << user.userPhone << '~' << user.userEmail << '~' << endl;
    return app;
}

// Overload the fstream operator to upadate files with current vector data
ofstream& operator << (ofstream& out, vector<string> data){
    for(int i = 0, k = 1; i < data.size(); i++, k++){
        if(k == 4){
            k = 0;
            out << data[i] << "~\n";
        }
        else{
            out << data[i] << '~';
        }
    }
    return out;
}

// Copy data from file into a vector
void copyData(vector <string>& vector){
	ifstream file(DB);
  	string line;
  	while(getline(file, line, '~')){
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    	vector.push_back(line);
    }
    file.close();
}
