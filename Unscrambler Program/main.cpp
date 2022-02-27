/* program_4.cpp
    Unscrambler: A game where the user gets to choose board size and unscramble the words
    The board is randomly scrambled and the user has to rotate the row and column to get the correct words
    Author: Sania Khaja
    Date: 11/19/2021
    Class: CS 141, Fall 2021, UIC
    System: Windows using CLion

*/

#include <iostream>
#include <cctype>     // Allows using the toupper() function
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
using namespace std;    // So that we don't need to preface cin and cout with std::

// checks for win by comparing the original completed board and the current scrambled Board
void checkWin(bool & stillPlaying, const vector<char> scrambledBoard, const vector<char> completedBoard) {
    bool theSameBoard = true;

    //going through each position
    for (int i = 0; i < scrambledBoard.size(); i++) {
        // checking to see if values on the board is the same
        if (completedBoard.at(i) != scrambledBoard.at(i)) {
            theSameBoard = false;
            break;
        }
    }
    // means the user has won the game so they no longer are playing
    if (theSameBoard == true) {
        stillPlaying = false;
    }
} // end of checkWin()

class Board {
public:
    // sets the game board vector and board size
    void setGameBoard(vector <char> theGameBoard, int theBoardSize) {
        gameBoard = theGameBoard;
        boardSize = theBoardSize;
    } // end of setGameBoard

    // used to display the board and the words that the board needs to reach to
    void displayBoard(const vector<string> & originalBoardWords, const bool stillPlaying) {
        // only need to print the words if user has not won the game already
        if (stillPlaying == true) {
            cout << "These are the words that you should try to spell out using the board, in order: " << endl;
            // displays the words the user needs to have on the board
            for (int j = 0; j < originalBoardWords.size() - 1; j++) {
                cout << originalBoardWords.at(j) << ", ";
            }
            cout << originalBoardWords.at(originalBoardWords.size() - 1) << "." << endl;
            cout << endl;
            cout << "Current board:" << endl;
        }
        printBoard(); // prints the board

        // printing that the user won
        if (stillPlaying == false) {
            cout << "Congratulations, you won! Thank you for playing!\n"
                    "Exiting program...";
        }
    } // end of displayBoard

    // prints out the board
    void printBoard() {
        int positionCounter = 0; // used to know which position we are at in the board while printing

        cout << "   ";
        // printing out the row numbers
        for (int num = 0; num < boardSize; num++) {
            cout << num << "   ";
        }
        cout << endl;

        // going through each row section in board
        for (int row = 0; row < boardSize; row++) {
            cout << "   ";
            // printing out dashes between each row
            for (int numDashes = 0; numDashes < (boardSize * 4) - 1; numDashes++) {
                cout << "-";
            }
            cout << endl;
            cout << row << " ";
            // printing all letters in board
            for (int col = 0; col < boardSize; col++) {
                cout << "| " << gameBoard.at(positionCounter) << " ";
                positionCounter++;
            }
            cout << "|" << endl;
        }
        cout << "   ";
        // printing dashes at the end
        for (int numDashes = 0; numDashes < (boardSize * 4) - 1; numDashes++) {
            cout << "-";
        }
        cout << endl;

        cout << "Current board words: ";
        // prints out the current words on the board
        for (int i = 0; i < gameBoard.size(); i++) {
            cout << gameBoard.at(i);
        }
        cout << endl;
    } // end of printBoard()

