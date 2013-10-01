//
//  p2.cpp
//  p2.cpp
//
//  Created by John West on 9/19/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include "p2.h"

using namespace std;

static int addNumbers(int x, int y);
static int multiplyNumbers(int x, int y);
static int algebraic_helper(int result, list_t list, int (*fn)(int, int));

static list_t reverse_helper(list_t list, list_t reverseList);
static list_t append_helper(list_t first, list_t second);

static list_t filter_odd_or_even_helper(list_t list, list_t filteredList, int remainderValue);
static list_t filter_helper(list_t list, list_t filteredList, bool (*fn)(int));

static list_t rotate_helper(list_t list, list_t rotatedList, unsigned int n);
static list_t insert_list_helper(list_t first, list_t second, list_t combined, unsigned int n);
static list_t chop_helper(list_t list, unsigned int n);

static int fib_tail_helper(int n, int currentN, int currentNumber, int result);

static bool tree_covered_by(tree_t tree, tree_t tree_covered);

//--------------------------------------------------------//
int sum(list_t list)
{
    if (list_isEmpty(list)) {
        return 0;
    }

    return algebraic_helper(addNumbers(list_first(list), 0), list_rest(list), addNumbers);
}

int product(list_t list)
{
    if (list_isEmpty(list)) {
        return 1;
    }

    return algebraic_helper(multiplyNumbers(list_first(list), 1), list_rest(list), multiplyNumbers);
}

int accumulate(list_t list, int (*fn)(int, int), int identity)
{
    if (list_isEmpty(list)) {
        return identity;
    }
    
    return algebraic_helper(fn(identity, list_first(list)), list_rest(list), fn);
}

//--------------------------------------------------------//
static int addNumbers(int x, int y)
{
    return x + y;
}

static int multiplyNumbers(int x, int y)
{
    return x * y;
}

static int algebraic_helper(int result, list_t list, int (*fn)(int, int))
{
    if (list_isEmpty(list)) {
        return result;
    }

    return algebraic_helper(fn(result, list_first(list)), list_rest(list), fn);
}

//--------------------------------------------------------//
list_t reverse(list_t list)
{
    return reverse_helper(list, list_make());
}

static list_t reverse_helper(list_t list, list_t reverseList)
{
    if (list_isEmpty(list)) {
        return reverseList;
    }

    return reverse_helper(list_rest(list), list_make(list_first(list), reverseList));
}

//--------------------------------------------------------//
list_t append(list_t first, list_t second)
{
    return append_helper(reverse(first), second);
}

list_t append_helper(list_t first, list_t second)
{
    if (!list_isEmpty(first)) {
        return append_helper(list_rest(first), list_make(list_first(first), second));

    }
    else {
        return second;
    }
}

//--------------------------------------------------------//
list_t filter_odd(list_t list)
{
    if (list_isEmpty(list)) {
        return list;
    }

    return filter_odd_or_even_helper(list, list_make(), 1);
}

list_t filter_even(list_t list)
{
    if (list_isEmpty(list)) {
        return list;
    }

    return filter_odd_or_even_helper(list, list_make(), 0);
}

//--------------------------------------------------------//
static list_t filter_odd_or_even_helper(list_t list, list_t filteredList, int remainderValue)
{
    if (list_isEmpty(list)) {
        return reverse(filteredList);
    }
    else if ((list_first(list) % 2) == remainderValue) {
        filteredList = list_make(list_first(list), filteredList);
    }

    return filter_odd_or_even_helper(list_rest(list), filteredList, remainderValue);
}

//--------------------------------------------------------//
list_t filter(list_t list, bool (*fn)(int))
{
    if (list_isEmpty(list)) {
        return list;
    }

    return filter_helper(list, list_make(), fn);
}

static list_t filter_helper(list_t list, list_t filteredList, bool (*fn)(int))
{
    if (list_isEmpty(list)) {
        return reverse(filteredList);
    }
    else if (fn(list_first(list))) {
        filteredList = list_make(list_first(list), filteredList);
    }

    return filter_helper(list_rest(list), filteredList, fn);
}

//--------------------------------------------------------//
list_t rotate(list_t list, unsigned int n)
{
    if (list_isEmpty(list)) {
        return list;
    }

    return rotate_helper(list, list_make(), n);
}

static list_t rotate_helper(list_t list, list_t rotatedList, unsigned int n)
{
    if (list_isEmpty(list)) {
        list = reverse(rotatedList);
        rotatedList = list_make();
    }

    if (n == 0) {
        return append(list, reverse(rotatedList));
    }
    else {
        return rotate_helper(list_rest(list), list_make(list_first(list), rotatedList), n - 1);
    }
}

