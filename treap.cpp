#include "header_treap.h"
using namespace treap;

//A random generator
int seed = 1;
default_random_engine gen (seed);
uniform_real_distribution<float> pri_dist (0.0,1.0);

/*
**Inserts a node in the binary tree whose root is root. The insertion is made
**to create a binary search tree in which the parent is always alphabetically
**bigger than ots left son and smaller than the right son. In addition, a son is always
**less searched than a parent.
*/ 
int treap::insert_word(Node *&root, string word, string translation) {
    if(root == NULL) {
        root = new_node(word, translation, NULL);
        return 1;
    }
}

Node *new_node(string word, string translation, Node *parent) {
    Node *new_node = new Node;
    new_node->word = word;
    new_node->translation = translation;
    new_node->tagged = false;

    new_node->parent = parent;
    new_node->son_left = NULL;
    new_node->son_right = NULL;

    new_node->rand_priority = pri_dist(gen);
    new_node->n_searches = 0;
}