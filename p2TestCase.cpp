//
//  p2TestCase.cpp
//  p2.cpp
//
//  Created by John West on 9/21/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "p2.h"
#include "recursive.h"

using namespace std;

void makeGlobalLists();
void makeReverseLists(vector <list_t> &reverseList, vector <list_t> &reverseCorrectList);
bool checkListsEqual(list_t first, list_t second, bool equal);
    // REQUIRES: equal is passed in as true

void testSumFunction(int &totalCases, int &casesPassed);
void testProductFunction(int &totalCases, int &casesPassed);
void testListFNFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t), vector <list_t> &results, const vector <list_t> &correct, const string &fnName);

bool DIAGNOSTIC = false;

list_t STANDARD_LIST1;
list_t STANDARD_LIST2;
list_t STANDARD_LIST3;
list_t STANDARD_LIST4;

list_t EDGE_LIST1;
list_t EDGE_LIST2;
list_t EDGE_LIST3;
list_t EDGE_LIST4;

list_t STRESS_LIST1;
list_t STRESS_LIST2;
list_t STRESS_LIST3;
list_t STRESS_LIST4;

int main()
{
    string userInput;
    vector <list_t> reverseList(8, list_make());
    vector <list_t> reverseCorrectList(8, list_make());

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
    makeReverseLists(reverseList, reverseCorrectList);

    for (int i = 0; i < 8; i++) {
        list_print(reverseCorrectList.at(i));
    }

    int x = 0;
    for (int j = 0; j < 100000; j++) {
        x = x + j;
    }
    cout << "\nx: " << x << endl;

    cout << endl << "Starting test cases for p2..." << endl << "-----------------------------" << endl;

    testSumFunction(totalCases, casesPassed);
    testProductFunction(totalCases, casesPassed);
    testListFNFunction(totalCases, casesPassed, reverse, reverseList, reverseCorrectList, "Reverse");

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

    STRESS_LIST1 = list_make();
    STRESS_LIST2 = list_make();
    STRESS_LIST3 = list_make();
    STRESS_LIST4 = list_make();

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

    for (int i = 0; i < 100000; i++) {
        STRESS_LIST1 = list_make(1, STRESS_LIST1);
        STRESS_LIST2 = list_make((i % 10), STRESS_LIST1);
        STRESS_LIST3 = list_make((i % 100), list_make(4, STRESS_LIST1));
    }
    // STRESS_LIST1 is 100,000 1's
    // STRESS_LIST2 is (0,1,2,3,4,5,6,7,8,9,0,1 ....)
    // STRESS_LIST3 is (0,1,2,3,4,5,6,7,8,9,10,11,12 ....)

    return;
}

void makeReverseLists(vector <list_t> &reverseList, vector <list_t> &reverseCorrectList)
{
    reverseList.at(0) = STANDARD_LIST1;
    reverseList.at(1) = STANDARD_LIST2;
    reverseList.at(2) = STANDARD_LIST3;
    reverseList.at(3) = STANDARD_LIST4;
    reverseList.at(4) = EDGE_LIST1;
    reverseList.at(5) = EDGE_LIST2;
    reverseList.at(6) = EDGE_LIST3;
    reverseList.at(7) = EDGE_LIST4;
    
    reverseCorrectList.at(0) = STANDARD_LIST2;
    reverseCorrectList.at(1) = STANDARD_LIST1;
    reverseCorrectList.at(2) = list_make(5, list_make(4, list_make(3, list_make(2, list_make()))));
    reverseCorrectList.at(3) = STANDARD_LIST4;
    reverseCorrectList.at(4) = EDGE_LIST1;
    reverseCorrectList.at(5) = EDGE_LIST2;
    reverseCorrectList.at(6) = EDGE_LIST3;
    reverseCorrectList.at(7) = list_make(2, list_make(4, list_make()));

    return;
}

bool checkListsEqual(list_t first, list_t second, bool equal)
{
    if (list_isEmpty(first) || list_isEmpty(second)) {
        return equal;
    }

    if (list_first(first) != list_first(second)) {
        equal = false;
    }

    return checkListsEqual(list_rest(first), list_rest(second), equal);
}

