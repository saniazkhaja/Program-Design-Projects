/* ----------------------------------------------------------------------
    Program 2: Great 13
        Peg puzzle. Jump pegs to try and leave only a single peg.

    Course: CS 141, Fall 2021
    System: Windows using Clion
    Author: Sania Khaja

   ----------------------------------------------------------------------
*/
#include <iostream>
#include <cctype>   // for toupper()
using namespace std;

// keeps track of which move you are on
int moveNumber = 1;
// declaring all board values
char pA = '#';
char pB = '#';
char pC = '#';
char pD = '#';
char pE = '#';
char pF = '#';
char pG = '.';
char pH = '#';
char pI = '#';
char pJ = '#';
char pK = '#';
char pL = '#';
char pM = '#';

// ----------------------------------------------------------------------
// Display the game instructions.
void displayInstructions() {
    cout << "Class: CS 141             \n"
         << "Program: #2 Great 13      \n"
         << "  \n"
         << "Make a series of jumps until there is a single piece left in the   \n"
         << "middle. On each move you must jump an adjacent piece into an empty \n"
         << "square, jumping horizontally, vertically, or diagonally.           \n"
         << "Input of 'R' resets the board back to the beginning, and input of  \n"
         << "'X' exits the game.'   \n"
         << endl;
} //end displayInstructions()

// ----------------------------------------------------------------------
// Display the board, using the global variables pA..pM
void displayBoard()
{
    cout <<"\n "
         <<                 "    Board   " <<            " Position \n"
         <<"       "             << pA <<             "          A    \n"
         <<"     " <<      pB<<" "<<pC<<" "<<pD<<       "      B C D  \n"
         <<"   "<<pE<<" "<<pF<<" "<<pG<<" "<<pH<<" "<<pI<<"  E F G H I\n"
         <<"     " <<      pJ<<" "<<pK<<" "<<pL<<       "      J K L  \n"
         <<"       "             << pM <<             "          M    \n"
         << endl;
} //end displayBoard()

// ----------------------------------------------------------------------
// to reset board and start game over
void resetBoard() {
    cout << endl << "   *** Restarting" << endl;
    moveNumber = 1;
    pA = '#';
    pB = '#';
    pC = '#';
    pD = '#';
    pE = '#';
    pF = '#';
    pG = '.';
    pH = '#';
    pI = '#';
    pJ = '#';
    pK = '#';
    pL = '#';
    pM = '#';
    displayBoard();
} // end of resetBoard()

// ----------------------------------------------------------------------
// depending on the piece chosen, stores boardPiece to the value on the board and returns it
char checkBoardPiece(char whichPiece) {
    char boardPiece;

    if (whichPiece == 'A') {
        boardPiece = pA;
    }
    else if (whichPiece == 'B') {
        boardPiece = pB;
    }
    else if (whichPiece == 'C') {
        boardPiece = pC;
    }
    else if (whichPiece == 'D') {
        boardPiece = pD;
    }
    else if (whichPiece == 'E') {
        boardPiece = pE;
    }
    else if (whichPiece == 'F') {
        boardPiece = pF;
    }
    else if (whichPiece == 'G') {
        boardPiece = pG;
    }
    else if (whichPiece == 'H') {
        boardPiece = pH;
    }
    else if (whichPiece == 'I') {
        boardPiece = pI;
    }
    else if (whichPiece == 'J') {
        boardPiece = pJ;
    }
    else if (whichPiece == 'K') {
        boardPiece = pK;
    }
    else if (whichPiece == 'L') {
        boardPiece = pL;
    }
    else {
        boardPiece = pM;
    }
    return boardPiece;
} //end of checkBoardPiece

// ----------------------------------------------------------------------
// checking if the move is valid based on piece and then returning 0 if not valid and 1 if valid
int checkValidMove(char sourcePiece, char jumpPiece, char destinationPiece) {
    if ((checkBoardPiece(sourcePiece)) != '#') {
        cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
        return 0;
    }
    else if ((checkBoardPiece(jumpPiece)) != '#') {
        cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
        return 0;
    }
    else if ((checkBoardPiece(destinationPiece)) != '.') {
        cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
        return 0;
    }
    return 1;
} // end of checkValidMove()

