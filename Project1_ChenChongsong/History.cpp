//
//  History.cpp
//  cs32_project1(3)
//
//  Created by CCS on 3/7/17.
//  Copyright © 2017 CCS. All rights reserved.
//

#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//#include "globals.h"
//#include "Player.h"
//#include "Robot.h"
//#include "Arena.h"
//#include "Game.h"
#include "History.h"


History::History (int nRows, int nCols) : rows(nRows), cols(nCols){
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            historyMap[i][j] = 0;
        }
    }
}

bool History::record (int r, int c) {
    if (r < 1 || r > rows) return false;
    if (c < 1 || c > cols) return false;
    historyMap[r-1][c-1]++;
    return true;
}

void History::display() const {
    clearScreen();
    char tmp;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            if (!historyMap[i][j])
                tmp = '.';
            else {
                if (historyMap[i][j] < 26)
                    tmp = 'A' + historyMap[i][j]-1;
                else
                    tmp = 'Z';
            }
            std::cout << tmp;
        }
        std::cout << std::endl;
    }
}
