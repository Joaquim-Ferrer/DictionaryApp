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

    Node *aux = root;

    while(1) {
        int comparison = word.compare(aux->word);
        if(comparison < 0) {
            if(aux->son_left == NULL) {
                //Insert new node to the left of the subtree
                Node *node = new_node(word, translation, aux);
                aux->son_left = node;
                break;
            }
            aux = aux->son_left;
        }
        else if(comparison > 0) {
            if(aux->son_right == NULL) {
                //Insert new node to the riht of the subtree
                Node *node = new_node(word, translation, aux);
                aux->son_right = node;
                break;
            }
            aux = aux->son_right;
        }
        else {
            //There's a node wih that word already
            return 0;
        }
    }
    //The new node goes up the tree while its parent ha n_searches 1 and a 
    //rand_priority lower than his
    splay(node);
    return 1;
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
    new_node->n_searches = 1;
}