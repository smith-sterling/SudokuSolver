#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "SudokuBoard.h"

using namespace std;

string randomTitle();
string toLower(const string& s);

int main() {
    cout << """"
              "Enter your board number by number, reading left-to-right, top-to-bottom, as you would a book in english\n"
              "Separate every number with a space.\n"
              "If the block at that space is blank, enter '0' instead.\n"
              """";
    cout << endl;
    vector<vector<int>> list;
    for (int i = 0; i < 9; ++i) {
        vector<int> thisRow;
        for (int j = 0; j < 9; ++j) {
            int q;
            cin >> q;
            if (q > 9 || q < 0) {
                --i;
                cout << "No! Try a better number! One that's in range." << endl;
                continue;
            }
            thisRow.push_back(q);
        }
        list.push_back(thisRow);
    }

    SudokuBoard board(list);
    if (! board.solveBoard()) {
        cout << "\nHere's what you tried to enter, " + randomTitle() + ": \n" << board.toString();
        return -1;
    }

    cout << "\nAlright, I have the answer here." << endl;
    cout << "If you would like to have me tell you the whole board, type 'done'.\n"
            "If you would like me to tell you a specific square, type 'hint'\n"
            "If you would like to see the board that you gave me plus any hints I've given you or things I confirmed, \n"
            "   type 'board' or 'status'"
            "If you would like to guess a specific square and have me tell you if you are correct, type 'guess'\n"
         << endl;

    string input;
    while (input != "done") {
        cin >> input;
        input = toLower(input);
        if (input == "hint") {
            int col, row;
            cout << "Alright, so input the coordinates of the box you would like me to tell you.\n"
                    "First, the column, starting at 1 on the left and going to 9 on the right. Then press enter."
                 << endl;
            cin >> col;
            cout << "Alright, next input the row, starting with 1 on the bottom up to 9 on the top" << endl;
            cin >> row;
            cout << board.hint(col, row) << endl;
        } else if (input == "guess") {
            int col, row, guess;
            cout << "Alright, so input the coordinates of the box you would like to guess.\n"
                    "First, the column, starting at 1 on the left and going to 9 on the right. Then press enter."
                 << endl;
            cin >> col;
            cout << "Alright, next input the row, starting with 1 on the bottom up to 9 on the top" << endl;
            cin >> row;
            cout << "Okay, now enter what you would like to guess, and I will tell you if that number is correct" << endl;
            cin >> guess;
            cout << ((board.guess(col, row, guess)) ? ("That is correct") : ("Sorry, try again...")) << endl;
        } else if (input == "board" || input == "status") {
            cout << board.status() << endl;
        } else if (input == "done") {
                input = "done";
        } else {
            cout << "Sorry, what was that?" << endl;
        }
    }


    cout << endl << board.toString() << endl;

    return 0;
}

string toLower(const string & s) {
    string lowerString;
    for (char c : s) {
        lowerString += (char)tolower(c);
    }
    return lowerString;
}

string randomTitle() {
    string titles [] = {"imbecile", "idiot", "imbecilen", "masochist", "sausage-fingers",
                        "man", "Benedict Cabbage-patch", "three-inch fool", "fool", "cream-faced loon",
                        "loser", "kleptomaniac"};

    srand(time(nullptr));
    return titles[rand() % titles->size()];
}