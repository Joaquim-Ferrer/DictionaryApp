#ifndef HEADER_H
#define HEADER_H

struct AVL_Node {
    Node *parent; 
    Node *son_left;  
    Node *son_right;

    string word;
    string translation;
    bool tagged;

    int height;
};

#endif