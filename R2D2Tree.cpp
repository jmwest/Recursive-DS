//
//  R2D2Tree.cpp
//  p2.cpp
//
//  Created by John West on 10/19/13.
//  Copyright (c) 2013 John West. All rights reserved.
//
#include <iostream>
#include "p2.h"
#include "recursive.h"

using namespace std;

list_t decode(tree_t t, list_t key)
{
	if (tree_isEmpty(t)) {
		return list_make();
	}

	if (list_first(key)) {
		return append(decode(tree_left(t), list_rest(key)),
					  list_make(tree_elt(t), decode(tree_right(t), list_rest(key))));
	}
	else {
		return append(decode(tree_left(t), list_rest(key)),
					  decode(tree_right(t), list_rest(key)));
	}
}

bool list_equal(list_t l1, list_t l2)
// EFFECTS: returns true iff l1 == l2.
{
    if (list_isEmpty(l1) && list_isEmpty(l2)) {
		return true;
    } else if (list_isEmpty(l1) || list_isEmpty(l2)) {
		return false;
    } else if (list_first(l1) != list_first(l2)) {
		return false;
    } else {
		return list_equal(list_rest(l1), list_rest(l2));
    }
}

int main()
{
	tree_t tree = tree_make(5,
					  tree_make(7,
								tree_make(3, tree_make(), tree_make()),
								tree_make(1, tree_make(), tree_make())),
					  tree_make(9,
								tree_make(2, tree_make(), tree_make()),
								tree_make(8, tree_make(), tree_make())));

	list_t key1 = list_make(1, list_make(0, list_make(1, list_make())));
	list_t key2 = list_make(0, list_make(0, list_make(1, list_make())));
	list_t key3 = list_make(1, list_make(1, list_make(1, list_make())));
	list_t key4 = list_make(0, list_make(0, list_make(0, list_make())));

	list_t answer1 = list_make(3, list_make(1, list_make(5, list_make(2, list_make(8, list_make())))));
	list_t answer2 = list_make(3, list_make(1, list_make(2, list_make(8, list_make()))));
	list_t answer3 = list_make(3, list_make(7, list_make(1, list_make(5, list_make(2, list_make(9, list_make(8, list_make())))))));
	list_t answer4 = list_make();

	if (list_equal(answer1, decode(tree, key1))) {
		cout << "Yahoo!" << endl;
	}
	if (list_equal(answer2, decode(tree, key2))) {
		cout << "Can someone get this walking carpet out of my way?" << endl;
	}
	if (list_equal(answer3, decode(tree, key3))) {
		cout << "Use the force, Luke" << endl;
	}
	if (list_equal(answer4, decode(tree, key4))) {
		cout << "Somehow, I know. Somehow I've always known" << endl;
	}

	return 0;
}