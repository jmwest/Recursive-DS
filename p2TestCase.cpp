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
void makeAccumulateLists(vector <int> &accumulateCorrect);
void makeReverseLists(vector <list_t> &reverseCorrectList);
void makeAppendLists(vector <list_t> &appendCorrect);
void makeFilterLists(vector <list_t> &filterOddCorrect, vector <list_t> &filterEvenCorrect);
void makeRotateLists(vector <list_t> &rotateCorrect, vector <int> &numbers);
void makeChopLists(vector <list_t> &chopCorrect, vector <int> &numbers);

bool checkListsEqual(list_t first, list_t second, bool equal);
    // REQUIRES: equal is passed in as true

void testSumFunction(int &totalCases, int &casesPassed);
void testProductFunction(int &totalCases, int &casesPassed);
void testAccumulateFunction(int &totalCases, int &casesPassed, const vector <list_t> &inputs);
void testListFNFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t), const vector <list_t> &inputs, const vector <list_t> &correct, const string &fnName);
void testAppendFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t, list_t), const vector <list_t> &inputs, const vector <list_t> &correct, const string &fnName);
void testRotateChopFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t, unsigned int), const vector <list_t> &inputs, const vector <int> &numbers, const vector <list_t> &correct, const string &fnName);

int addition(int x, int y);
int multiplication(int x, int y);

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
    vector <list_t> appendCorrect;
    vector <list_t> oddCorrectList;
    vector <list_t> evenCorrectList;
    vector <list_t> filterCorrect;
    vector <list_t> rotateCorrect;
    vector <list_t> chopCorrect;
    vector <int> rotateNumbers;
    vector <int> chopLength;

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
    makeAppendLists(appendCorrect);
    makeFilterLists(oddCorrectList, evenCorrectList);
    makeRotateLists(rotateCorrect, rotateNumbers);
    makeChopLists(chopCorrect, chopLength);

    cout << endl << "Starting test cases for p2..." << endl << "-----------------------------" << endl;

    testSumFunction(totalCases, casesPassed);
    testProductFunction(totalCases, casesPassed);
    testAccumulateFunction(totalCases, casesPassed, inputList);
    testListFNFunction(totalCases, casesPassed, reverse, inputList, reverseCorrectList, "Reverse");
    testAppendFunction(totalCases, casesPassed, append, inputList, appendCorrect, "Append");
    testListFNFunction(totalCases, casesPassed, filter_even, inputList, evenCorrectList, "Filter Even");
    testListFNFunction(totalCases, casesPassed, filter_odd, inputList, oddCorrectList, "Filter Odd");
    testRotateChopFunction(totalCases, casesPassed, rotate, inputList, rotateNumbers, rotateCorrect, "Rotate");
    testRotateChopFunction(totalCases, casesPassed, chop, inputList, chopLength, chopCorrect, "Chop");

    cout << "\n\nTest Cases passed: " << casesPassed << endl << " Test Case total : " << totalCases << endl << endl;

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

