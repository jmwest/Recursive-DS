//
//  ComparatorTree.cpp
//  p2.cpp
//
//  Created by John West on 10/21/13.
//  Copyright (c) 2013 John West. All rights reserved.
//

#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

typedef bool (*Comparator)(int, int);

bool ascending(int a, int b);

bool tree_isSorted(tree_t tree, Comparator comp)
{
	if (tree_isEmpty(tree)) {
		return true;
	}

	if (tree_isEmpty(tree_left(tree))) {
		if (tree_isEmpty(tree_right(tree))) {
			return true;
		}
		else {
			return tree_isSorted(tree_right(tree), comp);
		}
	}
	else if (tree_isEmpty(tree_right(tree))) {
		return tree_isSorted(tree_left(tree), comp);
	}

	if (comp(tree_elt(tree_left(tree)), tree_elt(tree)) && comp(tree_elt(tree), tree_elt(tree_right(tree)))) {
		return tree_isSorted(tree_left(tree), comp) && tree_isSorted(tree_right(tree), comp);
	}
	else return false;
}

int main()
{
	tree_t tree = tree_make(5,
							tree_make(3,
									  tree_make(1, tree_make(), tree_make()),
									  tree_make(4, tree_make(), tree_make())),
							tree_make(7,
									  tree_make(6, tree_make(), tree_make()),
									  tree_make(8, tree_make(), tree_make())));

	if (tree_isSorted(tree, ascending)) {
		cout << "We did it!" << endl;
	}

	return 0;
}

bool ascending(int a, int b)
{
	return a < b;
}