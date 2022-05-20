// These are all the functions of the program from which
// the user choose one or more to apply to the file

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <conio.h>

using namespace std;

#include "functions.h"

// Display the main menu for the user to choose from
void start(){
  	string choice;
    while(choice != "4"){
        cout << "\nWhat do you want to do?\n"
                "1- Register\n2- Login\n"
                "3- Change Password\n4- Exit\n";
        cout << "Choose one of the above options: ";
        cin.clear();
        getline(cin, choice);
        if(choice == "1")
            registration();
        else if(choice == "2")
            login();
        else if(choice == "3")
            changePass();
        else if(choice == "4")
            break;
        else{
            cerr << "########## INVALID INPUT! ##########\n";
            cout << "Enter ONLY numbers from 1 to 4.\n";
            continue;
        }
      	DATA.clear();
      	copyData(DATA);
    }
    cout << "\t\t\tThank You for using the Login Application!\n";
    return;
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

// Overload the fstream operator to write all user data into files
ofstream& operator << (ofstream& app, UserData user){
    app << user.userPass << '~' << user.userName << '~';
    app << user.userPhone << '~' << user.userEmail << '~' << endl;
    return app;
}

// Overload the fstream operator to upadate files with current vector data
ofstream& operator << (ofstream& out, vector<string> data){
    for(int i = 0, k = 1; i < data.size() - 1; i++, k++){
        if(k == 4){
            k = 0;
            out << data[i] + "~\n";
        }
        else
            out << data[i] + '~';
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
  	DATA.clear();
    copyData(DATA);
    // Get the name to check for the correct format
    while(true){
        cout << "Enter username/ID: ";
        cin.clear();
        getline(cin, name);
        // Check for the regular expression of names
        regex validName("^[\\w-.]+{4,}$");
        if(!regex_match(name, validName)){
            cerr << "########## INVALID username format ##########\n";
            cout << "Username must be: At least 4 characters.\n"
                    "ONLY upper and lowercase letters.\n"
                    "Underscore(_), period(.) or hyphen(-)!\n";
            continue;
        }
        else{
          	for(int i = 1; i < DATA.size(); i += 4){
                if(name == DATA[i]){
                    cerr << "########## Username is already registered! ##########\n";
                    cout << "Please use ANOTHER username!\n";
                    return nameCheck(name);
                }
            }
            return name;
        }
    }
}

// Check for the correct format of the user's email
string& emailCheck(string& email){
    DATA.clear();
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
                    cerr << "########## Email is already registered! ##########\n";
                    cout << "Please use ANOTHER email!\n";
                    return emailCheck(email);
                }
            }
            return email;
        }
    }
}

// Check for the correct format of phone number
string& phoneCheck(string& phone){
  	DATA.clear();
    copyData(DATA);
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
          	for(int i = 2; i < DATA.size(); i += 4){
                if(phone == DATA[i]){
                    cerr << "########## Phone is already registered! ##########\n";
                    cout << "Please use ANOTHER phone!\n";
                    return phoneCheck(phone);
                }
            }
            return phone;
        }
    }
}

// Check for the correct format of the user's password
string& passwordCheck(string& password){
    DATA.clear();
    copyData(DATA);
    // Get the password to check for the correct format
    while(true){
        cout << "Enter your password: ";
        hidePass(password);
        // Check for the regular expression of standard password
        regex validPassword("^(?=.+[0-9])(?=.+[a-zA-Z])(?=.+[!@#$&*]).{8,16}$");
        if(!regex_match(password, validPassword)){
            cerr << "########## INVALID password format ##########\n";
            cout << "Password must be: At least 8 characters,"
                    " mixture of upper and lowercase letters\n"
                    "At least one number and one special character!\n";
            password = "";
            continue;
        }
        else{
            string password2;
            cout << "Enter password again: ";
            hidePass(password2);
            if(password == password2)
                return password;
            else{
                cerr << "########## Passwords does NOT match! ##########\n";
                password = "";
            }
        }
    }
}

// Encrypt password before storing it
string passEncryption(string& pass, int choice){
    string temp = pass;
    int x;
    pass = "";
    for (auto ch : temp){
        if (isalpha(ch)){
            if (choice == 1)
                x = (5 * lettersMap.at(toupper(ch)) + 8) % 26;
            else
                x = 21 * (lettersMap.at(toupper(ch)) - 8) % 26;
            for (auto el : lettersMap){
                if (el.second == x){
                    if (isupper(ch)){
                        pass += el.first;
                        break;
                    }
                    else{
                        pass += (char)tolower(el.first);
                        break;
                    }
                }
            }
        }
        else
          	pass += ch;  
    }
    return pass;
}

