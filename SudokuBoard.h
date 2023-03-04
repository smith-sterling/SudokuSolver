//
// Created by S Smith on 12/9/22.
//

#ifndef SUDOKUSOLVER_SUDOKUBOARD_H
#define SUDOKUSOLVER_SUDOKUBOARD_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <math.h>
using namespace std;


class SudokuBoard {
private:
    vector<vector<pair<int, bool>>> board;      //bool is a "isEditable"
    vector<vector<pair<int, bool>>> origPlusHints;

public:
    SudokuBoard (vector<vector<int>> list) {
        for (vector<int> row : list) {
            vector<pair<int, bool>> boardRow;
            for (int i : row) {
                if (i > 9 || i < 1) {
                    boardRow.emplace_back(make_pair(0, true));
                } else {
                    boardRow.emplace_back(make_pair(i, false));
                }
            }
            board.push_back(boardRow);
            origPlusHints.push_back(boardRow);
        }
    }


    bool solveBoard () {
        if (solveBoardHelper(0)) {
//            cout << "\nSuccess" << endl;
            return true;
        } else {
            cout << "\nAre you sure that was a valid sudoku board?" << endl;
            return false;
        }
    }

    bool solveBoardHelper(int squareID) {
        if (squareID >= 81) return isCompletelySolved();
        int row = squareID / 9;
        int col = squareID % 9;

        if (!board.at(row).at(col).second) { //if this was part of the original board (not editable)
            return solveBoardHelper(squareID + 1);
        } else {
            while (board.at(row).at(col).first < 9) {
                ++board.at(row).at(col).first;
                if (!isOkay(row, col)) {
                    continue;
                }
                if (solveBoardHelper(squareID + 1)) {
                    return true;
                }
            }
            board.at(row).at(col).first = 0;
            return false;
        }
    }

    bool isCompletelySolved () {
        //row logic && 0-catching
        for (int row = 0; row < board.size(); ++row) {
            set<int> rowHas;
            for (int col = 0; col < board.at(row).size(); ++col) {
                if (board.at(row).at(col).first == 0 ||
                    !rowHas.insert(board.at(row).at(col).first).second) {
                    return false;
                }
            }
        }
        //col logic
        for (int col = 0; col < board.size(); ++col) {
            set<int> colHas;
            for (int row = 0; row < board.at(col).size(); ++row) {
                if (!colHas.insert(board.at(row).at(col).first).second) {
                    return false;
                }
            }
        }
        //box logic
        for (int col = 0; col < 9; col += 3) {
            for (int row = 0; row < 9; row += 3 ) {
                set<int> boxHas;
                if (!boxHas.insert(board.at(row).at(col).first).second ||
                    !boxHas.insert(board.at(row).at(col + 1).first).second ||
                    !boxHas.insert(board.at(row).at(col + 2).first).second ||

                    !boxHas.insert(board.at(row + 1).at(col).first).second ||
                    !boxHas.insert(board.at(row + 1).at(col + 1).first).second ||
                    !boxHas.insert(board.at(row + 1).at(col + 2).first).second ||

                    !boxHas.insert(board.at(row + 2).at(col).first).second ||
                    !boxHas.insert(board.at(row + 2).at(col + 1).first).second ||
                    !boxHas.insert(board.at(row + 2).at(col + 2).first).second) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isOkay(int row, int col) {
        return rowIsOkay(row) && columnIsOkay(col) && boxIsOkay(row, col);
    }
    bool rowIsOkay(int row) {
        set<int> included;
        for (auto i : board.at(row)) {
            if (i.first == 0) continue;
            if (!included.insert(i.first).second) {
                return false;
            }
        }
        return true;
    }
    bool columnIsOkay(int col) {
        set<int> included;
        for (int i = 0; i < 9; ++i) {
            if (board.at(i).at(col).first == 0) continue;
            if (!included.insert(board.at(i).at(col).first).second) {
                return false;
            }
        }
        return true;
    }
    bool boxIsOkay(int row, int col) {
        vector<int> rowsToCheck;
        vector<int> colsToCheck;
        row = (row / 3) * 3;
        col = (col / 3) * 3;
        for (int i = 0; i < 3; ++i) {
            rowsToCheck.push_back(row + i);
            colsToCheck.push_back(col + i);
        }

        set<int> included;
        for (int i : rowsToCheck) {
            for (int j : colsToCheck) {
                if (board.at(i).at(j).first == 0) continue;
                if (! included.insert(board.at(i).at(j).first).second) {
                    return false;
                }
            }
        }
        return true;
    }

    string toString() {
        string s = "\n";
        for (vector<pair<int, bool>> row : board) {
            for (auto i : row) {
                s += to_string(i.first);
                s += " ";
            }
            s = s.substr(0, s.size() - 1);
            s += "\n";
        }
        return s;
    }

    string status() {
        string s = "\n";
        for (vector<pair<int, bool>> row : origPlusHints) {
            for (auto i : row) {
                s += to_string(i.first);
                s += " ";
            }
            s = s.substr(0, s.size() - 1);
            s += "\n";
        }
        return s;
    }

    int hint(int col, int row) {
        row = 9 - row;
        col = col - 1;

        int value = board.at(row).at(col).first;
        origPlusHints.at(row).at(col).first = value;

        return value;
    }
    bool guess(int col, int row, int guess) {
        row = 9 - row;
        col = col - 1;

        bool guessedIt = board.at(row).at(col).first == guess;
        if (guessedIt) { origPlusHints.at(row).at(col).first = guess; }

        return guessedIt;
    }
};


#endif //SUDOKUSOLVER_SUDOKUBOARD_H
