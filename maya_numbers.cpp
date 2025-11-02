#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
#include <ios>
#include <vector>

using namespace std;

// Global constant for the base 20 and Mayan representation of numbers
const int BASE = 20;
// Global constant for array of 3 game choices a, b and c
const int ARR_SIZE = 3;

// Function Prototypes
int powerCounter(int number);
void numberToMayan(int number);
void printMayanNumber(int number);
int guessNumberGame(int number);

int main() {

    // Seed random number generator once at program start
    srand(time(NULL));

    // Mayan representation of 5212
    cout << "The Mayan representation of 5,212 is: " << endl << endl;
    printMayanNumber(5212);
    cout << endl;

    // Call the game function in main function
    int number = 0;
    guessNumberGame(number);

}

// Counts how many powers of 20 are in the number
int powerCounter(int number) {
    // Initialize variable for exponent of base
    int exponent = 0;
    // Keep dividing by 20 base to give how many times the number goes into 20
    while (number >= 20) {
        number /= BASE; // Keep dividing by 20 base to give how many times the number goes into 20
        exponent++;
    }
    return exponent;
}

// Convers numbers to mayan representations
void numberToMayan(int userInput) {

    // Method of storing mayan representations, I used @ as the shell for zero as it looks better
    string mayanRepresentation[6] = { "    @","    o","   oo","  ooo"," oooo"," ====" };

    // Initialize variable for checking the ones and fives place
    int ones = userInput % 5;

    // If there are dashes only, ie. number is evenly divisible by five
    if (ones == 0 && userInput >= 5) {
        while (userInput >= 5) {
            userInput -= 5;
            cout << mayanRepresentation[5] << endl;
        }
    }
    // If there are dots and dashes, ie. there's a remainder after dividing by five
    else if (ones != 0 && userInput >= 5) {
        cout << mayanRepresentation[ones] << endl;
        while (userInput >= 5) {
            userInput -= 5;
            cout << mayanRepresentation[5] << endl;
        }
    }
    // If there are only dots, ie. numbers less than five
    else {
        cout << mayanRepresentation[ones] << endl;
    }
}

// Goes through powers of 20 and prints them out as Mayan representation
void printMayanNumber(int userInput) {

    // initialize variable for exponent of base
    int exponent = powerCounter(userInput);
    int remainder; // initialize variable for remainder

    // Print mayan numbers working down from the highest power of base
    for (int i = exponent; i >= 0; i--) {

        // This checks how many powers of 20 go into the number
        remainder = userInput / (pow(BASE, i));
        // Prints the Mayan representation of the number
        numberToMayan(remainder);

        // Subtracts all the powers of 20 in specified spot
        userInput -= ((pow(BASE, i)) * remainder); //

        // If on the last power of 20 , don't print separating line
        if (i != 0) {
            cout << "------" << endl;
        }
    }
}

