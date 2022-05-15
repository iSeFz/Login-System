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
            registration();
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

// Check for the correct format of the user's name
string& nameCheck(string& name){
    // Get the name to check for the correct format
    while(true){
        cout << "Enter username: ";
        cin.clear();
        getline(cin, name);
        // Check for the regular expression of names
        regex validName("^[a-zA-Z-_.]+{4,}$");
        if(!regex_match(name, validName)){
            cerr << "########## INVALID username format ##########\n";
            cout << "Username must be: At least 4 characters.\n"
                    "ONLY upper and lowercase letters.\n"
                    "Underscore(_), period(.) or hyphen(-)!\n";
            continue;
        }
        else{
            return name;
        }
    }
}

// Check for the correct format of the user's email
string& emailCheck(string& email){
    copyData(DATA);
    // Get the email to check for the correct format
    while(true){
        cout << "Enter email: ";
        cin.clear();
        getline(cin, email);
        // Check for the regular expression of standard email
        regex validEmail("^[\\w#!%$&+*-/=?.]+@([\\w-]+\\.)+([\\w-]{2,4})*$");
        if(!regex_match(email, validEmail)){
            cerr << "########## INVALID email format ##########\n";
            continue;
        }
        else{
            for(int i = 3; i < DATA.size(); i += 4){
                if(email == DATA[i]){
                    cerr << "########## This email is already registered! ##########\n";
                    cout << "Please use another email.\n";
                    return emailCheck(email);
                }
            }
            return email;
        }
    }
}

// Check for the correct format of phone number
string& phoneCheck(string& phone){
    // Get the phone number to check for the correct format
    while(true){
        cout << "Enter phone number: ";
        cin.clear();
        getline(cin, phone);
        // Check for the regular expression of egyptian phone numbers
        regex validPhoneNum("^01[0125][0-9]{8}$");
        if(!regex_match(phone, validPhoneNum)){
            cerr << "########## INVALID phone number ##########\n";
            cout << "Phone number must be: ONLY 11 digit numbers\n"
                    "Starting with 010, 011, 012 or 015!\n";
            continue;
        }
        else{
            return phone;
        }
    }
}

// Register new profile to the system
void registration(){
    cout << "---------- Register new user ----------\n";
    string name, email, phone, pass;
    // Check the inputs of the user
    nameCheck(name);
    emailCheck(email);
    phoneCheck(phone);
    UserData user(pass, name, email, phone);
    cout << "Welcome " << user.userName << "! You've registered successfully!\n";
    // Store the newly registered user data to the profiles system
    ofstream dataBase(DB, ios::app);
    dataBase << user;
    dataBase.close();
    cout << "---------------------------------------\n";
}