// ----------------------------------------------------------------------
// checking diagonals and making sure they are adjacent
int checkDiagonalAdjacent(char sourcePiece, char jumpPiece, char destinationPiece) {
    if ((sourcePiece == 'A' || destinationPiece == 'A') && (sourcePiece == 'E' || destinationPiece == 'E') && jumpPiece == 'B') {
        return 1;
    }
    else if ((sourcePiece == 'A' || destinationPiece == 'A') && (sourcePiece == 'I' || destinationPiece == 'I') && jumpPiece == 'D') {
        return 1;
    }
    else if ((sourcePiece == 'I' || destinationPiece == 'I') && (sourcePiece == 'M' || destinationPiece == 'M') && jumpPiece == 'L') {
        return 1;
    }
    else if ((sourcePiece == 'M' || destinationPiece == 'M') && (sourcePiece == 'E' || destinationPiece == 'E') && jumpPiece == 'J') {
        return 1;
    }
    else if ((sourcePiece == 'B' || destinationPiece == 'B') && (sourcePiece == 'L' || destinationPiece == 'L') && jumpPiece == 'G') {
        return 1;
    }
    else if ((sourcePiece == 'D' || destinationPiece == 'D') && (sourcePiece == 'J' || destinationPiece == 'J') && jumpPiece == 'G') {
        return 1;
    }
    else {
        return 0;
    }
} //end of checkDiagonalAdjacent()

// ----------------------------------------------------------------------
// checking verticals and making sure they are adjacent. returns 1 if they are adjacent
int checkVerticalAdjacent(char sourcePiece, char jumpPiece, char destinationPiece) {
    if ((sourcePiece == 'B' || destinationPiece == 'B') && (sourcePiece == 'J' || destinationPiece == 'J') && jumpPiece == 'F') {
        return 1;
    }
    else if ((sourcePiece == 'D' || destinationPiece == 'D') && (sourcePiece == 'L' || destinationPiece == 'L') && jumpPiece == 'H') {
        return 1;
    }
    else if ((sourcePiece == 'A' || destinationPiece == 'A') && (sourcePiece == 'G' || destinationPiece == 'G') && jumpPiece == 'C') {
        return 1;
    }
    else if ((sourcePiece == 'C' || destinationPiece == 'C') && (sourcePiece == 'K' || destinationPiece == 'K') && jumpPiece == 'G') {
        return 1;
    }
    else if ((sourcePiece == 'G' || destinationPiece == 'G') && (sourcePiece == 'M' || destinationPiece == 'M') && jumpPiece == 'K') {
        return 1;
    }
    else {
        return 0;
    }
} //end of checkVerticalAdjacent()

// ----------------------------------------------------------------------
// checking horizontals and making sure they are adjacent
int checkHorizontalAdjacent(char sourcePiece, char jumpPiece, char destinationPiece){
    if ((sourcePiece == 'B' || destinationPiece == 'B') && (sourcePiece == 'D' || destinationPiece == 'D') && jumpPiece == 'C') {
        return 1;
    }
    else if ((sourcePiece == 'J' || destinationPiece == 'J') && (sourcePiece == 'L' || destinationPiece == 'L') && jumpPiece == 'K') {
        return 1;
    }
    else if ((sourcePiece == 'E' || destinationPiece == 'E') && (sourcePiece == 'G' || destinationPiece == 'G') && jumpPiece == 'F') {
        return 1;
    }
    else if ((sourcePiece == 'F' || destinationPiece == 'F') && (sourcePiece == 'H' || destinationPiece == 'H') && jumpPiece == 'G') {
        return 1;
    }
    else if ((sourcePiece == 'G' || destinationPiece == 'G') && (sourcePiece == 'I' || destinationPiece == 'I') && jumpPiece == 'H') {
        return 1;
    }
    else {
        return 0;
    }
} //end of checkHorizontalAdjacent()

