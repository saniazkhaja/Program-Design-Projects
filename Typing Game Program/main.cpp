/* ---------------------------------------------
Program 3: Typing

Course: CS 141, Fall 2021. Tues 1pm lab
System: Using Clion
Author: Sania Khaja
---------------------------------------------
*/


#include <iostream>
#include <ctime>        // Needed to set the random number seedseed to be the current time
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
#include <cctype>     // Allows using the tolower() function
using namespace std;    // So that we don't need to preface cin and cout with std::


//---------------------------------------------------------------------------
// To calculate elapsed time and keeping track of time
void CalculateTime (int & elapsedSeconds) {
    elapsedSeconds = 0;     // Will store number of elapsed seconds
    // Declare a variable to hold a time, and set it to the current time
    time_t startTime = time( NULL);
    // Find the difference between the current time and the start time
    elapsedSeconds = difftime( time( NULL), startTime);
} // End of CalculateTime


//---------------------------------------------------------------------------
// Calculating the score of the two timed scenarios by using the time, amount of words misspelled and the multiplier of a correct typed word
// Displays each sub score
void TheScore (const int elapsedTime, const int amountOfWordsMisspelled, int & score, const int wordLengthScore) {
   int timeScore = 0;
   int wordScore = 0;
   score = 0;

   // Calculating score based on the time used and displaying it
    if (elapsedTime < 15) {
        cout << "   Elapsed time: " << elapsedTime << " seconds. " << (15 - elapsedTime) * 2 << " point bonus for finishing " <<  (15 - elapsedTime) << " seconds early." << endl;
        timeScore = (15 - elapsedTime) * 2;
    }
    else {
        cout << "   Elapsed time: " << elapsedTime << " seconds. " << (15 - elapsedTime) * 3 << " point bonus for finishing " <<  (15 - elapsedTime) << " seconds late." << endl;
        timeScore = (15 - elapsedTime) * 3;
    }
    // Calculating score of words typed correctly and displaying it
    cout << "   " << (5 - amountOfWordsMisspelled) * wordLengthScore << " points: " << (5 - amountOfWordsMisspelled) << " spelled correctly x " << wordLengthScore << " points each" << endl;
    // Checking to see if there are any words misspelled
    if (amountOfWordsMisspelled != 0) {
        // Calculating score penalty of words misspelled
        cout << "   " << amountOfWordsMisspelled * (wordLengthScore * 2) << " point penalty: " << (amountOfWordsMisspelled) << " spelled incorrectly x " << wordLengthScore * 2 << " points each" << endl;
    }
    // Calculating score of words correct minus the score penalty
    wordScore = (5 - amountOfWordsMisspelled) * wordLengthScore - (amountOfWordsMisspelled * wordLengthScore * 2);
    // Calculating the final score by adding the time and word score together
    score = timeScore + wordScore;
    cout << "   Score: " << score << endl << endl;
} // End of TheScore


//---------------------------------------------------------------------------
// Gets the userInput and displays which words were misspelled by comparing the array of correct words. Keeps count of misspelled words
void GettingWordsAndDisplayMisspelled (const vector<string> wordsToType, const vector<string> wordsToTypeCorrect, int & misspelledWordsCounter) {
    string userWordInput = "";
    vector<string> userWords; // Used to store all the words the user inputs

    // Goes through the user input and adds to an array to store the words
    for (int i = 0; i < 5; i++) {
        cin >> userWordInput;
        userWords.push_back(userWordInput);
    }

    // Loop is used to check each word in the array and see if the user spelled it correctly or not
    for (int i = 0; i < 5; i++) {
        // Checking if words were not correct
        if (userWords.at(i) != wordsToTypeCorrect.at(i)) {
            misspelledWordsCounter++;
            if (misspelledWordsCounter == 1) {
                cout << "   Misspelled words:" << endl;
            }
            cout << "       " << userWords.at(i) << " should be: " << wordsToTypeCorrect.at(i) << endl;
        }
    }
    // Checking if all words were spelled correctly
    if (misspelledWordsCounter == 0) {
        cout << "   No misspelled words!" << endl;
    }
    userWords.clear(); //Clears array so it can be used again
} // End of GettingWordsAndDisplayMisspelled


