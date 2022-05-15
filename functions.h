// functions.h content

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

#endif