    // used to rotate the board based on user input
    void userRotatesBoard(const int & boardSize, vector<char> & scrambledBoard, vector<string> originalBoardWords, bool & stillPlaying, const vector<char> completedBoard) {
        Board theBoard;
        char userRowOrCol;
        int userRowOrColNum;
        int userRotation;
        bool validInput = false;

        // trying to get valid inputs from user
        while (validInput == false) {
            // displaying rotation information
            cout << "   Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
                    "   This should be in the format of <R or C> <row/column number> <number of positions to rotate>, \n"
                    "   where valid row and column numbers are between 0 and " << boardSize - 1 << "," << endl <<
                 "   E.g. R 0 1 would rotate the top row (row 0) of the board to the right once, \n"
                 "        c 1 -2 would rotate the second column (col 1) of the board upwards twice. \n"
                 "   Your choice: ";
            cin >> userRowOrCol >> userRowOrColNum >> userRotation; // getting user input

            // checking to see the user did not pick row or column
            if (toupper(userRowOrCol) != 'R' && toupper(userRowOrCol) != 'C') {
                cout << "First input must be 'R' or 'C'. Try again." << endl;
                continue;
            }
            // checking to see if a valid row or column was picked
            if (userRowOrColNum < 0 || userRowOrColNum > boardSize - 1) {
                cout << "Number must be between 0 and " << boardSize - 1 << ". Try again." << endl;
                continue;
            }
            validInput = true;
        }

        // rotates row
        if (toupper(userRowOrCol) == 'R') {
            rotateRow(userRowOrColNum, userRotation, scrambledBoard, boardSize);
        }
        // rotates column
        if (toupper(userRowOrCol) == 'C') {
            rotateCol(userRowOrColNum, userRotation, scrambledBoard, boardSize);
        }
        checkWin(stillPlaying, scrambledBoard, completedBoard);
        theBoard.setGameBoard(scrambledBoard, boardSize);
        theBoard.displayBoard(originalBoardWords, stillPlaying);
    } // end of userRotatesBoard()

