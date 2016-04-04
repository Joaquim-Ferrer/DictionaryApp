#include "header_avl.h"
/*
**Insert node in the binary tree whose root is root. The innsertion is made 
to create an AVL binary tree.
**Returns 1 if the word was inserted or 0 if the word already existed.
*/
int insert_word(AVL_Node *&root, string word, string translation) {
    if(root == NULL) {
        root = new_node(word, translation, NULL);
        return 1;
    }

    AVL_Node *aux = root;

    while(1) {
        int comparison = word.compare(aux->word);
        if(comparison < 0) {
            if(aux->son_left == NULL) {
                //insert new node to the left of the subtree
                aux->son_left = new_node(word, translation, aux);
                break;
            }
            aux = aux->son_left;
        }
        else if(comparison > 0) {
            if(aux->son_right == NULL) {
                //insert new node to the right of the subtree
                aux->son_right = new_node(word, translation, aux); 
                break;
            }
            aux = aux->son_right;
        }
        else {
            //There's a node with that word
            return 0;
        }
    }

    //Go up the tree and correct the heights. If the height is changed then check
    //if rebalance is needed. Notice that aux begins in the parent of the new node
    while(aux != NULL) {
        update_height(aux);
        int balance = get_balance(aux);
        if(balance == 2) {
            if(get_balance(aux->son_right) == -1) {
                rotate_right(aux->son_right);//Double rotation
            }
            rotate_left(aux);
            if(aux == root) {
                //Updates the root of the tree if it shifts
                root = aux->parent;
            }
        }
        else if(balance == -2) {
            if(get_balance(aux->son_left) == 1) {
                rotate_left(aux->son_left);//Double rotation
            }
            rotate_right(aux);
            if(aux == root) {
                //Updates the root of the tree if it shifts
                root = aux->parent;
            }
        }
        aux = aux->parent;
    }
    return 1;
}

/*
**Searches for a word in the tree.
**Returns NULL if the word is not found;
**Returns the word's translation if the word is found
*/
AVL_Node *search_node(AVL_Node *root, string word) {
    AVL_Node *aux = root;

    while(aux != NULL) {
        int comparison = word.compare(aux->word);
        if(comparison < 0) {
            aux = aux->son_left;    
        }
        else if(comparison > 0) {
            aux = aux->son_right;
        }
        else {
            return aux;
        }
    }

    return NULL;
}

AVL_Node *new_node(string word, string translation, AVL_Node *parent) {
    AVL_Node *new_node = new AVL_Node;
    new_node->word = word;
    new_node->translation = translation;
    
    new_node->tagged = false;
    new_node->height = 1;

    new_node->parent = parent;
    new_node->son_right = NULL;
    new_node->son_left = NULL;

    return new_node;
}

/*
**Rotates the subtree with root node to the right
*/
void rotate_right(AVL_Node *node) {
    if(node->parent != NULL && node->parent->son_left == node) {
        node->parent->son_left = node->son_left;
    }
    else if(node->parent != NULL && node->parent->son_right == node) {
        node->parent->son_right = node->son_left;
    }
    node->son_left->parent = node->parent;
    

    AVL_Node *left_right_subtree = node->son_left->son_right;

    node->son_left->son_right = node;
    node->parent = node->son_left;
    node->son_left = left_right_subtree;
    if(left_right_subtree != NULL) {
        left_right_subtree->parent = node;
    }
    //Update heights. Heights will be recalculated if its children change.
    //The nodes whose children change are node and node->son_left(which is now
    //node->parent)
    update_height(node);
    update_height(node->parent);

}

/*
**Rotates the subtree with root node to the left
*/
void rotate_left(AVL_Node *node) {
    if(node->parent != NULL && node->parent->son_right == node)
    {
        node->parent->son_right = node->son_right;
    }
    else if(node->parent != NULL && node->parent->son_left == node) {
        node->parent->son_left = node->son_right;
    }
    node->son_right->parent = node->parent;

    AVL_Node *right_left_subtree = node->son_right->son_left;

    node->son_right->son_left = node;
    node->parent = node->son_right;
    node->son_right = right_left_subtree;
    if(right_left_subtree != NULL) {
        right_left_subtree->parent = node;
    }
    //Update heights. Heights will be recalculated if its children change.
    //The nodes whose children change are node and node->son_right(which is now node->parent)
    update_height(node);
    update_height(node->parent);

}

/*
**Updates the height of the node's presuming it's children heights are correct
*/
void update_height(AVL_Node *node) {
    int height_right = 0;
    int height_left = 0;
    
    if(node->son_right != NULL) {
        height_right = node->son_right->height;
    }
    if(node->son_left != NULL) {
        height_left = node->son_left->height;
    }

    node->height = max(height_right, height_left) + 1;
}

/*
**Returns the balance factor of the Node node
*/
int get_balance(AVL_Node *node) {
    int height_right = 0;
    int height_left = 0;
    
    if(node->son_right != NULL) {
        height_right = node->son_right->height;
    }
    if(node->son_left != NULL) {
        height_left = node->son_left->height;
    }

    return height_right - height_left;
}

/*
**Returns the max of 2 integers
*/
int max(int a, int b) {
    if(a>b) {
        return a;
    }
    else {
        return b;
    }
}

/*
**As the name says prints the root and its descendents in order
*/
void print_node_and_descents_ordered(AVL_Node *root) {
    if(root == NULL) {
        return;
    }

    if(root->son_left != NULL) {
        print_node_and_descents_ordered(root->son_left);
    }
    cout << root->word << "\n";
    if(root->son_right != NULL) {
        print_node_and_descents_ordered(root->son_right);
    }
}