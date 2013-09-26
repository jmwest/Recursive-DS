//
//  p2TestCase.cpp
//  p2.cpp
//
//  Created by John West on 9/21/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include <string>

#include "p2.h"
#include "recursive.h"

using namespace std;

void makeGlobalLists();
void testSumFunction(int &totalCases, int &casesPassed);
void testProductFunction(int &totalCases, int &casesPassed);

bool DIAGNOSTIC = false;

list_t STANDARD_LIST1;
list_t STANDARD_LIST2;
list_t STANDARD_LIST3;
list_t STANDARD_LIST4;

list_t EDGE_LIST1;
list_t EDGE_LIST2;
list_t EDGE_LIST3;
list_t EDGE_LIST4;

int main()
{
    string userInput;

    int totalCases = 0;
    int casesPassed = 0;

    cout << "Turn DIAGNOSTIC on? (y/n): ";
    cin >> userInput;

    if ((userInput == "y") || (userInput == "yes") || (userInput == "1")) {
        DIAGNOSTIC = true;
    }
    else {
        DIAGNOSTIC = false;
    }

    makeGlobalLists();

    cout << endl << "Starting test cases for p2..." << endl << "-----------------------------" << endl;

    testSumFunction(totalCases, casesPassed);
    testProductFunction(totalCases, casesPassed);

    cout << "\nTest Cases passed: " << casesPassed << endl << " Test Case total : " << totalCases << endl << endl;

    return 0;
}

void makeGlobalLists()
{
    STANDARD_LIST1 = list_make();
    STANDARD_LIST2 = list_make();
    STANDARD_LIST3 = list_make();
    STANDARD_LIST4 = list_make();
    
    EDGE_LIST1 = list_make();
    EDGE_LIST2 = list_make(0, list_make());
    EDGE_LIST3 = list_make(7, list_make());
    EDGE_LIST4 = list_make(4, list_make(2, list_make()));
    // EDGE_LIST1 = ()
    // EDGE_LIST2 = (0)
    // EDGE_LIST3 = (7)
    // EDGE_LIST4 = (4,2)

    for (int i = 4; i > 0; i--) {
        STANDARD_LIST1 = list_make(i, STANDARD_LIST1);
        STANDARD_LIST2 = list_make(5 - i, STANDARD_LIST2);
        STANDARD_LIST3 = list_make(i + 1, STANDARD_LIST3);
        STANDARD_LIST4 = list_make(1, STANDARD_LIST4);
    }
    // STANDARD_LIST1 is (1,2,3,4)
    // STANDARD_LIST2 is (4,3,2,1)
    // STANDARD_LIST3 is (2,3,4,5)
    // STANDARD_LIST4 is (1,1,1,1)

    return;
}

void testSumFunction(int &totalCases, int &casesPassed)
{
    int sum_result1 = 0;
    int sum_result2 = 0;
    int sum_result3 = 0;
    int sum_result4 = 0;
    
    int sum_edge1 = 0;
    int sum_edge2 = 0;
    int sum_edge3 = 0;
    int sum_edge4 = 0;

    sum_result1 = sum(STANDARD_LIST1);
    totalCases++;
    cout << endl << ".";

    sum_result2 = sum(STANDARD_LIST2);
    totalCases++;
    cout << ".";

    sum_result3 = sum(STANDARD_LIST3);
    totalCases++;
    cout << ".";

    sum_result4 = sum(STANDARD_LIST4);
    totalCases++;
    cout << ".";

    sum_edge1 = sum(EDGE_LIST1);
    totalCases++;
    cout << ".";
    
    sum_edge2 = sum(EDGE_LIST2);
    totalCases++;
    cout << ".";

    sum_edge3 = sum(EDGE_LIST3);
    totalCases++;
    cout << ".";
    
    sum_edge4 = sum(EDGE_LIST4);
    totalCases++;
    cout << "." << endl;

    if (sum_result1 == 10) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 1 failed with result: " << sum_result1 << endl;
    }
    
    if (sum_result2 == 10) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 2 failed with result: " << sum_result2 << endl;
    }

    if (sum_result3 == 14) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 3 failed with result: " << sum_result3 << endl;
    }

    if (sum_result4 == 4) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 4 failed with result: " << sum_result4 << endl;
    }

    if (sum_edge1 == 0) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 5 failed with result: " << sum_edge1 << endl;
    }

    if (sum_edge2 == 0) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 6 failed with result: " << sum_edge2 << endl;
    }

    if (sum_edge3 == 7) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 7 failed with result: " << sum_edge3 << endl;
    }
    
    if (sum_edge4 == 6) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nSum Case 8 failed with result: " << sum_edge4 << endl;
    }

    return;
}

void testProductFunction(int &totalCases, int &casesPassed)
{
    int product_result1 = 0;
    int product_result2 = 0;
    int product_result3 = 0;
    int product_result4 = 0;
    
    int product_edge1 = 0;
    int product_edge2 = 0;
    int product_edge3 = 0;
    int product_edge4 = 0;
    
    product_result1 = product(STANDARD_LIST1);
    totalCases++;
    cout << endl << ".";
    
    product_result2 = product(STANDARD_LIST2);
    totalCases++;
    cout << ".";
    
    product_result3 = product(STANDARD_LIST3);
    totalCases++;
    cout << ".";
    
    product_result4 = product(STANDARD_LIST4);
    totalCases++;
    cout << ".";
    
    product_edge1 = product(EDGE_LIST1);
    totalCases++;
    cout << ".";
    
    product_edge2 = product(EDGE_LIST2);
    totalCases++;
    cout << ".";
    
    product_edge3 = product(EDGE_LIST3);
    totalCases++;
    cout << ".";
    
    product_edge4 = product(EDGE_LIST4);
    totalCases++;
    cout << "." << endl;
    
    if (product_result1 == 24) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 1 failed with result: " << product_result1 << endl;
    }

    if (product_result2 == 24) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 2 failed with result: " << product_result2 << endl;
    }
    
    if (product_result3 == 120) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 3 failed with result: " << product_result3 << endl;
    }
    
    if (product_result4 == 1) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 4 failed with result: " << product_result4 << endl;
    }
    
    if (product_edge1 == 1) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 5 failed with result: " << product_edge1 << endl;
    }
    
    if (product_edge2 == 0) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 6 failed with result: " << product_edge2 << endl;
    }
    
    if (product_edge3 == 7) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 7 failed with result: " << product_edge3 << endl;
    }
    
    if (product_edge4 == 8) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 8 failed with result: " << product_edge4 << endl;
    }

    return;
}