#include <iostream>
#include "p2.h"

using namespace std;

bool checkListsEqual(list_t first, list_t second, bool equal)
// REQUIRES: equal is passed in as true
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

bool tree_equal(tree_t t1, tree_t t2)
    // EFFECTS: returns true iff t1 == t2
{
    if (tree_isEmpty(t1) && tree_isEmpty(t2)) {
	return true;
    } else if (tree_isEmpty(t1) || tree_isEmpty(t2)) {
	return false;
    } else {
	return ((tree_elt(t1) == tree_elt(t2)) 
		&& tree_equal(tree_left(t1), tree_left(t2))
		&& tree_equal(tree_right(t1), tree_right(t2)));
    }
}

int main()
{
	tree_t empty = tree_make();
    tree_t start = tree_make(2,
			     tree_make(1, tree_make(), tree_make()),
			     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
			   tree_make(1, tree_make(), tree_make()),
			   tree_make(4, 
				     tree_make(3, tree_make(), tree_make()),
				     tree_make()));

    tree_t second = tree_make(2,
                              tree_make(1, tree_make(), tree_make(1, tree_make(), tree_make())),
                              tree_make(4,
                                        tree_make(3, tree_make(), tree_make()),
                                        tree_make(5, tree_make(),
                                                  tree_make(7,
                                                        tree_make(6, tree_make(),tree_make()),
                                                        tree_make(7, tree_make(), tree_make())))));
    tree_t secondInsertOne = tree_make(2,
                              tree_make(1, tree_make(),
                                        tree_make(1, tree_make(),
                                                  tree_make(1, tree_make(), tree_make()))),
                              tree_make(4,
                                        tree_make(3, tree_make(), tree_make()),
                                        tree_make(5, tree_make(),
                                                  tree_make(7,
                                                            tree_make(6, tree_make(),tree_make()),
                                                            tree_make(7, tree_make(), tree_make())))));

    tree_t secondInsertNine = tree_make(2,
                              tree_make(1, tree_make(), tree_make(1, tree_make(), tree_make())),
                              tree_make(4,
                                        tree_make(3, tree_make(), tree_make()),
                                        tree_make(5, tree_make(),
                                                  tree_make(7,
                                                            tree_make(6, tree_make(), tree_make()),
                                                            tree_make(7, tree_make(),
                                                                      tree_make(9, tree_make(), tree_make()))))));

    int passed = 0;

    if (contained_by(start, end)) {
        cout << "\nst,e\n";
        passed++;
    }

    if (contained_by(end, start)) {
        cout << "e,st\n";
    }
    else { passed++; }

    if (contained_by(start, start)) {
        cout << "st,st\n";
        passed++;
    }

    if (contained_by(second, start)) {
        cout << "se,st\n";
    }
    else { passed++; }

    if (contained_by(second, secondInsertNine)) {
        cout << "se,se9\n";
        passed++;
    }

    if (contained_by(secondInsertNine, secondInsertOne)) {
        cout << "se9,se1\n";
    }
    else { passed++; }

	if (contained_by(empty, secondInsertNine)) {
		std::cout << "empty, se9\n";
		passed++;
	}

    list_t correct1 = list_make(1, list_make(2, list_make(4, list_make())));
    list_t correct2 = list_make(1, list_make(2, list_make(3, list_make(4, list_make()))));
    list_t correct3 = list_make(1, list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, list_make(6, list_make(7, list_make(7, list_make())))))))));
    list_t correct4 = list_make(1, list_make(1, list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, list_make(6, list_make(7, list_make(7, list_make()))))))))));
    list_t correct5 = list_make(1, list_make(1, list_make(2, list_make(3, list_make(4, list_make(5, list_make(6, list_make(7, list_make(7, list_make(9, list_make()))))))))));
	list_t correctEmpty = list_make();

    list_t travel1 = traversal(start);
    list_t travel2 = traversal(end);
    list_t travel3 = traversal(second);
    list_t travel4 = traversal(secondInsertOne);
    list_t travel5 = traversal(secondInsertNine);
	list_t travelEmpty = traversal(empty);

    if (checkListsEqual(correct1, travel1, true)) {
        passed++;
    }
    if (checkListsEqual(correct2, travel2, true)) {
        passed++;
    }
    if (checkListsEqual(correct3, travel3, true)) {
        passed++;
    }
    if (checkListsEqual(correct4, travel4, true)) {
        passed++;
    }
    if (checkListsEqual(correct5, travel5, true)) {
        passed++;
    }
	if (checkListsEqual(correctEmpty, travelEmpty, true)) {
		cout << "got the empty" << endl;
	}

    list_print(travel1);
    cout << endl;
    list_print(travel2);
    cout << endl;
    list_print(travel3);
    cout << endl;
    list_print(travel4);
    cout << endl;
    list_print(travel5);
    cout << endl;

    int sum1 = tree_sum(start);
    int sum2 = tree_sum(end);
    int sum3 = tree_sum(second);
    int sum4 = tree_sum(secondInsertOne);
    int sum5 = tree_sum(secondInsertNine);

    if (sum1 == 7) {
        passed++;
    }
    if (sum2 == 10) {
        passed++;
    }
    if (sum3 == 36) {
        passed++;
    }
    if (sum4 == 37) {
        passed++;
    }
    if (sum5 == 45) {
        passed++;
    }

    cout << sum1 << endl;
    cout << sum2 << endl;
    cout << sum3 << endl;
    cout << sum4 << endl;
    cout << sum5 << endl;
    
    cout << passed << " out of 17!\n\n";

    tree_t candidate = insert_tree(3, start);
    tree_print(end);
    cout << endl;

    tree_print(candidate);
    cout << endl;

    if (tree_equal(candidate, end)) {
	cout << "Success!\n";
    } else {
	cout << "Failed\n";
    }

    tree_t secondResultOne = insert_tree(1, second);
    tree_print(secondInsertOne);
    cout << endl;

    tree_print(secondResultOne);
    cout << endl;

    if (tree_equal(secondInsertOne, secondResultOne)) {
        cout << "Success!\n\n\n\n";
    }
    else {
        cout << "Failed\n\n\n\n";
    }

    tree_t secondResultNine = insert_tree(9, second);
    tree_print(secondInsertNine);
    cout << endl;
    
    tree_print(secondResultNine);
    cout << endl;
    
    if (tree_equal(secondInsertNine, secondResultNine)) {
        cout << "Success!\n\n\n\n";
    }
    else {
        cout << "Failed\n\n\n\n";
    }

    return 0;
}
