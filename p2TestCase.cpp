//
//  p2TestCase.cpp
//  p2.cpp
//
//  Created by John West on 9/21/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>

#include "p2.h"
#include "recursive.h"

using namespace std;

int main()
{
    int totalCases = 0;
    int casesPassed = 0;

    int sum_result1 = 0;
    int sum_result2 = 0;
    int sum_result3 = 0;

    int sum_edge1 = 0;
    int sum_edge2 = 0;

    list_t standardList1 = list_make();
    list_t standardList2 = list_make();
    list_t standardList3 = list_make();
    
    list_t edgeList1 = list_make();
    list_t edgeList2 = list_make(0, list_make());

    for (int i = 4; i > 0; i--) {
        standardList1 = list_make(i, standardList1);
        standardList2 = list_make(5 - i, standardList2);
        standardList3 = list_make(i + 1, standardList3);
    }
    // standardList1 is (1,2,3,4)
    // standardList2 is (4,3,2,1)
    // standardList3 is (2,3,4,5)

    cout << "Starting test cases for p2..." << endl << "-----------------------------" << endl;

    sum_result1 = sum(standardList1);
    totalCases++;
    cout << ".";

    sum_result2 = sum(standardList2);
    totalCases++;
    cout << ".";

    sum_result3 = sum(standardList3);
    totalCases++;
    cout << ".";

    if (sum_result1 == 10) {
        casesPassed++;
    }

    if (sum_result2 == 10) {
        casesPassed++;
    }

    if (sum_result3 == 14) {
        casesPassed++;
    }

    sum_edge1 = sum(edgeList1);
    totalCases++;
    cout << ".";

    sum_edge2 = sum(edgeList2);
    totalCases++;
    cout << ".";

    if (sum_edge1 == 0) {
        casesPassed++;
    }

    if (sum_edge2 == 0) {
        casesPassed++;
    }

    cout << "\nTest Cases passed: " << casesPassed << "/" << totalCases << endl;

    return 0;
}