void makeAccumulateLists(vector <int> &accumulateCorrect)
{
    accumulateCorrect.push_back(10);
    accumulateCorrect.push_back(24);
    accumulateCorrect.push_back(14);
    accumulateCorrect.push_back(1);

    accumulateCorrect.push_back(0);
    accumulateCorrect.push_back(0);
    accumulateCorrect.push_back(7);
    accumulateCorrect.push_back(8);

    accumulateCorrect.push_back(1);
    accumulateCorrect.push_back(45000);
    accumulateCorrect.push_back(4950);

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

void makeAppendLists(vector <list_t> &appendCorrect)
{
    appendCorrect.push_back(list_make(1, list_make(2, list_make(3, list_make(4, STANDARD_LIST1)))));
    appendCorrect.push_back(list_make(4, list_make(3, list_make(2, list_make(1, STANDARD_LIST2)))));
    appendCorrect.push_back(list_make(2, list_make(3, list_make(4, list_make(5, STANDARD_LIST3)))));
    appendCorrect.push_back(list_make(1, list_make(1, list_make(1, list_make(1, STANDARD_LIST4)))));

    appendCorrect.push_back(list_make());
    appendCorrect.push_back(list_make(0, list_make(0, list_make())));
    appendCorrect.push_back(list_make(7, list_make(7, list_make())));
    appendCorrect.push_back(list_make(4, list_make(2, EDGE_LIST4)));

    list_t stressList1 = list_make();
    list_t stressList2 = list_make();

    for (int i = 19999; i >= 0; i--) {
        stressList1 = list_make(1, stressList1);
        stressList2 = list_make((i % 10), stressList2);
    }

    appendCorrect.push_back(stressList1);
    appendCorrect.push_back(stressList2);

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

void makeRotateLists(vector <list_t> &rotateCorrect, vector <int> &numbers)
{
    numbers.push_back(2);
    numbers.push_back(1);
    numbers.push_back(0);
    numbers.push_back(2);

    numbers.push_back(20);
    numbers.push_back(250);
    numbers.push_back(1000);
    numbers.push_back(57);

    numbers.push_back(2);
    numbers.push_back(30);
    numbers.push_back(100);

    rotateCorrect.push_back(list_make(3, list_make(4, list_make(1, list_make(2, list_make())))));
    rotateCorrect.push_back(list_make(3, list_make(2, list_make(1, list_make(4, list_make())))));
    rotateCorrect.push_back(STANDARD_LIST3);
    rotateCorrect.push_back(STANDARD_LIST4);

    rotateCorrect.push_back(EDGE_LIST1);
    rotateCorrect.push_back(EDGE_LIST2);
    rotateCorrect.push_back(EDGE_LIST3);
    rotateCorrect.push_back(list_make(2, list_make(4, list_make())));

    rotateCorrect.push_back(STRESS_LIST1);
    rotateCorrect.push_back(STRESS_LIST2);
    rotateCorrect.push_back(STRESS_LIST3);

    return;
}

void makeChopLists(vector <list_t> &chopCorrect, vector <int> &numbers)
{
    numbers.push_back(2);
    numbers.push_back(1);
    numbers.push_back(0);
    numbers.push_back(4);

    numbers.push_back(0);
    numbers.push_back(0);
    numbers.push_back(1);
    numbers.push_back(1);

    numbers.push_back(9999);
    numbers.push_back(1210);
    numbers.push_back(57);

    chopCorrect.push_back(list_make(1, list_make(2, list_make())));
    chopCorrect.push_back(list_make(4, list_make(3, list_make(2, list_make()))));
    chopCorrect.push_back(STANDARD_LIST3);
    chopCorrect.push_back(list_make());

    chopCorrect.push_back(list_make());
    chopCorrect.push_back(list_make(0, list_make()));
    chopCorrect.push_back(list_make());
    chopCorrect.push_back(list_make(4, list_make()));

    chopCorrect.push_back(list_make(1, list_make()));

    list_t stress1 = list_make();

    for (int i = 8789; i >= 0 ; i--) {
        stress1 = list_make((i % 10), stress1);
    }

    chopCorrect.push_back(stress1);

    list_t stress2 = list_make();

    for (int i = 42; i >= 0; i--) {
        stress2 = list_make(i, stress2);
    }

    chopCorrect.push_back(stress2);

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

    int product_stress = 0;

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

    product_stress = product(STRESS_LIST1);
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

    if (product_stress == 1) {
        casesPassed++;
    }
    else if (DIAGNOSTIC) {
        cout << "\nProduct Case 9 failed with result: " << product_stress << endl;
    }

    return;
}

void testAccumulateFunction(int &totalCases, int &casesPassed, const vector <list_t> &inputs)
{
    vector <int> results(inputs.size());
    vector <int> accumulateCorrect;

    makeAccumulateLists(accumulateCorrect);

    cout << endl;

    for (unsigned int i = 0; i < inputs.size(); i++)
    {
        if (i == 8) {
            results.at(i) = accumulate(inputs.at(i), multiplication, 1);
        }
        else if (i > 8) {
            results.at(i) = accumulate(inputs.at(i), addition, 0);

        }
        else {
            if ((i % 2) == 0) {
                results.at(i) = accumulate(inputs.at(i), addition, 0);
            }
            else {
                results.at(i) = accumulate(inputs.at(i), multiplication, 1);
            }
        }

        totalCases++;
        
        if (results.at(i) == accumulateCorrect.at(i)) {
            casesPassed++;
            cerr << ".";
        }
        else {
            cerr << "x";
            
            if (DIAGNOSTIC) {
                cout << "\nAccumulate Case " << i + 1 << " failed with result: " << results.at(i) << endl;
            }
        }
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
            cerr << "x";
            
            if (DIAGNOSTIC) {
                cout << "\n" << fnName << " Case " << i + 1 << " failed with result: ";
                list_print(results.at(i));
                cout << endl;
            }
        }
    }

    return;
}

void testAppendFunction(int &totalCases, int &casesPassed, list_t (*fn)(list_t, list_t), const vector <list_t> &inputs, const vector <list_t> &correct, const string &fnName)
{
    vector <list_t> results(inputs.size() - 1);
    
    cout << endl;
    
    for (unsigned int i = 0; i < inputs.size() - 1; i++)
    {
        results.at(i) = fn(inputs.at(i), inputs.at(i));
        totalCases++;
        
        if (checkListsEqual(results.at(i), correct.at(i), true)) {
            casesPassed++;
            cerr << ".";
        }
        else {
            cerr << "x";
            
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
            cerr << "x";
            
            if (DIAGNOSTIC) {
                cout << "\n" << fnName << " Case " << i + 1 << " failed with result: ";
                list_print(results.at(i));
                cout << endl;
            }
        }
    }
    
    return;
}

int addition(int x, int y)
{
    return x + y;
}

int multiplication(int x, int y)
{
    return x * y;
}