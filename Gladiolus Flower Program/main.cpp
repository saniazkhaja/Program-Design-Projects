/* ---------------------------------------------
    Program 1: Gladiolus
        Prompt for the number of sections and display
        an ASCII gladiolus flower, with the sections centered
        above each other.

    Course: CS 141, Fall 2021. Tues 5pm lab
    System: Windows using cLion
    Author: Sania Khaja

    Original ASCII graphics gives:
                ________                      ___
                |      |                    /     \
                |      |                    \     /
             ___|      |___                   ---
            |              |
            |         ______ ------- ______
            |       /                       \
            |      |                         |
            |      |                         |
            |       \    ____/----\____     /
            |         \__/              \__/


         ___ |  | |----    |-----    |-----       / \     |\    |
          |  |--| |---     |     |   |           /   \    | \   |
          |  |  | |----    |-----    |----      /_____\   |  \  |
                           |     |   |         /       \  |   \ |
                           |-----    |_____   /         \ |    \|

---------------------------------------------------------------------------

*/

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw. The number in setw(...) is the total of blank spaces including the printed item.
using namespace std;  // so that we don't need to preface every cin and cout with std::

// Entire program is given inside of main()
int main() {

    // Display the menu and get the user choice
    int menuOption = 0;
    cout << "Program 1: Gladiolus            \n"
         << "Choose from among the following options:  \n"
         << "   1. Display original graphic  \n"
         << "   2. Display Gladiolus         \n"
         << "   3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;

    // Handle menu option of 3 to exit
    if( menuOption == 3) {
        exit( 0);
    }

    // Handle menu option of 1 to display custom ASCII graphics
    else if( menuOption == 1) {
        cout << setw( 8) << " ";
        cout << endl;
        // Display ASCII graphics
        cout << setw( 8) << " " << "        ________                      ___                    \n"
             << setw( 8) << " " << "        |      |                    /     \\                 \n"
             << setw( 8) << " " << "        |      |                    \\     /                 \n"
             << setw( 8) << " " << "     ___|      |___                   ---                    \n"
             << setw( 8) << " " << "    |              |                                         \n"
             << setw( 8) << " " << "    |         ______ ------- ______                          \n"
             << setw( 8) << " " << "    |       /                       \\                       \n"
             << setw( 8) << " " << "    |      |                         |                       \n"
             << setw( 8) << " " << "    |      |                         |                       \n"
             << setw( 8) << " " << "    |       \\    ____/----\\____     /                      \n"
             << setw( 8) << " " << "    |         \\__/              \\__/                       \n"
             << setw( 8) << " " << "                                                             \n"
             << setw( 8) << " " << "                                                             \n"
             << setw( 8) << " " << " ___ |  | |----    |-----    |-----       / \\     |\\    |  \n"
             << setw( 8) << " " << "  |  |--| |---     |     |   |           /   \\    | \\   |  \n"
             << setw( 8) << " " << "  |  |  | |----    |-----    |----      /_____\\   |  \\  |  \n"
             << setw( 8) << " " << "                   |     |   |         /       \\  |   \\ |  \n"
             << setw( 8) << " " << "                   |-----    |_____   /         \\ |    \\|  \n"
             << endl;
        // Display a line across the bottom
        for( int i=0; i<75; i++) {
            cout << "-";
        }
        cout << endl;
    } //end if( menuOption == 1)  // menu option to display custom graphic

    // To create Gladiolus
    else if( menuOption == 2) {
        int numberOfSections = 0;
        int tempPetalCount = 1; // to keep track of how many petals needed for each section
        int highestPetalCount = 0; // the biggest petal length in flower
        int startingSpaces = 0;
        int middlePetal = 1; // position of middle petal in a section
        bool rightLeaf = true;

        cout << "Number of sections -> ";
        cin >> numberOfSections;

        for (int i = 1; i <= numberOfSections; i++) { // double loop used to figure out what the highestPetalCount is
            for (int j = 1; j <= tempPetalCount; j++) {
                highestPetalCount = tempPetalCount;
            }
            tempPetalCount = tempPetalCount + 2;
        }

        tempPetalCount = 1; // flower always starts with 1 petal
        startingSpaces = highestPetalCount / 2; // how many spaces before "("

        for (int section = 1; section <= numberOfSections; section++) { // for each section of the flower
            int tempSpaces = startingSpaces;
            bool reachedMiddlePetal = false;
            int tempMiddleSpace = 2;

            for (int lineSpace = 0; lineSpace <= startingSpaces ; lineSpace++){ // putting space before each section dashes
                cout << " ";
            }
            cout << "---" << endl;

            for (int petal = 1; petal <= tempPetalCount; petal++) { // for each petal
                if (middlePetal == petal) { //checking to see if middle petal has been reached
                    reachedMiddlePetal = true;
                }

                if (tempSpaces != 0 && !reachedMiddlePetal) { // printing out spaces before the middle petal. triangle shape
                    for (int spaces = 1; spaces <= tempSpaces; spaces++){
                        cout << " ";
                    }
                    tempSpaces = tempSpaces - 1;
                }
                else if (reachedMiddlePetal) { // printing spaces after the middle of the petal. inverted triangle
                    for (int spaces1 = 1; spaces1 <= tempSpaces; spaces1++){
                        cout << " ";
                    }
                    tempSpaces = tempSpaces + 1;
                }

                if (middlePetal == petal) { // putting bud in middle of flower section and putting spaces before and after bud
                    cout << "(";
                    for (int midSpace = 1; midSpace <= middlePetal; midSpace++){
                        cout << " ";
                    }
                    cout << "@";
                    for (int midSpace = 1; midSpace <= middlePetal; midSpace++){
                        cout << " ";
                    }
                    cout << ")" << endl;
                }
                else { // creating spaces between each petal
                    cout << "(";
                    if (!reachedMiddlePetal) { // figuring out spacing before reaching the middle of the flower section
                        for (int space = 0; space <= tempMiddleSpace; space++){
                            cout << " ";
                        }
                        tempMiddleSpace =  tempMiddleSpace + 2;
                        cout << ")" << endl;
                    }
                    else if (reachedMiddlePetal) { // figuring out spacing after the middle of the flower section
                        tempMiddleSpace =  tempMiddleSpace - 2;
                        for (int space = 0; space <= tempMiddleSpace; space++){
                            cout << " ";
                        }
                        cout << ")" << endl;
                    }
                }
            }
            tempPetalCount = tempPetalCount + 2; // change in petal amount is +2 in each section
            middlePetal = (tempPetalCount / 2) + 1; // figuring out which petal would be in the middle of a section
        }

        for (int lineSpace = 0; lineSpace <= startingSpaces ; lineSpace++) { // to print out the dashes before each section
            cout << " ";
        }
        cout << "---" << endl;

        for (int stem = 1; stem <= numberOfSections * 2; stem++) { // loop in order to create stem and leaf
            if (stem % 2 == 1 && rightLeaf) { // checking if leaf should be put and if the leaf should be to the right
                for (int lineSpace = 0; lineSpace <= startingSpaces + 1; lineSpace++) { // to print out spaces before stem
                    cout << " ";
                }
                rightLeaf = false;
                cout << "|/" << endl;
            }
            else if (stem % 2 == 1 && !rightLeaf) { // checking if leaf should be put and if the leaf should be to the left
                for (int lineSpace = 0; lineSpace <= startingSpaces; lineSpace++) { // to print out spaces before stem
                    cout << " ";
                }
                rightLeaf = true;
                cout << "\\|" << endl;
            }
            else { //to print just the stem
                for (int lineSpace = 0; lineSpace <= startingSpaces + 1; lineSpace++) {
                    cout << " ";
                }
                cout << "|" << endl;
            }
        }
    } //end if( menuOption == 2) // menu option to display building

    cout << "Exiting" << endl;
    return 0;
}// end main()
