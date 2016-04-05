#ifndef HEADER_TREAP
#define HEADER_TREAP

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
}