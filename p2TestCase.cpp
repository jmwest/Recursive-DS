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

void makeGlobalLists(vector <list_t> &inputList);
void makeReverseLists(vector <list_t> &reverseCorrectList);
void makeFilterLists(vector <list_t> &filterOddCorrect, vector <list_t> &filterEvenCorrect);
void makeChopLists(vector <list_t> &chopCorrect, vector <int> numbers);

bool checkListsEqual(list_t first, list_t second, bool equal);
    // REQUIRES: equal is passed in as true

void testSumFunction(int &totalCases, int &casesPassed);
void testProductFunction(int &totalCases, int &casesPassed);
void testListFNFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t), const vector <list_t> &inputs, const vector <list_t> &correct, const string &fnName);
void testRotateChopFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t, unsigned int), const vector <list_t> &inputs, const vector <int> &numbers, const vector <list_t> &correct, const string &fnName);

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
    vector <list_t> inputList;
    vector <list_t> reverseCorrectList;
    vector <list_t> oddCorrectList;
    vector <list_t> evenCorrectList;

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

    makeGlobalLists(inputList);
    makeReverseLists(reverseCorrectList);
    makeFilterLists(oddCorrectList, evenCorrectList);

    cout << endl << "Starting test cases for p2..." << endl << "-----------------------------" << endl;

    testSumFunction(totalCases, casesPassed);
    testProductFunction(totalCases, casesPassed);
    testListFNFunction(totalCases, casesPassed, reverse, inputList, reverseCorrectList, "Reverse");
    testListFNFunction(totalCases, casesPassed, filter_even, inputList, evenCorrectList, "Filter Even");
    testListFNFunction(totalCases, casesPassed, filter_odd, inputList, oddCorrectList, "Filter Odd");

    cout << "\nTest Cases passed: " << casesPassed << endl << " Test Case total : " << totalCases << endl << endl;

    return 0;
}

void makeGlobalLists(vector <list_t> &inputList)
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

    for (int i = 9999; i >= 0; i--) {
        STRESS_LIST1 = list_make(1, STRESS_LIST1);
        STRESS_LIST2 = list_make((i % 10), STRESS_LIST2);

        if (i < 100) {
            STRESS_LIST3 = list_make(i, STRESS_LIST3);
        }
    }
    // STRESS_LIST1 is 10,000 1's
    // STRESS_LIST2 is (0,1,2,3,4,5,6,7,8,9,0,1 ...)
    // STRESS_LIST3 is (0,1,2,3,4,5 ... 96,97,98,99)

    inputList.push_back(STANDARD_LIST1);
    inputList.push_back(STANDARD_LIST2);
    inputList.push_back(STANDARD_LIST3);
    inputList.push_back(STANDARD_LIST4);
    inputList.push_back(EDGE_LIST1);
    inputList.push_back(EDGE_LIST2);
    inputList.push_back(EDGE_LIST3);
    inputList.push_back(EDGE_LIST4);
    inputList.push_back(STRESS_LIST1);
    inputList.push_back(STRESS_LIST2);
    inputList.push_back(STRESS_LIST3);

    return;
}

void makeReverseLists(vector <list_t> &reverseCorrectList)
{
    reverseCorrectList.push_back(STANDARD_LIST2);
    reverseCorrectList.push_back(STANDARD_LIST1);
    reverseCorrectList.push_back(list_make(5, list_make(4, list_make(3, list_make(2, list_make())))));
    reverseCorrectList.push_back(STANDARD_LIST4);
    reverseCorrectList.push_back(EDGE_LIST1);
    reverseCorrectList.push_back(EDGE_LIST2);
    reverseCorrectList.push_back(EDGE_LIST3);
    reverseCorrectList.push_back(list_make(2, list_make(4, list_make())));
    reverseCorrectList.push_back(STRESS_LIST1);

    list_t stressCorrect2 = list_make();
    list_t stressCorrect3 = list_make();
    for (int i = 0; i < 10000; i++) {
        stressCorrect2 = list_make((i % 10), stressCorrect2);

        if (i < 100) {
            stressCorrect3 = list_make(i, stressCorrect3);
        }
    }

    reverseCorrectList.push_back(stressCorrect2);
    reverseCorrectList.push_back(stressCorrect3);

    return;
}

