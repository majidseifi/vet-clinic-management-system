#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Function 1
int inputInt(void);

//Function 2
int inputIntPositive(void) ;

//Function 3
int inputIntRange(int, int) ;

//Function 4
char inputCharOption(const char[]);

//Function 5
void inputCString(char*, int, int);

//Function 6
void displayFormattedPhone(const char*);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

#endif // !CORE_H
