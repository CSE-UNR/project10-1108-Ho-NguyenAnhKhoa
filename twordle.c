 //
//Name: twordle.c
//Purpose:  The program used find guesses a 5 letter world with feedback and hint.
//Author: Nguyen Anh Khoa Ho
//

#include <stdio.h>
#include <stdbool.h>

#define WORD_SIZE 5
#define MAX_GUESSES 6

void uploadFile(char word[]);
bool isValidGuess(char guess[]);
void toLowerCase(char str[]);
int findLetter(char word[], char letter);
void compareGuess(char guess[], char word[], char result[], char pointer[]);
void displayGuess(char results[][WORD_SIZE + 1], char pointers[][WORD_SIZE + 1], int count);
bool isWin(char result[]);
void printCentered(char str[]);

int main() {
    char word[WORD_SIZE + 1];
    char guess[100];

    char results[MAX_GUESSES][WORD_SIZE + 1];
    char pointers[MAX_GUESSES][WORD_SIZE + 1];

    int count = 0;
    bool win = false;

    uploadFile(word);
    toLowerCase(word);

    while (count < MAX_GUESSES && !win) {
        if (count == MAX_GUESSES - 1) {
            printf("FINAL GUESS: ");
        } else {
            printf("GUESS %d! Enter your guess: ", count + 1);
        }

        scanf("%99s", guess);
        toLowerCase(guess);

        while (!isValidGuess(guess)) {
            printf("Your guess must be 5 letters long and contain only letters.\n");
            printf("Please try again: ");
            scanf("%99s", guess);
            toLowerCase(guess);
        }

        compareGuess(guess, word, results[count], pointers[count]);

        printf("==============================\n");
        displayGuess(results, pointers, count + 1);

        win = isWin(results[count]);
        count++;
    }

    if (win) {
        if (count == 1) {
            printCentered("You won in 1 guess!");
            printCentered("GOATED!");
        } else {
            printf("      You won in %d guesses!\n", count);

            if (count == 2 || count == 3) {
                printCentered("Amazing!");
            } else if (count == 4 || count == 5) {
                printCentered("Nice!");
            }
        }
    } else {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

//Read the mystery word from word.txt  
void uploadFile(char word[]) {
    FILE *file = fopen("word.txt", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        word[0] = '\0';
        return;
    }

    fscanf(file, "%5s", word);
    word[WORD_SIZE] = '\0';

    fclose(file);
}

//Check if the guess is exactly 5 letters 
bool isValidGuess(char guess[]) {
    int i = 0;

    while (guess[i] != '\0') {
        if ((guess[i] < 'a' || guess[i] > 'z') &&
            (guess[i] < 'A' || guess[i] > 'Z')) {
            return false;
        }
        i++;
    }

    return i == WORD_SIZE;
}

//Convert  to lowercase 
void toLowerCase(char str[]) {
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
        }
        i++;
    }
}

// Find where a letter appears in the word 
int findLetter(char word[], char letter) {
    for (int i = 0; i < WORD_SIZE; i++) {
        if (word[i] == letter) {
            return i;
        }
    }

    return -1;
}

// Compare the guess with the mystery word  
void compareGuess(char guess[], char word[], char result[], char pointer[]) {
    for (int i = 0; i < WORD_SIZE; i++) {
        result[i] = guess[i];
        pointer[i] = ' ';
    }

    for (int i = 0; i < WORD_SIZE; i++) {
        if (guess[i] == word[i]) {
            result[i] = guess[i] - 32;
        }
    }

    for (int i = 0; i < WORD_SIZE; i++) {
        int position = findLetter(word, guess[i]);

        if (result[i] >= 'A' && result[i] <= 'Z') {
            pointer[i] = ' ';
        } else if (position != -1 && guess[position] != word[position]) {
            pointer[i] = '^';
        } else {
            pointer[i] = ' ';
        }
    }

    result[WORD_SIZE] = '\0';
    pointer[WORD_SIZE] = '\0';
}

//Display all previous guesses 
void displayGuess(char results[][WORD_SIZE + 1], char pointers[][WORD_SIZE + 1], int count) {
    for (int i = 0; i < count; i++) {
        printf("%s\n", results[i]);

        bool hasPointer = false;

        for (int j = 0; j < WORD_SIZE; j++) {
            if (pointers[i][j] == '^') {
                hasPointer = true;
            }
        }

        if (hasPointer) {
            printf("%s\n", pointers[i]);
        }

        printf("\n");
    }
}

//Check all letters are correct 
bool isWin(char result[]) {
    for (int i = 0; i < WORD_SIZE; i++) {
        if (result[i] < 'A' || result[i] > 'Z') {
            return false;
        }
    }

    return true;
}

// Display the result to center 
void printCentered(char str[]) {
    int len = 0;

    while (str[len] != '\0') {
        len++;
    }

    int spaces = (30 - len) / 2;

    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }

    printf("%s\n", str);
}