void makeFilterLists(vector <list_t> &filterOddCorrect, vector <list_t> &filterEvenCorrect)
{
    filterOddCorrect.push_back(list_make(1, list_make(3, list_make())));
    filterOddCorrect.push_back(list_make(3, list_make(1, list_make())));
    filterOddCorrect.push_back(list_make(3, list_make(5, list_make())));
    filterOddCorrect.push_back(STANDARD_LIST4);
    filterOddCorrect.push_back(list_make());
    filterOddCorrect.push_back(list_make());
    filterOddCorrect.push_back(list_make(7, list_make()));
    filterOddCorrect.push_back(list_make());
    filterOddCorrect.push_back(STRESS_LIST1);

    filterEvenCorrect.push_back(list_make(2, list_make(4, list_make())));
    filterEvenCorrect.push_back(list_make(4, list_make(2, list_make())));
    filterEvenCorrect.push_back(list_make(2, list_make(4, list_make())));
    filterEvenCorrect.push_back(list_make());
    filterEvenCorrect.push_back(list_make());
    filterEvenCorrect.push_back(list_make(0, list_make()));
    filterEvenCorrect.push_back(list_make());
    filterEvenCorrect.push_back(list_make(4, list_make(2, list_make())));
    filterEvenCorrect.push_back(list_make());

    list_t oddStressList1 = list_make();
    list_t oddStressList2 = list_make();
    list_t evenStressList1 = list_make();
    list_t evenStressList2 = list_make();

    for (int i = 9999; i >= 0; i--) {
        if ((i % 2) == 0) {
            evenStressList1 = list_make((i % 10), evenStressList1);

            if (i < 100) {
                evenStressList2 = list_make(i, evenStressList2);
            }
        }
        else {
            oddStressList1 = list_make((i % 10), oddStressList1);

            if (i < 100) {
                oddStressList2 = list_make(i, oddStressList2);
            }
        }
    }

    filterOddCorrect.push_back(oddStressList1);
    filterOddCorrect.push_back(oddStressList2);

    filterEvenCorrect.push_back(evenStressList1);
    filterEvenCorrect.push_back(evenStressList2);

    return;
}

bool checkListsEqual(list_t first, list_t second, bool equal)
{
    if (list_isEmpty(first) && list_isEmpty(second)) {
        return equal;
    }
    else if (list_isEmpty(first) && !list_isEmpty(second)) {
        return false;
    }
    else if (!list_isEmpty(first) && list_isEmpty(second)) {
        return false;
    }

    if (list_first(first) != list_first(second)) {
        equal = false;
    }

    return checkListsEqual(list_rest(first), list_rest(second), equal);
}

void testSumFunction(int &totalCases, int &casesPassed)
{
    vector <int> sum_results(12, 0);

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
    
    if (sum_results.at(8) == 10000) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 9 failed with result: " << sum_results.at(8) << endl;
        }
    }

    sum_results.at(9) = sum(STRESS_LIST2);
    totalCases++;
    
    if (sum_results.at(9) == 45000) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 10 failed with result: " << sum_results.at(9) << endl;
        }
    }

    sum_results.at(10) = sum(STRESS_LIST3);
    totalCases++;

    if (sum_results.at(10) == 4950) {
        casesPassed++;
        cout << ".";
    }
    else {
        cout << "x";
        
        if (DIAGNOSTIC) {
            cout << "\nSum Case 11 failed with result: " << sum_results.at(10) << endl;
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
    cout << ".";
    
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

void testListFNFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t), const vector <list_t> &inputs, const vector <list_t> &correct, const string &fnName)
{
    vector <list_t> results(inputs.size());

    cout << endl;

    for (unsigned int i = 0; i < inputs.size(); i++)
    {

        results.at(i) = fn(inputs.at(i));
        totalCases++;

        if (checkListsEqual(results.at(i), correct.at(i), true)) {
            casesPassed++;
            cerr << ".";
        }
        else {
            cout << "x";
            
            if (DIAGNOSTIC) {
                cout << "\n" << fnName << " Case " << i + 1 << " failed with result: ";
                list_print(results.at(i));
                cout << endl;
            }
        }
    }

    return;
}

void testRotateChopFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t, unsigned int), const vector <list_t> &inputs, const vector <int> &numbers, const vector <list_t> &correct, const string &fnName)
{
    vector <list_t> results(inputs.size());
    
    cout << endl;
    
    for (unsigned int i = 0; i < inputs.size(); i++)
    {
        
        results.at(i) = fn(inputs.at(i), numbers.at(i));
        totalCases++;
        
        if (checkListsEqual(results.at(i), correct.at(i), true)) {
            casesPassed++;
            cerr << ".";
        }
        else {
            cout << "x";
            
            if (DIAGNOSTIC) {
                cout << "\n" << fnName << " Case " << i + 1 << " failed with result: ";
                list_print(results.at(i));
                cout << endl;
            }
        }
    }
    
    return;
}
