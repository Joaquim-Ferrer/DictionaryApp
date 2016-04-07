#ifndef HEADER_TREAP
#define HEADER_TREAP

using namespace std;

#include <iostream>
#include <string>
#include <random>

namespace treap {
    struct Node {
        Node *parent;
        Node *son_left;
        Node *son_right;

        string word;
        string translation;
        bool tagged;

        float rand_priority;
        long int n_searches;
    };

int insert_word(Node *&root, string word, string translation);
Node *new_node(string word, string translation, Node *parent);
void splay(Node *node);
void rotate_right(Node *node);
void rotate_left(Node *node);
Node *search_node(Node *root, string word);
void print_node_and_descents_ordered(Node *root);

}

#endif