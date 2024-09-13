#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Function 1
int inputInt(void) {
    int result;
    char a;
    do {
        scanf("%d%c", &result, &a);
        if (a != '\n') {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (a != '\n');
    return result;
}

//Function 2
int inputIntPositive(void) {
    int result;
    do {
        result = inputInt();
        if (result <= 0) {
            printf("ERROR! Value must be > 0: ");
        }
    } while (result <= 0);
    return result;
}

//Function 3
int inputIntRange(int from, int to) {
    int result;
    do {
        result = inputInt();
        if (result < from || result > to) {
            printf("ERROR! Value must be between %d and %d inclusive: ", from, to);
        }
    } while (result < from || result > to);
    return result;
}

//Function 4
char inputCharOption(const char string[]) {
    char result;
    int i,valid = 0;
    do {
        scanf("%c", &result);
        clearInputBuffer();
        
        for (i=0; string[i] != '\0'; i++) {
            if (result == string[i]) {
                valid = 1;
            }
        }
        if (valid == 0) {
            printf("ERROR: Character must be one of [%s]: ", string);
        }
        
    } while (valid != 1);
    
    return result;
}

//Function 5
void inputCString(char* string, int min_char, int max_char) {
    int count;
    char tempString[100] = { '\0' };
    do {
        scanf("%[^\n]", tempString);
        clearInputBuffer();
        
        count = (int)strlen(tempString);
        
        if (count < min_char || count > max_char) {
            if (min_char == max_char) {
                printf("Invalid 10-digit number! Number: ");
            } else if (count > max_char){
                printf("ERROR: String length must be no more than %d chars: ", max_char);
            } else {
                printf("ERROR: String length must be between %d and %d chars: ", min_char, max_char);
            }
        }
    } while (count < min_char || count > max_char);
    
    strcpy(string, tempString);

}

//Function 6
void displayFormattedPhone(const char* phoneNumber){
    int i, count=0, IsDigit=1;
    
    if (phoneNumber != NULL) {
        // is it 10 digits?
        
        count = (int)strlen(phoneNumber);
        
        // is the characters digit?
        for (i=0; i<10; i++) {
            if (phoneNumber[i] < 48 || phoneNumber[i] > 57) {
                IsDigit = 0;
            }
        }
    }
    
    if (IsDigit == 1 && count == 10 && phoneNumber != NULL) {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", phoneNumber[0], phoneNumber[1], phoneNumber[2], phoneNumber[3], phoneNumber[4], phoneNumber[5], phoneNumber[6], phoneNumber[7], phoneNumber[8], phoneNumber[9]);
    } else {
        printf("(___)___-____");
    }
    
    
    
}