// ----------------------------------------------------------------------
// changing board values to update board based on move
void determineBoardChange(char whichPiece, char updatePiece) {
    if (whichPiece == 'A') {
        pA = updatePiece;
    }
    if (whichPiece == 'B') {
        pB = updatePiece;
    }
    if (whichPiece == 'C') {
        pC = updatePiece;
    }
    if (whichPiece == 'D') {
        pD = updatePiece;
    }
    if (whichPiece == 'E') {
        pE = updatePiece;
    }
    if (whichPiece == 'F') {
        pF = updatePiece;
    }
    if (whichPiece == 'G') {
        pG = updatePiece;
    }
    if (whichPiece == 'H') {
        pH = updatePiece;
    }
    if (whichPiece == 'I') {
        pI = updatePiece;
    }
    if (whichPiece == 'J') {
        pJ = updatePiece;
    }
    if (whichPiece == 'K') {
        pK = updatePiece;
    }
    if (whichPiece == 'L') {
        pL = updatePiece;
    }
    if (whichPiece == 'M') {
        pM = updatePiece;
    }
} //end of determinePieceChange()

// ----------------------------------------------------------------------
// changing board values to update board based on move
void changeBoard (char sourcePiece, char jumpPiece, char destinationPiece) {
    // Going through each piece on the board and checking if the piece has to change or not
    char emptyPiece = '.';
    char actualPiece = '#';

    determineBoardChange(sourcePiece, emptyPiece);
    determineBoardChange(jumpPiece, emptyPiece);
    determineBoardChange(destinationPiece, actualPiece);

    displayBoard();
} //end of changeBoard()

// ----------------------------------------------------------------------
// checking if the game has been won yet and returns true or false
bool checkWin () {
    //checking to see how many pieces left on the board
    int countPieces = 0;
    if (pA == '#') {
        countPieces++;
    }
    if (pB == '#') {
        countPieces++;
    }
    if (pC == '#') {
        countPieces++;
    }
    if (pD == '#') {
        countPieces++;
    }
    if (pE == '#') {
        countPieces++;
    }
    if (pF == '#') {
        countPieces++;
    }
    if (pG == '#') {
        countPieces++;
    }
    if (pH == '#') {
        countPieces++;
    }
    if (pI == '#') {
        countPieces++;
    }
    if (pJ == '#') {
        countPieces++;
    }
    if (pK == '#') {
        countPieces++;
    }
    if (pL == '#') {
        countPieces++;
    }
    if (pM == '#') {
        countPieces++;
    }

    if (countPieces == 1) {
        cout << endl << "Congratulations, you did it!" << endl;
    }
    return countPieces == 1;
} // end of checkWin()

// ----------------------------------------------------------------------
// Main section of the program, containing the game play loop
int main() {
    displayInstructions();
    displayBoard();
    // Game play loop
    while(checkWin() == 0) {
        string moveFrom = ""; // used to store user input of move
        char sourcePiece;
        char jumpPiece;
        char destinationPiece;
        char exitOrRestart;
        cout << moveNumber << ". "
             << "Enter positions from, jump, and to (e.g. EFG): ";
        cin >> moveFrom; // getting user input
        for(int i = 0; i < moveFrom.size(); i++) {  // converting user input into uppercase
            moveFrom.at(i)= toupper(moveFrom.at(i));
        }
        exitOrRestart = moveFrom.at(0);

        // checking if game needs to be exited, restarted or played
        if (exitOrRestart == 'X') {
            cout << "Exiting" << endl;
            if (checkWin() == 0) {
                cout << endl << "Better luck next time." << endl;
            }
            break;
        }
        else if (exitOrRestart == 'R') {
            resetBoard();
            continue;
        }
        else {
            sourcePiece = moveFrom.at(0);
            jumpPiece = moveFrom.at(1);
            destinationPiece = moveFrom.at(2);
            // checking if move is valid. If so, then continues to change the board
            if (checkValidMove(sourcePiece, jumpPiece, destinationPiece) == 0) {
                continue;
            }
            else if (checkDiagonalAdjacent(sourcePiece, jumpPiece, destinationPiece) != 1 && checkVerticalAdjacent(sourcePiece, jumpPiece, destinationPiece) != 1 && checkHorizontalAdjacent(sourcePiece, jumpPiece, destinationPiece) != 1) {
                cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
                continue;
            }
            else {
                moveNumber++;
                changeBoard(sourcePiece, jumpPiece, destinationPiece);
            }
        }
    } //end while loop
    cout << "Done." << endl;
    return 0;
} //end main()
