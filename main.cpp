// @author Michael Yeung
// @since April 15, 2024
// Runs a fun game of Hangman on the console
#include <iostream> //input/output
#include <fstream> //file stream
#include <string>
#include <array>
#include <stdlib.h>  //rand
#include <ctype.h> //character utilities

using namespace std;    

string key;
int MAX_GUESSES = 9;

//returns a random word from words.txt
string getWord() {
    ifstream inFile;
    inFile.open("words.txt");
    
    int counter = 0;
    string key = "";
    /* initialize random seed: */
    srand(time(NULL));
    
    /* generate secret number between 0 and 9999: */
    int index = rand() % 10000;

    while(getline(inFile, key)) {
        if (index == counter)
            return key;
        counter++;
    }
    return "";

}

void runner() {
    //creates an array that stores correct user guesses, default '-'
    char progress[key.length()];
    for (int i = 0; i < key.length(); i++) {
        progress[i] = '-';
    }
    //array of hangman pieces
    char hangman[MAX_GUESSES] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    
    //array of letters, false by default
    bool letGuessed[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //starts the prompts
    int numWrongGuess = 0;
    string guess = "";
    bool valid = false; //char is valid
    bool done = false; //word is guessed correctly
    char guessChar; //guess in char data type
    
    cout << "Welcome to Hangman!" << endl;

    while (numWrongGuess < MAX_GUESSES && !done) { //User only has set amt of lives
        valid = false;
        done = true;

        do { //keeps going until user's guess is a single letter
            cout << "Here's the word: ";
            for (int i = 0; i < sizeof progress; i++) 
                cout << progress[i];
                
            cout << "\nWhat's your best letter? "; //check to make sure it is a char
            cin >> guess;
            
            guessChar = guess.at(0);
            guessChar = tolower(guessChar);
            
            if (guess.length() != 1 || !isalpha(guessChar))
                cout << "The guess has to be one letter. Try again.\n" << endl;
            else if (letGuessed[guessChar - 97])
                cout << "You already guessed this letter. Try again.\n" << endl;
        } while (guess.length() != 1 || !isalpha(guessChar) || letGuessed[guessChar - 97]);
        
        //processes guess
        letGuessed[guessChar - 97] = true;
        
        for (int i = 0; i < key.length(); i++) {
            if (key.at(i) == guessChar) {
                progress[i] = guessChar;
                valid = true;
            }
            if (progress[i] == '-') {
                done = false;
            }
        }
        if (!valid) {
            numWrongGuess++;
            cout << guessChar << " is not in the word." << endl;
        }

        //makes sure that you can't do same letter , array of all letters
        
        
        //update hangman parts
        if (numWrongGuess == 1)
            hangman[numWrongGuess - 1] = '|';
        else if (numWrongGuess == 2)
            hangman[numWrongGuess - 1] = 'O';
        else if (numWrongGuess == 3)
            hangman[numWrongGuess - 1] = '_';
        else if (numWrongGuess == 4)
            hangman[numWrongGuess - 1] = '_';
        else if (numWrongGuess == 5)
            hangman[numWrongGuess - 1] = '/';
        else if (numWrongGuess == 6)
            hangman[numWrongGuess - 1] = '\\';
        else if (numWrongGuess == 7)
            hangman[numWrongGuess - 1] = '|';
        else if (numWrongGuess == 8)
            hangman[numWrongGuess - 1] = '/';
        else if (numWrongGuess == 9)
            hangman[numWrongGuess - 1] = '\\';
        
        //print result
        cout << "   " << hangman[0] << "   " << endl;
        cout << "  " << hangman[2] << hangman[1] << hangman[3] << endl;
        cout << " " << hangman[4] << " " << hangman[6] << " " << hangman[5] << "  " << endl;
        cout << "  " << hangman[7] << " " << hangman[8] << "  " << endl;
    }
    
    //finishing message
    if (done) {
        cout << "Congratulations! You guessed the word " << key << " with just " << numWrongGuess << " wrong guesses!";
    }
    else {
        cout << "The word was " << key << ". Better luck next time!";
    }
}
int main() {
    key = getWord(); //gets the key word
    runner(); //runs the game
}