    // used to rotate the row based on user input
    void rotateRow(int userRowNum, int userRotation, vector<char> & scrambledBoard, int boardSize) {
        int startingPointOfRow = userRowNum * boardSize;

        // row moving in the positive direction
        if (userRotation > 0) {
            //rotates board for the amount of times user specified
            for (int i = 0; i < userRotation; i++) {
                char tempLetter = scrambledBoard.at((userRowNum * boardSize) + (boardSize - 1));
                // rotating row forward by one
                for (int r = startingPointOfRow; r < startingPointOfRow + boardSize; r++) {
                    char nextLetter = scrambledBoard.at(r);
                    scrambledBoard.at(r) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }

        // row moving in the negative direction
        if (userRotation < 0) {
            //rotates board for the amount of times user specified
            for (int j = 0; j < abs(userRotation); j++) {
                char tempLetter = scrambledBoard.at(startingPointOfRow);
                // rotating row backwards by one
                for (int r = (userRowNum * boardSize) + (boardSize - 1); r >= startingPointOfRow; r--) {
                    char nextLetter = scrambledBoard.at(r);
                    scrambledBoard.at(r) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
    } // end of rotateRow()

    // used to rotate the column based on user input
    void rotateCol(int userColNum, int userRotation, vector<char> & scrambledBoard, int boardSize) {
        // column moving in positive direction
        if (userRotation > 0) {
            //rotates board for the amount of times user specified
            for (int i = 0; i < userRotation; i++) {
                char tempLetter = scrambledBoard.at(userColNum + (boardSize - 1) * boardSize);
                // rotating column forward by one
                for (int c = userColNum; c < boardSize * boardSize; c+=boardSize) {
                    char nextLetter = scrambledBoard.at(c);
                    scrambledBoard.at(c) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
        // column moving in negative direction
        if (userRotation < 0) {
            //rotates board for the amount of times user specified
            for (int j = 0; j < abs(userRotation); j++) {
                char tempLetter = scrambledBoard.at(userColNum);
                // rotating column backward by one
                for (int c = userColNum + (boardSize - 1) * boardSize; c >= userColNum; c-=boardSize) {
                    char nextLetter = scrambledBoard.at(c);
                    scrambledBoard.at(c) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
    } // end of rotateCol()

private:
    int boardSize = 0;
    vector <char> gameBoard;
}; // end of Board class

// reading words into vector in order to store words
void readWordsIntoDictionary (vector <string> & dictionary) {
    // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "dictionary-3to5-letters.txt");       // Open dictionary file
    assert (inStream.fail() == false );     // Ensure file open worked
    dictionary.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while (inStream >> newWord) {           // While there is another word to be read
        dictionary.push_back(newWord);
    }

    // Close the dictionary file
    inStream.close();
} // end of readWordsIntoDictionary

// used to scramble the board once the completed board was ready
void scrambleTheBoard(const vector<char> & completedBoard, vector<char> & scrambledBoard, const int amountOfScrambles, const int boardSize, vector<char> & originalScrambledBoard, vector<string> originalBoardWords) {
    Board theBoard;
    scrambledBoard.clear();
    originalScrambledBoard.clear();
    int randomRow;
    int randomCol;
    scrambledBoard = completedBoard;

    // scrambling the board for the amount of times teh user specified
    for (int i = 0; i < amountOfScrambles; i++) {
        randomRow = rand() % boardSize; // chooses random row in board
        randomCol = rand() % boardSize; // chooses random column in board

        // getting last letter in the row and storing it
        char tempLetter = scrambledBoard.at((randomRow * boardSize) + (boardSize - 1));
        // looping through entire row in order to shift the row
        for (int r = (randomRow * boardSize); r < (randomRow * boardSize) + boardSize; r++) {
            char nextLetter = scrambledBoard.at(r);
            scrambledBoard.at(r) = tempLetter;
            tempLetter = nextLetter;
        }

        // getting last letter in the column and storing it
        tempLetter = scrambledBoard.at(randomCol + (boardSize - 1) * boardSize);
        // looping through entire column in order to shift the column
        for (int c = randomCol; c < boardSize * boardSize; c+=boardSize) {
            char nextLetter = scrambledBoard.at(c);
            scrambledBoard.at(c) = tempLetter;
            tempLetter = nextLetter;
        }
    }
    originalScrambledBoard = scrambledBoard; // now board is scrambled so keeping the original form
    // used to set and display the scrambled board
    theBoard.setGameBoard(scrambledBoard, boardSize);
    theBoard.displayBoard(originalBoardWords, true);
} // end of scrambleTheBoard()

// used to choose the words to fill the board and stores all words in the board
void selectingWordsForBoard(const vector <string> & dictionary, const int boardSize, vector<string> & boardWords, vector<char> & completedBoard) {
    Board theBoard;
    int randomWordPosition = 0;
    int amountOfAvailablePositions = boardSize * boardSize; // amount of letters that the board can have
    int amountOfLetters = 0;
    boardWords.clear();
    completedBoard.clear();

    // getting random words for the board
    // loop makes sure that function words will not fill past the board
    while (amountOfLetters < amountOfAvailablePositions) {
        randomWordPosition = rand() % dictionary.size(); // gets random word to fill the board

        // checking to see if the size of the word is too big for the board
        if ((amountOfLetters + dictionary.at(randomWordPosition).size()) > amountOfAvailablePositions) {
            continue;
        }
        else {  // valid word to put into board so prints out the word
            // +1 is for the space. variable used to keep track of how many values filled in board
            amountOfLetters = amountOfLetters + dictionary.at(randomWordPosition).size() + 1;
            boardWords.push_back(dictionary.at(randomWordPosition));

            // adding each char in word to board vector
            for (int i = 0; i < dictionary.at(randomWordPosition).size(); i++) {
                completedBoard.push_back(dictionary.at(randomWordPosition).at(i));
            }
            completedBoard.push_back(' ');
        }
        // checking to see if no more words could fit into the board and then breaks out of while loop
        if ((amountOfAvailablePositions - amountOfLetters) < 3) {
            // loop used to add spaces to fill the rest of the board
            for (int i = 0; i < (amountOfAvailablePositions - amountOfLetters); i++) {
                completedBoard.push_back(' ');
            }
            break;
        }
    }
} // end of selectingWordsForBoard()

// starting display that gives a brief description about the game and asks whether the user wants to play or quit
// Also, gets valid board size and scrambles
void beginningDisplay(int dictionarySize, bool & stillPlaying, int & boardSize, int & amountOfScrambles) {
    char userInput; // used to know whether user wants to play or quit the game

    // displaying beginning message
    cout << "Program 5: Unscrambler\t\n"
            "CS 141, Fall 2021, UIC\t\n"
            " \n"
            "You will be presented with a board that is filled  \n"
            "with scrambled words. Rotate the rows and columns  \n"
            "to get the words displayed in the right order.     \n"
            "\n" << dictionarySize << " words have been read in from the dictionary.\n" << endl <<
            "Enter Q to quit or B to begin:";
    cin >> userInput;

    // checking if user quit and then displaying message
    if (toupper(userInput) == 'Q') {
        cout << endl << "Thank you for playing! \n"
                        "Exiting program... " << endl;
        exit (0);
    }

    // checking if user wants to play the game
    if (toupper(userInput) == 'B') {
        stillPlaying = true; // in order to know that user has started to play the game
        // used to get a valid board size
        while (boardSize < 4) {
            cout << "Choose your board size (must be a number greater than or equal to 4): " << endl;
            cin >> boardSize; // getting user input for board size

            // means invalid board size
            if (boardSize < 4) {
                cout << "The board size must be at least 4. Retry." << endl;
            }
            else {
                break;
            }
        }
        // used to get valid amount of scrambles
        while (amountOfScrambles < 1) {
            cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):" << endl;
            cin >> amountOfScrambles; // getting user input for the amount of scrambles
            if (amountOfScrambles < 1) {
                cout << "The number of times you select must be at least 1. Retry." << endl;
            }
            else {
                break;
            }
        }
    }
} // end of beginningDisplay()

int main() {
    bool stillPlaying = false; // to know whether the user is playing the game
    vector <string> dictionary; // storing all the 3 to 5 letter words
    int boardSize = 0;
    vector<string> originalBoardWords; // used to keep a list of the original words
    vector<char> completedBoard; // the board before it is scrambled
    vector<char> scrambledBoard;
    vector<char> originalScrambledBoard;
    Board theBoard;

    readWordsIntoDictionary(dictionary); // reading in all the words into the dictionary vector
    srand( 1);   // make it predictable for now

    char userInputOption;
    int amountOfScrambles = 0;

    beginningDisplay(dictionary.size(), stillPlaying, boardSize, amountOfScrambles); // setting up the board
    selectingWordsForBoard(dictionary, boardSize, originalBoardWords, completedBoard);
    scrambleTheBoard(completedBoard, scrambledBoard, amountOfScrambles, boardSize, originalScrambledBoard, originalBoardWords);

    while (stillPlaying == true) {
        // Displaying menu options
        cout << "Enter one of the following: \n"
                "   R to rotate a row or column, \n"
                "   C to view what the completed board should look like, \n"
                "   B to reset the board back to the beginning, \n"
                "   G to generate a new board with new random words, \n"
                "   S to have the computer automatically solve a board that you enter (5 points extra credit), \n"
                "   Q to quit. \n"
                "Your choice:" << endl;
        // Receiving user input
        cin >> userInputOption;

        // Checking which menu option was selected and calling respective functions
        switch (toupper(userInputOption)) {
            case 'R': // in order to rotate row and column in the board
                theBoard.userRotatesBoard(boardSize, scrambledBoard, originalBoardWords, stillPlaying, completedBoard);
                break;
            case 'C': //shows what completed board looks like
                cout << "The completed board should look like: " << endl;
                theBoard.setGameBoard(completedBoard, boardSize);
                theBoard.printBoard();
                theBoard.setGameBoard(scrambledBoard, boardSize);
                theBoard.displayBoard(originalBoardWords, true);
                break;
            case 'B': //Resets the board back to the beginning
                theBoard.setGameBoard(originalScrambledBoard, boardSize);
                theBoard.displayBoard(originalBoardWords, true);
                scrambledBoard = originalScrambledBoard;
                break;
            case 'G': //Generates a new board with different random words
                selectingWordsForBoard(dictionary, boardSize, originalBoardWords, completedBoard);
                scrambleTheBoard(completedBoard, scrambledBoard, amountOfScrambles, boardSize, originalScrambledBoard, originalBoardWords);
                break;
            case 'S': // computer automatically solves board
                break;
            case 'Q': //to exit program
                cout << "Thank you for playing! \n"
                        "Exiting program... " << endl;
                exit(0);
            default:
                break;
        }
    }
    return 0;
} // end of main()
