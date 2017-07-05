//
//  History.hpp
//  cs32_project1(3)
//
//  Created by CCS on 3/7/17.
//  Copyright © 2017 CCS. All rights reserved.
//

#ifndef History_h
#define History_h

class History;

#include "globals.h"

class History
{
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;

    private:
        int historyMap[MAXROWS][MAXROBOTS];
        int rows, cols;
};

#endif /* History_h */
