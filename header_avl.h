#ifndef HEADER_AVL
#define HEADER_AVL

using namespace std;

#include <string>

struct AVL_Node {
    AVL_Node *parent; 
    AVL_Node *son_left;  
    AVL_Node *son_right;

    string word;
    string translation;
    bool tagged;

    int height;
};

/*
**Inserts a word in an AVL tree. In case the tree gets unbalanced, it gets balanced

*/
int insert_word(AVL_Node *&root, string word, string translation);

/*
**Searches a node in the subtree with root root with the word word 
*/
AVL_Node *search_node(AVL_Node *root, string word);

/*
**Creates a new node with it's default values, word word, translation translation
**and parent parent
*/
AVL_Node *new_node(string word, string translation, AVL_Node *parent);

/*
**Rotates the subtree with root node to the right
*/
void rotate_right(AVL_Node *node);

/*
**Rotates the subtree with root node to the left
*/
void rotate_left(AVL_Node *node);

/*
**Updates the height of a node considering the height of its children.
**Is only correct if it's children heights are correct or are NULL
*/
void update_height(AVL_Node *node);

/*
**Gets the balance factor of a node. It will be positive if its right subtree
**is deeper than its left subtree. 
**The possible return values are between -2 and 2.
*/
int get_balance(AVL_Node *node);

/*
**Returns the biggest integer, a or b
*/
int max(int a, int b);

#endif