//---------------------------------------------------------------------------
// Displaying misspelled words for user to type and then calls respective functions to display user misspelled words and the score
void Option1TimedSpellMisspelledWords (const vector<string> misspelledCorrectWordsList, const vector<string> misspelledIncorrectWordsList, int & score) {
    int index = 0;
    vector<string> wordsToType; // words that user needs to type correctly
    vector<string> wordsToTypeCorrect; // stores the correct version of the words that are displayed
    int misspelledWordsCounter = 0;
    int elapsedSeconds = 0;
    score = 0;

    cout << "Using commonly misspelled words" << endl;

    // loop used for displaying 5 words from misspelled list and storing the values in arrays
    for (int i = 0; i < 5; i++) {
        index = rand() % misspelledCorrectWordsList.size(); // choosing random index
        cout << misspelledIncorrectWordsList.at(index) << " ";
        wordsToTypeCorrect.push_back(misspelledCorrectWordsList.at(index)); // adding correct spelling words to array
        wordsToType.push_back(misspelledIncorrectWordsList.at(index)); // adding incorrect words to array
    }
    cout << endl << "Type in those words within goal of 15 seconds: " << endl;

    // function calls
    CalculateTime(elapsedSeconds);
    GettingWordsAndDisplayMisspelled(wordsToType, wordsToTypeCorrect, misspelledWordsCounter);
    TheScore(elapsedSeconds, misspelledWordsCounter, score, 3);

    // clearing arrays so it can be used again
    wordsToTypeCorrect.clear();
    wordsToType.clear();
} // End of Option1TimedSpellMisspelledWords


//---------------------------------------------------------------------------
// Displaying the words the user has to type from the dictionary while using the corresponding word length and keeping track of the score
void Option2TimedSpellDictionaryWords (const vector<string> dictionary, int wordLength, int & score) {
    int index = 0;
    int amountWords = 0;
    vector<string> wordsToType; // Storing which words the user needs to type
    int misspelledWordsCounter = 0;
    int elapsedSeconds = 0;

    cout << "Using full dictionary" << endl;

    // loop to choose 5 random words from the dictionary that satisfies the length
    while (amountWords < 5) {
        index = rand() % dictionary.size();
        // checking to see if random index chosen
        if (dictionary.at(index).length() == wordLength) {
            cout << dictionary.at(index) << " ";
            wordsToType.push_back(dictionary.at(index)); // adding dictionary word to array
            amountWords++;
        }
    }
    cout << endl << "Type in those words within goal of 15 seconds: " << endl;
    // function calls
    CalculateTime(elapsedSeconds);
    GettingWordsAndDisplayMisspelled(wordsToType, wordsToType, misspelledWordsCounter);
    TheScore(elapsedSeconds, misspelledWordsCounter, score, wordLength - 4);
    wordsToType.clear();
} // End of Option2TimedSpellDictionaryWords


//---------------------------------------------------------------------------
// Displaying words from certain indexes from either the dictionary, misspelled incorrect words or misspelled correct words list
void Option3DisplaySomeWords (const vector<string> misspelledIncorrectWordsList, const vector< string> misspelledCorrectWordsList, const vector<string> dictionary) {
    char userOption = ' ';
    int startIndex = 0;
    int endIndex = 0;

    // Displaying options
    cout << "   Displaying word list entries.\n"
            "   Which words do you want to display?\n"
            "      A. Dictionary of all words\n"
            "      B. Wrongly spelled common misspelled words\n"
            "      C. Correctly spelled common misspelled words\n";
    cout << "   Your choice -->" << endl;

    cin >> userOption;
    userOption = tolower(userOption); // user option to lowercase

    // Checking which option was chosen
    switch (userOption) {
        case 'a': // print from dictionary
            cout << "   Enter the start and end indices between 0 and 263532:";
            // getting indexes
            cin >> startIndex;
            cin >> endIndex;
            // loop prints from dictionary array from start index to end index
            for (int i = startIndex; i <= endIndex; i++) {
                cout << "      " <<  i << ". " << dictionary.at(i) << endl;
            }
            break;
        case 'b': // Printing out misspelled incorrect words
            cout << "   Enter the start and end indices between 0 and 113:";
            cin >> startIndex;
            cin >> endIndex;
            // loop prints from indexes and from incorrect list array
            for (int i = startIndex; i <= endIndex; i++) {
                cout << "      " <<  i << ". " << misspelledIncorrectWordsList.at(i) << endl;
            }
            break;
        case 'c': // Printing out misspelled correct words
            cout << "   Enter the start and end indices between 0 and 113:";
            cin >> startIndex;
            cin >> endIndex;
            // loop prints from indexes and from correct word list array
            for (int i = startIndex; i <= endIndex; i++) {
                cout << "      " <<  i << ". " << misspelledCorrectWordsList.at(i) << endl;
            }
            break;
        default:
            break;
    }
    cout << endl;
} // End of Option3DisplaySomeWords


