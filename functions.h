#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Here we will put function prototypes

// Declare data vector to copy the database file into
vector <string> DATA;

// Declare database text file
char DB[] = "database.txt";

// Display the main menu for the user to choose from
void start();

// Copy data from file into a vector
void copyData(vector<string>&);

// Check for the correct format of the user's name
string& nameCheck(string&);

// Check for the correct format of the user's email
string& emailCheck(string&);

// Check for the correct format of phone number
string& phoneCheck(string&);

// Register new profile to the system
void registration();

#endif