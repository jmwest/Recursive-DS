//
//  p2.cpp
//  p2.cpp
//
//  Created by John West on 9/19/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include "p2.h"

static int sum_helper(int sum, list_t list);
static int product_helper(int product, list_t list);
static int addNumbers(int x, int y);
static int multiplyNumbers(int x, int y);
static int algebraic_helper(int result, list_t list, int (*fn)(int, int));

static list_t reverse_helper(list_t list, list_t reverseList);
static list_t append_helper(list_t first, list_t second);

static list_t filter_odd_or_even_helper(list_t list, list_t filteredList, int remainderValue);
static list_t filter_helper(list_t list, list_t filteredList, bool (*fn)(int));

static list_t insert_list_helper(list_t firstBeginning, list_t firstEnding, list_t second, unsigned int n);

int sum(list_t list)
{
    return sum_helper(0, list);
}

static int sum_helper(int sum, list_t list)
{
    if (list_isEmpty(list))
    {
        return sum;
    }

    return sum_helper(list_first(list) + sum, list_rest(list));
}

int product(list_t list)
{
    return product_helper(1, list);
}

static int addNumbers(int x, int y)
{
    return x + y;
}

static int multiplyNumbers(int x, int y)
{
    return x * y;
}

static int product_helper(int product, list_t list)
{
    if (list_isEmpty(list))
    {
        return product;
    }
    
    return product_helper(list_first(list) * product, list_rest(list));
}

int accumulate(list_t list, int (*fn)(int, int), int identity)
{
    if (list_isEmpty(list)) {
        return identity;
    }

    return algebraic_helper(fn(identity, list_first(list)), list_rest(list), fn);
}

static int algebraic_helper(int result, list_t list, int (*fn)(int, int))
{
    if (list_isEmpty(list)) {
        return result;
    }

    return algebraic_helper(fn(result, list_first(list)), list_rest(list), fn);
}

list_t reverse(list_t list)
{
    list_t reverseList = list_make();

    return reverse_helper(list, reverseList);
}

static list_t reverse_helper(list_t list, list_t reverseList)
{
    if (list_isEmpty(list)) {
        return reverseList;
    }

    return reverse_helper(list_rest(list), list_make(list_first(list), reverseList));
}

list_t append(list_t first, list_t second)
{
    return append_helper(reverse(first), second);
}

list_t append_helper(list_t first, list_t second)
{
    if (!list_isEmpty(first)) {
        first = list_rest(first);
        second = list_make(list_first(first), second);

        return append_helper(first, second);
    }
    else {
        return second;
    }
}

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

    return filter_helper(list, filteredList, fn);
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
    if (list_isEmpty(first)) {
        return second;
    }
    else if (list_isEmpty(second)) {
        return first;
    }

    return insert_list_helper(first, list_make(), second, n);
}

static list_t insert_list_helper(list_t firstBeginning, list_t firstEnding, list_t second, unsigned int n)
{
    if (n == 1) {

    }
    return second;
}

list_t chop(list_t l, unsigned int n)
{
    return l;
}