//---------------------------------------------------------------------------
// Binary search on dictionary vector in order to find the word that the user input word
void Option4BinarySearch (const vector<string> dictionary) {
    int lowIndex, midIndex, highIndex;     // array indices for binary search
    int amountOfWordsLookedAt = 1;
    string wordToFind;

    cout << "Enter the word to lookup:";
    cin >> wordToFind; //getting user input

    // Loop converts string into all lowercase letters
    for (int i = 0; i < wordToFind.size(); i++) {
        wordToFind.at(i) = tolower(wordToFind.at(i));
    }

    // Binary search for word
    lowIndex = 0;
    highIndex = dictionary.size() - 1;
    while (lowIndex <= highIndex) {
        midIndex = (lowIndex + highIndex) / 2;

        // Displaying which word is being compared to the user input word
        cout << "     " << amountOfWordsLookedAt << ". Comparing to: " << dictionary.at(midIndex) << endl;
        amountOfWordsLookedAt++;

        if (wordToFind == dictionary.at(midIndex)) { // Checking if word was found
            cout << wordToFind << " was found." << endl;
            break;
        }
        else if (wordToFind < dictionary.at(midIndex)) {
            highIndex = midIndex - 1; // Word should be located before middle index
        }
        else {
            lowIndex = midIndex + 1;  // Word should be located after middle index
        }
    }
    // Checking if the word was not found
    if (wordToFind != dictionary.at(midIndex)) {
        cout << wordToFind << " was NOT found." << endl;
    }
} //end of Option4BinarySearch


//---------------------------------------------------------------------------
// Changing wordLength based on user input
void Option5SetWordLength (int & wordLength) {
    wordLength = 0;
    cout << "Enter new wordLength:" << endl;
    cin >> wordLength;
} // End of Option5SetWordLength


//---------------------------------------------------------------------------
// Read words into dictionary vector.
void readWordsIntoDictionary (vector <string> & dictionary) {
    // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "dictionary.txt");       // Open dictionary file
    assert (inStream.fail() == false );     // Ensure file open worked

    // If you had previously used vector dictionary, then you might want to clear it
    // before continuing to use it, though that is not the case here.
    dictionary.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while (inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        dictionary.push_back(newWord);
    }

    // Close the dictionary file
    inStream.close();
} // end of readWordsIntoDictionary


//---------------------------------------------------------------------------
// Reads in misspelledWords into two vectors. One is to store the incorrect words and the other stores the correct words
void readWordsIntoMisspelledWords (vector<string> & misspelledIncorrectWordsList, vector<string> & misspelledCorrectWordsList) {
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "misspelledWords.txt");       // Open file
    assert (inStream.fail() == false );     // Ensure file open worked
    int count = 0;

    // Clears vector in case it was used before
    misspelledIncorrectWordsList.clear();
    misspelledCorrectWordsList.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while (inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        if (count % 2 == 0) {
            misspelledIncorrectWordsList.push_back(newWord);
        }
        else {
            misspelledCorrectWordsList.push_back(newWord);
        }
        count++;
    }

    // Close the dictionary file
    inStream.close();
} // end of readWordsIntoDictionary

//---------------------------------------------------------------------------
// Initializing typing game and options
int main() {
    int menuOption;
    int currentScore = 0;
    int bestScore = 0;
    vector<string> dictionary; // Store words from input file into dictionary vector
    vector<string> misspelledIncorrectWordsList; // Store incorrect words from input file into vector
    vector<string> misspelledCorrectWordsList; // Store correct words from input file into vector
    bool stillPlaying = true;
    int wordLength = 5;

    // Initial display
    cout << "There are 263533 words in the full dictionary.\n"
            "There are 114 commonly misspelled words." << endl << endl;
    readWordsIntoDictionary( dictionary);
    readWordsIntoMisspelledWords(misspelledIncorrectWordsList, misspelledCorrectWordsList);
    srand( 1);   // make it predictable for now

    while (stillPlaying == true) {
        // Displaying menu options
        cout << "Select a menu option:\n"
                "   1. Spell commonly misspelled words (timed)\n"
                "   2. Type random words from full dictionary (timed)\n"
                "   3. Display some words from one of the lists\n"
                "   4. Use binary search to lookup a word in full dictionary\n"
                "   5. Set word length to use with full dictionary\n"
                "   6. Exit the program\n";
        cout << "Your choice -->" << endl;
        // Receiving user input
        cin >> menuOption;

        // Checking which menu option was selected and calling respective functions
        switch (menuOption) {
            case 1:
                Option1TimedSpellMisspelledWords(misspelledCorrectWordsList, misspelledIncorrectWordsList, currentScore);
                // checking to see which score is higher and keeping the higher score
                if (bestScore < currentScore) {
                    bestScore = currentScore;
                }
                break;
            case 2:
                Option2TimedSpellDictionaryWords(dictionary, wordLength, currentScore);
                wordLength++;
                // checking to see which score is higher and keeping the higher score
                if (bestScore < currentScore) {
                    bestScore = currentScore;
                }
                break;
            case 3:
                Option3DisplaySomeWords(misspelledIncorrectWordsList, misspelledCorrectWordsList, dictionary);
                break;
            case 4:
                Option4BinarySearch(dictionary);
                break;
            case 5:
                Option5SetWordLength(wordLength);
                break;
            case 6:
                cout << "Exiting program" << endl << "Best score was " << bestScore << endl;
                stillPlaying = false;
                break;
            default:
                break;
        }
    }
    return 0;
}
