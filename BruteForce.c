/**
@file
BBG2 Spring 2014 Assignment #1
A program that cracks a given password using a bruteforce attack.
It prints cracked password and amount of attempts to find it.
@author
Name: H. Tuğkan Kibar
Student no: 13011064
Date: 15/03/2014
E-Mail: htugkankibar@gmail.com
Compiler used: GCC
IDE: Code::Blocks
Operating System: Elementary OS Luna (0.2)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char charset[62];
char password[8];
int charsetLength;
long int attemptCount = 0;
char passwordCandidate[8];

/**
    Cracks password recursively.

    Creates instances of itself to generate and test different password candidates.
    When password and candidate matches, prints it out and terminates the program.

    @param Length of the password.
    @param Indicates which character slot of passwordCandidate variable is to be filled.
    @return This function returns nothing.
*/
void bruteForce(int length, int position) {
    if (position == length) {
        if (strcmp(password, passwordCandidate) == 0) {
            printf("Crack complete.\nPassword: %s\nAttempt count: %ld\n", passwordCandidate, ++attemptCount);
            exit(0);
        } else {
            attemptCount++;
        };
    } else {
        int i;
        for (i = 0; i < charsetLength; i++) {
            //By calling itself again and again and changing the position every time generates passwords sequentially.
            passwordCandidate[position] = charset[i];
            bruteForce(length, position + 1);
        };
    };
}

/**
    Generates a charset of allowed characters depending on the level.

    @param Difficulty level of the password.
    @return This function returns nothing.
*/
void generateCharset (int level) {
    //TODO: Find an able alternative for strlen() function that can handle multibyte characters and add turkish characters to charsets.
    switch (level) {
        case 1:
            strcpy(charset, "0123456789");
            break;
        case 2:
            strcpy(charset, "abcdefghijklmnoprstuvyzqwx");
            break;
        case 3:
            strcpy(charset, "0123456789abcdefghijklmnoprstuvyzqwx");
            break;
        case 4:
            strcpy(charset, "0123456789ABCDEFGHIJKLMNOPRSTUVYZQWXabcdefghijklmnoprstuvyzqwx");
            break;
    };
    charsetLength = strlen(charset);
}

/**
    Generates a random password using charset that was set by generateCharset().

    @param Length of the password.
    @return This function returns nothing.
*/
void generatePassword (int length) {
    int i, randomNumber;
    //Add a character to the password one by one from charset of legal chars.
    for (i = 0; i < length; i++) {
        randomNumber = rand() % charsetLength;
        password[i] = charset[randomNumber];
    };
}

/**
    Main function of the program.

    Takes needed inputs until they are usable.
    Makes sure inputs are not flawed and calls other functions according to these inputs.
*/
int main (void) {
    unsigned int level, length, who, control, i;
    srand((unsigned int) time(NULL));
    //Take inputs for difficulty level, password length and password source. Check if they are usable. If not ask again.
    do {
        printf("Select difficulty level.\nDigits only(1)\nLowercase chars only(2)\nDigits and lowercase chars(3)\n\
Digits, lowercase and uppercase chars(4)\n");
        scanf("%1ud", &level);
        printf("Length of the password? (4,6 or 8)\n");
        scanf("%1ud", &length);
        printf("User input(1) or randomly generated password(2)?\n");
        scanf("%1ud", &who);
    } while ((level > 5 || level < 1) || !(length == 4 || length == 6 || length == 8) || !(who == 1 || who == 2));
    //Generate a charset of allowed characters.
    generateCharset(level);
    //Depending to the who parameter, take an unflawed input from user and check its legality or call generatePassword() to randomly generate a password.
    if (who == 1) {
        do {
            printf("Enter password to be cracked.\n");
            scanf("%9s", password);
            control = 0;
            for (i = 0; i < length; i++) {
                if (strchr(charset, password[i]) != '\0') { //Checks if there are any unwanted characters.
                    control = 1;
                };
            };
        } while (strlen(password) != length && control == 1);
    } else if (who == 2) {
    generatePassword(length);
    };
    printf("Initial password is: %s\n", password);
    printf("Cracking...\n");
    //Crack the password.
    bruteForce(length, 0);
    return 0;
}
