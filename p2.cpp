//
//  p2.cpp
//  p2.cpp
//
//  Created by John West on 9/19/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include "recursive.h"

static int sum_helper(int sum, list_t list);

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