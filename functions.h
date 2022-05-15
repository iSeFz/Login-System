#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Here we will put function prototypes

// Declare data vector to copy the database file into
vector <string> DATA;

// Declare database text file
char DB[] = "database.txt";

// Declare map of characters
map <char, int> lettersMap{
    {'A',0},{'B',1},{'C',2},{'D',3},{'E',4},
    {'F',5},{'G',6},{'H',7},{'I',8},{'J',9},
    {'K',10},{'L',11},{'M',12},{'N',13},{'O',14},
    {'P',15},{'Q',16},{'R',17},{'S',18},{'T',19},
    {'U',20},{'V',21},{'W',22},{'X',23},{'Y',24},{'Z',25}
};

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

// Check for the correct format of the user's password
string& passwordCheck(string&);

// Encrypt password before storing it
string passEncryption(string&, int);

// Register new profile to the system
void registration();

// Check for registered username before or not
int isRegName();

// Check for password registered before or not
bool isRegPass();

// Hide password while the user is entering
string hidePass(string&);

// Login to an existing account
void login();

#endif