// Register new profile to the system
void registration(){
    if(badUser == 'd'){
        cout << "########## You are DENIED from accessing the system! ##########\n";
        return;
    }
    cout << "\n---------- Register new user ----------\n";
    string name, email, phone, pass;
    // Check the inputs of the user
    nameCheck(name);
    emailCheck(email);
    phoneCheck(phone);
    passwordCheck(pass);
    UserData user(pass, name, email, phone);
    cout << "$$$$$$$$$$ Welcome " << user.userName << "! You've registered successfully! $$$$$$$$$$\n";
    // Store the newly registered user data to the profiles system
    ofstream dataBase(DB, ios::app);
    dataBase << user;
    dataBase.close();
    cout << "---------------------------------------\n";
}

// Check for registered username before or not
int isRegName(){
    string name, ans;
    cout << "Enter your username/ID: ";
    cin.clear();
    getline(cin, name);
    for(int i = 1; i < DATA.size(); i += 4){
        if(name == DATA[i])
            return i;
    }
  	cerr << "########## Username NOT found! Maybe you're NOT registered yet! ##########\n";
    while(true){
        cout << "Would you like to register a profile (y/n)? ";
        cin.clear();
        getline(cin, ans);
        if(ans == "y"){
            registration();
            return 0;
        }
        else if(ans == "n"){
            cout << "-------------------------------------------\n";
            return 0;
        }
        else{
            cerr << "###### Enter ONLY y or n ######\n";
            continue;
        }
    }
}

// Check for password registered before or not
bool isRegPass(int nameIndex){
    string pass;
    hidePass(pass);
    for(int i = 0; i < DATA.size(); i += 4){
    	if(pass == DATA[i]){
      		cout << "$$$$$$$$$$ Successfull Login! Welcome back " << DATA[nameIndex] << "! $$$$$$$$$$\n";
            return true;
    	}
    }
    int count = 3;
    while(count != 0){
        cerr << "########## INVALID PASSWORD ##########\n"
                "You have " << count-- << " remaining attemps!\n";
        cout << "Enter your password AGAIN: ";
        pass = "";
        hidePass(pass);
        for(int i = 0; i < DATA.size(); i += 4){
            if(pass == DATA[i]){
                cout << "$$$$$$$$$$ Successfull Login! Welcome back " << DATA[nameIndex] << "! $$$$$$$$$$\n";
                return true;
            }
        }
    }
  	cout << "########## FAILED Login! You are DENIED from accessing the system! ##########\n";
  	badUser = 'd';
    return true;
}

// Hide password while the user is entering
string hidePass(string& pass){
    char ch;
    ch = getch();
    while(ch != 13){
        if(ch == 8 && pass.size()){
            cout << "\b \b";
            pass.pop_back();
            ch = getch();
            continue;
        }
        cout << '*';
        pass += ch;
        ch = getch();
    }
    cout << endl;
    return passEncryption(pass, 1);
}

// Login an existing account
void login(){
    if(badUser == 'd'){
        cout << "########## You are DENIED from accessing the system! ##########\n";
        return;
    }
  	cout << "\n---------- Login to your account ----------\n";
    int nameIndex;
  	DATA.clear();
    copyData(DATA);
    nameIndex = isRegName();
    if(nameIndex){
      	cout << "Enter your password: ";
        isRegPass(nameIndex);
    }
    else
        return;
    cout << "-------------------------------------------\n";
}

// Change password of an existing account
void changePass(){
    if(badUser == 'd'){
        cout << "########## You are DENIED from accessing the system! ##########\n";
        return;
    }
    cout << "\n---------- Change Password ----------\n";
    int index, count;
    string oldPass, newPass, tempPass;
  	DATA.clear();
    copyData(DATA);
    index = isRegName();
    oldPass = DATA[index - 1];
    cout << "Enter your OLD password: ";
    hidePass(tempPass);
    count = 3;
    while (tempPass != oldPass && count != 0){
        cerr << "########## INVALID PASSWORD ##########\n"
                "You have " << count-- << " remaining attemps!\n";
        cout << "Enter new password AGAIN: ";
        tempPass = "";
        hidePass(tempPass);
    }
    if(tempPass == oldPass){
        cout << "(NEW) ";
        passwordCheck(newPass);
        DATA[index - 1] = newPass;
        ofstream file(DB);
        file << DATA;
        file.close();
      	cout << "$$$$$$$$$$ Password CHANGED successfully! $$$$$$$$$$\n";
    }
    else
        cerr << "########## Changing password FAILED! Try Again Later ##########\n";
    cout << "-------------------------------------\n";
}