// Game function for playing Mayan number game
int guessNumberGame(int number) {

    int userInput;          // The guess seed made by user input
    int correctAnswer;      // First random number created using user input as a bound
    int lowerGuess;         // Lower bound for second random number to be created
    int higherGuess;        // Upper bound for third random number to be created

    cout << "Welcome to the Mayan number game!" << endl << endl;

    cout << "Enter a number greater than 10. THe game will choose a number less than "
        << "or equal to what you entered. You will then have to match the decimal numer "
        << "to its Mayan equivalent. Or, enter a number less than 10 to exit: ";
    cin >> userInput;

    // If incorrect input then clear input and reprompt user to enter another guess
    while (cin.fail()) {
        cout << "Wrong input, please enter a number higher than 10: ";
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> userInput;
    }

    // While loop for repeating the game as many times as desired
    while (userInput >= 10) {

        // Initialize random seed
        srand(time(NULL));

        // Correct answer created randomly
        correctAnswer = rand() % userInput;

        // Variables for providing upper and lower bounds on the two wrong guesses
        lowerGuess = correctAnswer * (0.5);
        higherGuess = correctAnswer * (1.5);
        // Build a candidate list of possible wrong answers in the [lowerGuess, higherGuess]
        // excluding the correct answer. If that list is empty (range too small),
        // fall back to the full [0, userInput-1] range excluding the correct answer.
        vector<int> candidates;
        for (int v = lowerGuess; v <= higherGuess; ++v) {
            if (v != correctAnswer && v >= 0 && v < userInput) candidates.push_back(v);
        }
        if (candidates.empty()) {
            for (int v = 0; v < userInput; ++v) {
                if (v != correctAnswer) candidates.push_back(v);
            }
        }

        // If candidates is still empty (possible if userInput <= 1), pick nearby values safely
        if (candidates.empty()) {
            if (correctAnswer > 0) candidates.push_back(correctAnswer - 1);
            else candidates.push_back(correctAnswer + 1);
        }

        // Pick two distinct wrong answers from candidates
        int idx1 = rand() % candidates.size();
        int wrongAnswerOne = candidates[idx1];
        // remove chosen
        candidates.erase(candidates.begin() + idx1);
        if (candidates.empty()) {
            // fill fallback options (shouldn't normally happen)
            for (int v = 0; v < userInput; ++v) if (v != correctAnswer && v != wrongAnswerOne) candidates.push_back(v);
            if (candidates.empty()) candidates.push_back((wrongAnswerOne + 1) % max(1, userInput));
        }
        int idx2 = rand() % candidates.size();
        int wrongAnswerTwo = candidates[idx2];

        // Create an array for randomizing the answers for displaying on screen
        int random[ARR_SIZE] = { correctAnswer, wrongAnswerOne, wrongAnswerTwo };

        // Randomize array
        for (int i = 0; i < ARR_SIZE; i++) {
            // Variable for randomized Index
            int index = rand() % ARR_SIZE;
            // Create temp index and repeat
            int temp = random[i];
            random[i] = random[index];
            random[index] = temp;
        }

        // Display 3 Mayan numbers and ask user for correct answer
        cout << endl << "Which of these Mayan numbers is equal to " << correctAnswer << "?" << endl;

        // Code for displaying 3 options randomly on screen
        cout << endl << "a." << endl;
        printMayanNumber(random[0]);
        cout << endl << "b." << endl;
        printMayanNumber(random[1]);
        cout << endl << "c." << endl;
        printMayanNumber(random[2]);
        cout << endl;

        // Initialize characters for checking input
        char correct;

        // assign characters to correct answer
        if (random[0] == correctAnswer) {
            correct = 'a';
        }
        else if (random[1] == correctAnswer) {
            correct = 'b';
        }
        else if (random[2] == correctAnswer) {
            correct = 'c';
        }

        // Ask user for their guess
        char userGuess;
        cout << "Enter a, b or c: ";
        cin >> userGuess;

        // If incorrect input then clear input and reprompt user to enter another guess
        while ((userGuess != 'a') && (userGuess != 'b') && (userGuess != 'c')) {
            cout << "Wrong input, please Enter a, b or c: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> userGuess;
        }
        cout << endl;

        // If user guess is corrent, print corrent and show the correct represnation
        if (userGuess == correct) {
            cout << "CORRECT! The Mayan represnation of " << correctAnswer << " is: " << endl;
            printMayanNumber(correctAnswer);
            cout << endl;
        }
        // If user guess is incorrect, print incorrect and show the correct representation
        else {
            cout << "INCORRECT! The Mayan represnation of " << correctAnswer << " is: " << endl;
            printMayanNumber(correctAnswer);
            cout << endl;
        }
        // Ask user to input another number to continue the game
        cout << "Enter another number, or less than 10 to exit: ";
        cin >> userInput;
        // If incorrect input then clear input and reprompt user to enter another guess
        while (cin.fail()) {
            cout << "Wrong input, please enter another number, or less than 10 to exit: ";
            cin.clear();
            cin.ignore(10000, '\n');
            cin >> userInput;
        }
    }

    // End game if user input is less than 10
    if (userInput < 10) {
        return 0;
    }
    // Ensure all control paths return a value to satisfy compiler warnings
    return 0;

}

