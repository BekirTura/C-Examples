#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char charset[62];
char password[8];
int charsetLength;
long int attemptCount = 0;
char passwordCandidate[8];

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
            passwordCandidate[position] = charset[i];
            bruteForce(length, position + 1);
        };
    };
}

void generateCharset (int level) {
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

void generatePassword (int length) {
    int i, randomNumber;
    for (i = 0; i < length; i++) {
        randomNumber = rand() % charsetLength;
        password[i] = charset[randomNumber];
    };
}

int main (void) {
    unsigned int level, length, who, control, i;
    srand((unsigned int) time(NULL));
    do {
        printf("Select difficulty level.\nDigits only(1)\nLowercase chars only(2)\nDigits and lowercase chars(3)\n\
Digits, lowercase and uppercase chars(4)\n");
        scanf("%1ud", &level);
        printf("Length of the password? (4,6 or 8)\n");
        scanf("%1ud", &length);
        printf("User input(1) or randomly generated password(2)?\n");
        scanf("%1ud", &who);
    } while ((level > 5 || level < 1) || !(length == 4 || length == 6 || length == 8) || !(who == 1 || who == 2));
    generateCharset(level);
    if (who == 1) {
        do {
            scanf("%9s", password);
            control = 0;
            for (i = 0; i < length; i++) {
                if (strchr(charset, password[i]) != '\0') {
                    control = 1;
                };
            };
        } while (strlen(password) != length && control == 1);
    } else if (who == 2) {
    generatePassword(length);
    };
    printf("Initial password is: %s\n", password);
    printf("Cracking...\n");
    bruteForce(length, 0);
    return 0;
}