void testSumFunction(int &totalCases, int &casesPassed)
{
    vector <int> sum_results(11, 0);

    sum_results.at(0) = sum(STANDARD_LIST1);
    totalCases++;

    if (sum_results.at(0) == 10) {
        casesPassed++;
        cout << endl << ".";
    }
    else {
        cout << endl << "x";

        if (DIAGNOSTIC) {
            cout << "\nSum Case 1 failed with result: " << sum_results.at(0) << endl;
        }
    }

    sum_results.at(1) = sum(STANDARD_LIST2);
    totalCases++;

    if (sum_results.at(1) == 10) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 2 failed with result: " << sum_results.at(1) << endl;
        }
    }

    sum_results.at(2) = sum(STANDARD_LIST3);
    totalCases++;
    
    if (sum_results.at(2) == 14) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 3 failed with result: " << sum_results.at(2) << endl;
        }
    }

    sum_results.at(3) = sum(STANDARD_LIST4);
    totalCases++;
    
    if (sum_results.at(3) == 4) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 4 failed with result: " << sum_results.at(3) << endl;
        }
    }

    sum_results.at(4) = sum(EDGE_LIST1);
    totalCases++;

    if (sum_results.at(4) == 0) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 5 failed with result: " << sum_results.at(4) << endl;
        }
    }

    sum_results.at(5) = sum(EDGE_LIST2);
    totalCases++;
    
    if (sum_results.at(5) == 0) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 6 failed with result: " << sum_results.at(5) << endl;
        }
    }

    sum_results.at(6) = sum(EDGE_LIST3);
    totalCases++;
    
    if (sum_results.at(6) == 7) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 7 failed with result: " << sum_results.at(6) << endl;
        }
    }
    
    sum_results.at(7) = sum(EDGE_LIST4);
    totalCases++;
    
    if (sum_results.at(7) == 6) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 8 failed with result: " << sum_results.at(7) << endl;
        }
    }

    sum_results.at(8) = sum(STRESS_LIST1);
    totalCases++;
    
    if (sum_results.at(8) == 100000) {
        casesPassed++;
        cout << endl << ".";
    }
    else {
        cout << endl << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 9 failed with result: " << sum_results.at(8) << endl;
        }
    }

    sum_results.at(9) = sum(STRESS_LIST2);
    totalCases++;
    
    if (sum_results.at(9) == 450000) {
        casesPassed++;
        cout << endl << ".";
    }
    else {
        cout << endl << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 10 failed with result: " << sum_results.at(8) << endl;
        }
    }
    
    sum_results.at(10) = sum(STRESS_LIST1);
    totalCases++;
    
    if (sum_results.at(10) == 100000) {
        casesPassed++;
        cout << endl << ".";
    }
    else {
        cout << endl << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 1 failed with result: " << sum_results.at(0) << endl;
        }
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

void testListFNFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t), vector <list_t> &results, const vector <list_t> &correct, const string &fnName)
{
    results.at(0) = fn(STANDARD_LIST1);
    totalCases++;
    
    if (checkListsEqual(results.at(0), correct.at(0), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 1 failed with result: ";
            list_print(results.at(0));
            cout << endl;
        }
    }
    
    results.at(1) = fn(STANDARD_LIST2);
    totalCases++;
    
    if (checkListsEqual(results.at(1), correct.at(1), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 2 failed with result: ";
            list_print(results.at(1));
            cout << endl;
        }
    }
    
    results.at(2) = fn(STANDARD_LIST3);
    totalCases++;
    
    if (checkListsEqual(results.at(2), correct.at(2), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 3 failed with result: ";
            list_print(results.at(2));
            cout << endl;
        }
    }

    results.at(3) = fn(STANDARD_LIST4);
    totalCases++;

    if (checkListsEqual(results.at(3), correct.at(3), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 4 failed with result: ";
            list_print(results.at(3));
            cout << endl;
        }
    }

    results.at(4) = fn(EDGE_LIST1);
    totalCases++;

    if (checkListsEqual(results.at(4), correct.at(4), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";

        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 5 failed with result: ";
            list_print(results.at(4));
            cout << endl;
        }
    }

    results.at(5) = fn(EDGE_LIST2);
    totalCases++;

    if (checkListsEqual(results.at(5), correct.at(5), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 6 failed with result: ";
            list_print(results.at(5));
            cout << endl;
        }
    }
    
    results.at(6) = fn(EDGE_LIST3);
    totalCases++;
    
    if (checkListsEqual(results.at(6), correct.at(6), true)) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 7 failed with result: ";
            list_print(results.at(6));
            cout << endl;
        }
    }
    
    results.at(7) = fn(EDGE_LIST4);
    totalCases++;
    
    if (checkListsEqual(results.at(7), correct.at(7), true)) {
        casesPassed++;
        cout << "." << endl;
    }
    else {
        cout << "x" << endl;
        
        if (DIAGNOSTIC) {
            cout << "\n" << fnName << " Case 8 failed with result: ";
            list_print(results.at(7));
            cout << endl;
        }
    }

    return;
}