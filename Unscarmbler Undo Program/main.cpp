/* Prog6UnscramblerUndo.cpp
    Unscrambler: A game where the user gets to choose board size and unscramble the words
    The board is randomly scrambled and the user has to rotate the row and column to get the correct words
    Unscrambler using linked list for infinite undo of moves.
    Author: Sania Khaja
    Date: 11/29/2021
    Class: CS 141, Fall 2021, UIC
    System: Windows using CLion

*/
#include <iostream>  // Needed to avoid compiler error for the exit() command
#include <cctype>     // Allows using the toupper() function
#include <fstream>    // For file input and output
#include <vector>     // Input file is stored in a vector
#include <cassert>    // For the assert statement used to validate file open
#include <string> // For strings
using namespace std;    // So that we don't need to preface cin and cout with std::


class Node
{
public:
   int theMoveNumber;
   vector<char> board;
   vector<string> theBoardWords;
   Node *pNext;
};

class Board {
public:
    Board() {
        pHead = NULL;
    }
    void setStillPlaying(bool isStillPlaying) {
        stillPlaying = isStillPlaying;
    }
    bool getStillPlaying() {
        return stillPlaying;
    }
    void setMoveNumber(int theMoveNumber) {
        moveNumber = theMoveNumber;
    }
    int getMoveNumber() {
        return moveNumber;
    }

    static void readWordsIntoDictionary();
    void scrambleBoard();
    void selectingWordsForBoard();
    void checkForWin();
    void displayBoard();
    void userRotatesBoard();
    void displayList();
    void addNodeToList();
    void deleteNodeFromList();
    void deleteAllNodesFromList();

private:
    static vector <string> dictionary;
    int amountOfScrambles;
    int boardSize;
    vector<char> scrambledBoard;
    vector<char> goalBoard;
    vector<string> goalWordsString;
    vector<string> boardWordsString;
    int moveNumber;
    bool stillPlaying;
    Node *pHead;
    Node *pTemp;
};



//--------------------------------------------------------------------------------
// Display the move numbers on the linked list
void Board::displayList()
{
    pTemp = pHead;
    cout << "List is: ";
    while (pTemp != NULL) {
        cout << pTemp -> theMoveNumber << ": ";
        for (int i = 0; i < pTemp -> theBoardWords.size(); i++) {
            cout << pTemp -> theBoardWords.at(i);
        }
        pTemp = pTemp -> pNext;
        if (pTemp != NULL) {
            cout << " -> ";
        }
    }
    cout << endl;

} // end displayList()


void Board::deleteNodeFromList()
{
    // ...
    if (pHead -> pNext == NULL) {
        cout << "*** You cannot undo past the beginning of the game.  Retry. ***" << endl;
    }
    else {
        cout << "* Undoing move * " << endl;
        pTemp = pHead;
        delete pTemp;
        pHead = pHead -> pNext;
        moveNumber = pHead -> theMoveNumber;
        scrambledBoard = pHead -> board;
        boardWordsString = pHead -> theBoardWords;
    }

} //end deleteNodeFromList()

void Board::deleteAllNodesFromList()
{
    // ...
    while (pHead  != NULL) {
        pTemp = pHead;
        pHead = pHead -> pNext;
        delete pTemp;
    }
} //end deleteNodeFromList()

void Board::addNodeToList()
{
    Node *pTemp = new Node;
    pTemp -> theMoveNumber = moveNumber;
    pTemp -> board = scrambledBoard;
    pTemp -> theBoardWords = boardWordsString;
    pTemp -> pNext = pHead;
    pHead = pTemp;
}


