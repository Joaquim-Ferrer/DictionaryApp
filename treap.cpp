#include "header_treap.h"
using namespace treap;

//#define TEST 1

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
    Node *node = NULL;

    while(1) {
        int comparison = word.compare(aux->word);
        if(comparison < 0) {
            if(aux->son_left == NULL) {
                //Insert new node to the left of the subtree
                node = new_node(word, translation, aux);
                aux->son_left = node;
                break;
            }
            aux = aux->son_left;
        }
        else if(comparison > 0) {
            if(aux->son_right == NULL) {
                //Insert new node to the riht of the subtree
                node = new_node(word, translation, aux);
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
    if(node->parent == NULL) {
        root = node;
    }
    return 1;
}


Node *treap::new_node(string word, string translation, Node *parent) {
    Node *new_node = new Node;
    new_node->word = word;
    new_node->translation = translation;
    new_node->tagged = false;

    new_node->parent = parent;
    new_node->son_left = NULL;
    new_node->son_right = NULL;

    new_node->rand_priority = pri_dist(gen);
    new_node->n_searches = 1;
    return new_node;
}

/*
**Makes the node node go up the tree through rotations until it's parent 
**either has a bigger n_searches or a bigger priority
*/
void treap::splay(Node *node) {
    if(node == NULL) {
        cout << "Can't splay NULL node" << endl;
        return;
    }
    
    while(1) {
        
        Node *parent = node->parent;
        if(parent == NULL || parent->n_searches > node->n_searches ||
        (parent->n_searches == node->n_searches && parent->rand_priority > node->rand_priority)) {
            return;
        }
        
        Node *g_parent = parent->parent;

        if(g_parent == NULL || 
        g_parent->n_searches > node->n_searches ||
        (g_parent->n_searches == node->n_searches && g_parent->rand_priority > node->rand_priority)) {
            //Only one operation needs to be done.
            if(parent->son_right == node) {
                //ZIG
                rotate_left(parent);
            }
            else {
                //ZIG
                rotate_right(parent);
            }
            return;
        }
        
        //ZIG ZIG OR ZIG ZAG STEP!! because node can go up two floors!
        if(parent == g_parent->son_right) {
            if(parent->son_right == node) {
                //ZIG ZIG
                rotate_left(parent);
            }
            else {
                //ZIG ZAG
                rotate_right(parent);
            }
            rotate_left(g_parent);
        }
        else {
            if(parent->son_left == node) {
                //ZIG ZIG
                rotate_right(parent);
            }
            else {
                //ZIG ZAG
                rotate_left(parent);
            }
            rotate_right(g_parent);
        }
    }
}

/*
**Rotates the subtree with root node to the right
*/
void treap::rotate_right(Node *node) {
    if(node->parent != NULL && node->parent->son_left == node) {
        node->parent->son_left = node->son_left;
    }
    else if(node->parent != NULL && node->parent->son_right == node) {
        node->parent->son_right = node->son_left;
    }
    node->son_left->parent = node->parent;
    

    Node *left_right_subtree = node->son_left->son_right;

    node->son_left->son_right = node;
    node->parent = node->son_left;
    node->son_left = left_right_subtree;
    if(left_right_subtree != NULL) {
        left_right_subtree->parent = node;
    }
}

/*
**Rotates the subtree with root node to the left
*/
void treap::rotate_left(Node *node) {
    if(node->parent != NULL && node->parent->son_right == node)
    {
        node->parent->son_right = node->son_right;
    }
    else if(node->parent != NULL && node->parent->son_left == node) {
        node->parent->son_left = node->son_right;
    }
    node->son_right->parent = node->parent;

    Node *right_left_subtree = node->son_right->son_left;

    node->son_right->son_left = node;
    node->parent = node->son_right;
    node->son_right = right_left_subtree;
    if(right_left_subtree != NULL) {
        right_left_subtree->parent = node;
    }
}

/*
**Searches for a word in the tree.
**Returns NULL if the word is not found;
**Returns the word's translation if the word is found
*/
Node *treap::search_node(Node *&root, string word) {
    Node *aux = root;

    while(aux != NULL) {
        int comparison = word.compare(aux->word);
        if(comparison < 0) {
            aux = aux->son_left;    
        }
        else if(comparison > 0) {
            aux = aux->son_right;
        }
        else {
            aux->n_searches++;
            splay(aux);
            if(aux->parent == NULL) {
                //If it's the new root update the root
                root = aux;
            }
            return aux;
        }
    }
    return NULL;
}

/*
**As the name says prints the root and its descendents in order
*/
void treap::print_node_and_descents_ordered(Node *root) {
    if(root == NULL) {
        return;
    }

    if(root->son_left != NULL) {
        print_node_and_descents_ordered(root->son_left);
    }
    
    if(root->parent == NULL) {
        cout << root->word << " searches:" << root->n_searches << " randon:" << root->rand_priority << "\n";
    }
    else {
        cout << root->word << " searches:" << root->n_searches << " parent: "
            << root->parent->word << " randon:" << root->rand_priority << "\n";
    }
    
    if(root->son_right != NULL) {
        print_node_and_descents_ordered(root->son_right);
    }
}

void treap::print_node(Node *node) {
    cout << node->word << endl;
}

#ifdef TEST
int main() {
    Node *root = NULL;
    insert_word(root, "w", "w");
    insert_word(root, "r", "r");

    print_node_and_descents_ordered(root);

    return 0;
}
#endif