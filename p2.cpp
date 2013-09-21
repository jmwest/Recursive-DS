//
//  p2.cpp
//  p2.cpp
//
//  Created by John West on 9/19/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include "recursive.h"
#include "p2.h"

static int sum_helper(int sum, list_t list);
static int product_helper(int product, list_t list);
static list_t reverse_helper(list_t list, list_t reverseList);

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
    
    return 0;
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