//--------------------------------------------------------//
list_t insert_list(list_t first, list_t second, unsigned int n)
{
    if (list_isEmpty(first)) {
        return second;
    }
    else if (list_isEmpty(second)) {
        return first;
    }

    return insert_list_helper(first, second, list_make(), n);
}

static list_t insert_list_helper(list_t first, list_t second, list_t combined, unsigned int n)
{
    if (n != 0) {
        return insert_list_helper(list_rest(first), second, list_make(list_first(first), combined), n - 1);
    }
    else {
        if (!list_isEmpty(second)) {
            return insert_list_helper(first, list_rest(second), list_make(list_first(second), combined), n);
        }
        else if (!list_isEmpty(first)) {
            return insert_list_helper(list_rest(first), second, list_make(list_first(first), combined), n);
        }
    }
    return reverse(combined);
}

//--------------------------------------------------------//
list_t chop(list_t l, unsigned int n)
{
    return chop_helper(reverse(l), n);
}

static list_t chop_helper(list_t list, unsigned int n)
{
    if (n == 0) {
        return reverse(list);
    }

    return chop_helper(list_rest(list), n - 1);
}

//--------------------------------------------------------//
int fib(int n)
{
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return fib(n - 1) + fib(n - 2);
}

//--------------------------------------------------------//
int fib_tail(int n)
{
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }

    return fib_tail_helper(n, 2, 1, 1);
}

static int fib_tail_helper(int n, int currentN, int currentNumber, int result)
{
    if (currentN == n) {
        return result;
    }

    return fib_tail_helper(n, currentN + 1, result, currentNumber + result);
}

//--------------------------------------------------------//
int tree_sum(tree_t tree)
{
    if (tree_isEmpty(tree)) {
        return 0;
    }

    return tree_elt(tree) + tree_sum(tree_left(tree)) + tree_sum(tree_right(tree));
}

//--------------------------------------------------------//
list_t traversal(tree_t tree)
{
    if (tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
        return list_make(tree_elt(tree), list_make());
    }
    else if (tree_isEmpty(tree_left(tree)) && !tree_isEmpty(tree_right(tree))) {
        return list_make(tree_elt(tree), traversal(tree_right(tree)));
    }
    else if (!tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))) {
        return reverse(list_make(tree_elt(tree), traversal(tree_left(tree))));
    }
    else {
        return append(traversal(tree_left(tree)), list_make(tree_elt(tree), traversal(tree_right(tree))));
    }
}

//--------------------------------------------------------//
bool contained_by(tree_t A, tree_t B)
{
    if (tree_covered_by(B, A))
    {
        return true;
    }
    else if (tree_isEmpty(tree_left(B)) && tree_isEmpty(tree_right(B)))
    {
        return false;
    }
    else
    {
        return contained_by(A, tree_left(B)) ||  contained_by(A, tree_right(B));
    }
}

static bool tree_covered_by(tree_t tree, tree_t tree_covered)
{
    if (tree_isEmpty(tree_left(tree)) &&
        tree_isEmpty(tree_right(tree)) &&
        tree_elt(tree) != tree_elt(tree_covered))
    {
        return false;
    }

    else if (tree_isEmpty(tree_left(tree)) &&
             !tree_isEmpty(tree_left(tree_covered)))
    {
        return false;
    }

    else if (tree_isEmpty(tree_right(tree)) &&
             !tree_isEmpty(tree_right(tree_covered)))
    {
        return false;
    }

    else if (tree_elt(tree) == tree_elt(tree_covered))
    {
        if (tree_isEmpty(tree_left(tree_covered)) &&
            tree_isEmpty(tree_right(tree_covered)))
        {
            return true;
        }
        else if (tree_isEmpty(tree_left(tree_covered)))
        {
            return tree_covered_by(tree_right(tree), tree_right(tree_covered));
        }
        else if (tree_isEmpty(tree_right(tree_covered)))
        {
            return tree_covered_by(tree_left(tree), tree_left(tree_covered));
        }
        else
        {
            return tree_covered_by(tree_left(tree), tree_left(tree_covered)) &&
                tree_covered_by(tree_right(tree), tree_right(tree_covered));
        }
    }

    else
    {
        return false;
    }
}

//--------------------------------------------------------//
tree_t insert_tree(int elt, tree_t tree)
{
    if (elt >= tree_elt(tree))
    {
        if (tree_isEmpty(tree_right(tree))) {
            return tree_make(tree_elt(tree), tree_left(tree), tree_make(elt, tree_make(), tree_make()));
        }
        else
        {
            return insert_tree(elt, tree_right(tree));
        }
    }
    else
    {
        if (tree_isEmpty(tree_left(tree))) {
            return tree_make(tree_elt(tree), tree_make(elt, tree_make(), tree_make()), tree_right(tree));
        }
        else
        {
            return insert_tree(elt, tree_left(tree));
        }
    }
}