// used to rotate the board based on user input
void Board::userRotatesBoard() {
    char theRowOrCol;
    int numberOfRotations;
    int rowOrCol;

    cout << "Enter the row/column to rotate, and # of (+/-) rotations:" << endl;
    cin >> theRowOrCol >> numberOfRotations; // getting user input
    while (numberOfRotations > boardSize - 1 || numberOfRotations < -(boardSize - 1)) {
        cout << "*** Shift value should be between " << -(boardSize - 1) << " and " << boardSize - 1 << ". Retry." << endl;
        cout << "Enter the row/column to rotate, and # of (+/-) rotations:" << endl;
        cin >> theRowOrCol >> numberOfRotations; // getting user input
    }
    rowOrCol = (int) theRowOrCol;

    // means a letter so rotating column
    if (rowOrCol > 96) {
        rowOrCol = rowOrCol - 97;
        // column moving in positive direction
        if (numberOfRotations > 0) {
            //rotates board for the amount of times user specified
            for (int i = 0; i < numberOfRotations; i++) {
                char tempLetter = scrambledBoard.at(rowOrCol + (boardSize - 1) * boardSize);
                // rotating column forward by one
                for (int c = rowOrCol; c < boardSize * boardSize; c+=boardSize) {
                    char nextLetter = scrambledBoard.at(c);
                    scrambledBoard.at(c) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
        // column moving in negative direction
        if (numberOfRotations < 0) {
            //rotates board for the amount of times user specified
            for (int j = 0; j < abs(numberOfRotations); j++) {
                char tempLetter = scrambledBoard.at(rowOrCol);
                // rotating column backward by one
                for (int c = rowOrCol + (boardSize - 1) * boardSize; c >= rowOrCol; c-=boardSize) {
                    char nextLetter = scrambledBoard.at(c);
                    scrambledBoard.at(c) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
    }
    else if (rowOrCol > 64) {
        rowOrCol = rowOrCol - 65;
        // column moving in positive direction
        if (numberOfRotations > 0) {
            //rotates board for the amount of times user specified
            for (int i = 0; i < numberOfRotations; i++) {
                char tempLetter = scrambledBoard.at(rowOrCol + (boardSize - 1) * boardSize);
                // rotating column forward by one
                for (int c = rowOrCol; c < boardSize * boardSize; c+=boardSize) {
                    char nextLetter = scrambledBoard.at(c);
                    scrambledBoard.at(c) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
        // column moving in negative direction
        if (numberOfRotations < 0) {
            //rotates board for the amount of times user specified
            for (int j = 0; j < abs(numberOfRotations); j++) {
                char tempLetter = scrambledBoard.at(rowOrCol);
                // rotating column backward by one
                for (int c = rowOrCol + (boardSize - 1) * boardSize; c >= rowOrCol; c-=boardSize) {
                    char nextLetter = scrambledBoard.at(c);
                    scrambledBoard.at(c) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
    }
    else { // means number so rotating row
        rowOrCol = rowOrCol - 48;
        int startingPointOfRow = rowOrCol * boardSize;

        // row moving in the positive direction
        if (numberOfRotations > 0) {
            //rotates board for the amount of times user specified
            for (int i = 0; i < abs(numberOfRotations); i++) {
                char tempLetter = scrambledBoard.at(startingPointOfRow + boardSize - 1);
                // rotating row forward by one
                for (int r = startingPointOfRow; r < startingPointOfRow + boardSize; r++) {
                    char nextLetter = scrambledBoard.at(r);
                    scrambledBoard.at(r) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }

        // row moving in the negative direction
        // row moving in the negative direction
        if (numberOfRotations < 0) {
            //rotates board for the amount of times user specified
            for (int j = 0; j < abs(numberOfRotations); j++) {
                char tempLetter = scrambledBoard.at(startingPointOfRow);
                // rotating row backwards by one
                for (int r = (rowOrCol * boardSize) + (boardSize - 1); r >= startingPointOfRow; r--) {
                    char nextLetter = scrambledBoard.at(r);
                    scrambledBoard.at(r) = tempLetter;
                    tempLetter = nextLetter;
                }
            }
        }
    }
    // to store board words into a strings
    string tempString = "";
    boardWordsString.clear();
    for (int j = 0; j < scrambledBoard.size(); j++) {
        if (scrambledBoard.at(j) != ' ') {
            tempString.push_back(scrambledBoard.at(j));
        }
        else {
            boardWordsString.push_back(tempString);
            boardWordsString.push_back(" ");
            tempString = "";
        }
    }
    boardWordsString.push_back(tempString);
} // end of userRotatesBoard()

void Board::displayBoard() {
    int positionCounter1 = 0; // used to know which position we are at in the board while printing
    int positionCounter2 = 0;

    cout << "   ";
    // printing out the row numbers
    for (char letter = 'A'; letter < boardSize + 'A'; letter++) {
        cout << letter << "   ";
    }
    cout << "       " << "Goal Board";
    cout << endl;

    // going through each row section in board
    for (int row = 0; row < boardSize; row++) {
        cout << "   ";
        // printing out dashes between each row
        for (int numDashes = 0; numDashes < (boardSize * 4) - 1; numDashes++) {
            cout << "-";
        }
        cout << "     ";
        for (int numDashes = 0; numDashes < (boardSize * 4); numDashes++) {
            cout << "-";
        }
        cout << endl;
        cout << row << " ";
        // printing all letters in board
        for (int col = 0; col < boardSize; col++) {
            cout << "| " << scrambledBoard.at(positionCounter1) << " ";
            positionCounter1++;
        }
        cout << "|    ";
        for (int col = 0; col < boardSize; col++) {
            cout << "| " << goalBoard.at(positionCounter2) << " ";
            positionCounter2++;
        }
        cout << "|" << endl;
    }
    cout << "   ";
    // printing dashes at the end
    for (int numDashes = 0; numDashes < (boardSize * 4) - 1; numDashes++) {
        cout << "-";
    }
    cout << "     ";
    for (int numDashes = 0; numDashes < (boardSize * 4); numDashes++) {
        cout << "-";
    }
    cout << endl;

    cout << "Board string: ";
    // prints out the current words on the board
    for (int i = 0; i < boardWordsString.size(); i++) {
        cout << boardWordsString.at(i);
    }
    cout << endl;

    cout << "Goal string: ";
    // prints out the current words on the board
    for (int i = 0; i < goalWordsString.size(); i++) {
        cout << goalWordsString.at(i) << " ";
    }
    cout << endl;
} // end of displayBoard()

void Board::checkForWin() {
    bool theSameBoard = true;

    //going through each position
    for (int i = 0; i < scrambledBoard.size(); i++) {
        // checking to see if values on the board is the same
        if (goalBoard.at(i) != scrambledBoard.at(i)) {
            theSameBoard = false;
            break;
        }
    }
    // means the user has won the game so they no longer are playing
    if (theSameBoard == true) {
        stillPlaying = false;
        cout << "Congratulations, you won! \n"
                "Exiting program... ";
    }
    else {
        displayList();
    }
} // end of checkWin()

void Board::readWordsIntoDictionary() {
    // Read in dictionary into dictionary vector
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( "commonWords.txt");       // Open dictionary file
    assert (inStream.fail() == false );     // Ensure file open worked
    dictionary.clear();

    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while (inStream >> newWord) {           // While there is another word to be read
        dictionary.push_back(newWord);
    }
    cout << dictionary.size() << " words have been read in from the dictionary." << endl;
    // Close the dictionary file
    inStream.close();
} // end of readWordsIntoDictionary

void Board::scrambleBoard() {
    int randomRow;
    int randomCol;
    scrambledBoard.clear();
    scrambledBoard = goalBoard;

    // scrambling the board for the amount of times the user specified
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
    // to store board words into a strings
   string tempString = "";
    for (int j = 0; j < scrambledBoard.size(); j++) {
        if (scrambledBoard.at(j) != ' ') {
            tempString.push_back(scrambledBoard.at(j));
        }
        else {
            boardWordsString.push_back(tempString);
            boardWordsString.push_back(" ");
            tempString = "";
        }
    }
    boardWordsString.push_back(tempString);
}

void Board::selectingWordsForBoard() {
    int randomWordPosition = 0;
    int amountOfAvailablePositions; // amount of letters that the board can have
    int amountOfLetters = 0;
    goalWordsString.clear();
    goalBoard.clear();
    scrambledBoard.clear();
    boardWordsString.clear();
    moveNumber = 1;
    boardSize = 0;

    cout << "   Choose board size. It must be a single digit >=4:    ";
    cin >> boardSize;
    // trying to get a valid size
    while (boardSize < 4 || boardSize > 9) {
        cin >> boardSize;
    }
    cout << "Choose single-digit number of times to scramble board:" << endl;
    cin >> amountOfScrambles;
    // getting valid scramble amount
    while (amountOfScrambles > 9 || amountOfScrambles < 1) {
        cin >> amountOfScrambles;
    }
    amountOfAvailablePositions = boardSize * boardSize;

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
            goalWordsString.push_back(dictionary.at(randomWordPosition));

            // adding each char in word to board vector
            for (int i = 0; i < dictionary.at(randomWordPosition).size(); i++) {
                goalBoard.push_back(dictionary.at(randomWordPosition).at(i));
            }
            goalBoard.push_back(' ');
        }
        // checking to see if no more words could fit into the board and then breaks out of while loop
        if ((amountOfAvailablePositions - amountOfLetters) < 1) {
            // loop used to add spaces to fill the rest of the board
            for (int i = 0; i < (amountOfAvailablePositions - amountOfLetters); i++) {
                goalBoard.push_back(' ');
            }
            break;
        }
    }
} // end of selectingWordsForBoard()
vector<string> Board::dictionary;

//-------------------------------------------------------------------------------------
int main() {
    Board theBoard;         // Create the board as an instance of the Board class
    int moveNumber = 1;
    char userMenuChoice;
    bool stillPlaying = true;
   // char pieceToMove = 'X'; // Will be set to 'X' or 'O' depending on move number. Start with 'X'
    theBoard.setMoveNumber(moveNumber);

    cout << "Program 6: Unscrambler Undo \n"
            "CS 141, Fall 2021, UIC\t     \n"
            " \n"
            "You will be presented with a board that is filled with scrambled words.    \n"
            "Rotate the rows and columns to get the words displayed in the right order. \n"
            "Press 'U' to undo moves.  ";
    theBoard.readWordsIntoDictionary(); // reading in all the words into the dictionary vector
    srand( 1);   // make it predictable for now
    theBoard.selectingWordsForBoard();
    theBoard.scrambleBoard();
    theBoard.displayBoard();
    theBoard.addNodeToList();
    theBoard.displayList();

    while (stillPlaying == true) {
        theBoard.setStillPlaying(stillPlaying);
        cout << "Enter one of the following: \n"
                "   R Rotate a row or column \n"
                "   G Generate a new board with new random words \n"
                "   U Undo most recent move \n"
                "   Q to quit. ";
        moveNumber = theBoard.getMoveNumber();
        cout << moveNumber << ". Your choice:" << endl;
        cin >> userMenuChoice;

        switch (toupper(userMenuChoice)) {
            case 'R':
                moveNumber++;
                theBoard.setMoveNumber(moveNumber);
                theBoard.userRotatesBoard();
                if (moveNumber != 1) {
                    theBoard.addNodeToList();
                }
                break;
            case 'G':
                theBoard.deleteAllNodesFromList();
                moveNumber = 1;
                theBoard.setMoveNumber(moveNumber);
                theBoard.selectingWordsForBoard();
                theBoard.scrambleBoard();
                theBoard.addNodeToList();
                break;
            case 'U':
                theBoard.deleteNodeFromList();
                break;
            case 'Q':
                cout << "Thank you for playing! Exiting program... ";
                theBoard.setStillPlaying(false);
                exit(0);
            default:
                break;
        }
        theBoard.displayBoard();
        theBoard.checkForWin();
        if (theBoard.getStillPlaying() == false) {
            stillPlaying = false;
        }
    }

return 0;
} // end main()
