#ifndef HEADER_HEAP
#define HEADER_HEAP

using namespace std;
using namespace treap;

#include <iostream>
#include <string>

void print_ordered_treap(Node *array[], int size);
int get_parent(int i);
int get_son_left(int i);
int get_son_right(int i);
void heapify(Node *array[], int i, int size);
int compare_nodes(Node *a, Node *b);

#endif