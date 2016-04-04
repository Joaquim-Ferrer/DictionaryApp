/*
**Insert node in the binary tree whose root is root. The innsertion is made 
to create an AVL binary tree.
**Returns 1 if the word was inserted or 0 if the word already existed.
*/
int insert_word(AVL_Node *&root, string word, string translation) {
    if(root == NULL) {
        Node *new_node = new_node(word, translation, NULL);
        root = new_node;
        return 1;
    }

    AVL_Node = root;

    while(1) {
        int comparison = word.compare(aux->word);
        if(comparison < 0) {
            if(aux->son_left == NULL) {
                //insert new node to the left of the subtree
                AVL_Node *new_node = new_node(word, translation, aux);
                aux->son_left = new_node;
                break;
            }
            aux = aux->son_left;
        }
        else if(comparison > 0) {
            if(aux->son_right == NULL) {
                //insert new node to the right of the subtree
                AVL_Node *new_node = new_node(word, translation, aux); 
                aux->son_right = new_node;
                break;
            }
            aux = aux->son_right;
        }
        else {
            //There's a node with that word
            return 0;
        }
    }
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
    Node_AVL *new_node = new Node_AVL;
    new_node->word = word;
    new_node->translation = translation;
    
    new_node->tagged->false;
    new_node->height = 1;

    new_node->parent = parent;
    new_node->son_right = NULL;
    new_node->son_left = NULL;

    return new_Node;
}

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