#include "header_treap.h"
#include "header_heapsort.h"

//#define TEST 1

void print_ordered_treap(Node *array[], int size) {
    for(int i = 1; i < size; i++) {
        heapify(array, i, size);
    }

    while(size != 0) {
        print_node(array[0]);
        swap(array[0], array[size - 1]);
        size--;

        int leaf_root = 0;
        while(1) {
            int i_left = get_son_left(leaf_root);
            int i_right = get_son_right(leaf_root);

            if(i_left >= size && i_right >= size) {
                break;
            }

            if(i_right >= size || compare_nodes(array[i_left], array[i_right]) > 0) {
                if(compare_nodes(array[leaf_root], array[i_left]) < 0) {
                    //THe left child is the bigger so swaps with leaf root
                    swap(array[leaf_root], array[i_left]);
                    leaf_root = i_left;
                    continue;
                }
                else {
                    //The leaf_root is in its place so go on
                    break;
                }
            }
            else if(compare_nodes(array[i_left], array[i_right]) <= 0) {
                if(compare_nodes(array[leaf_root], array[i_right]) < 0) {
                    //The right child is the bigger so swaps
                    swap(array[leaf_root], array[i_right]);
                    leaf_root = i_right;
                    continue;
                }
                else {
                    //The leaf_root is in its place so go on
                    break;
                }
            }
            else {
                break;
            }
        }
    }
}


/*
**Returns the index of the parent of the node with index i
*/
int get_parent(int i) {
    return i/2;
}

/*
**Returns the index of the left son of the node with index i
*/
int get_son_left(int i) {
    return i*2 + 1;
}

/*
**Returns the index of the right son of the node with index i
*/
int get_son_right(int i) {
    return i*2 + 2;
}

void heapify(Node *array[], int i, int size) {
    int i_parent = get_parent(i);

    //In case i = 0 it will pass
    if(compare_nodes(array[i], array[i_parent]) > 0) {
        swap(array[i], array[i_parent]);
        heapify(array, i_parent, size);
    }
}

/*
**Returns positive if node a has more searches or is alphabeticaly smmaller than node b
**Else returns 0 or negative
*/
int compare_nodes(Node *a, Node *b) {
    if(a->n_searches > b->n_searches) {
        return 1;
    }
    else if(a->n_searches == b->n_searches) {
        return (b->word).compare(a->word);
    }
    else {
        return -1;
    }
}

#ifdef TEST
int main() {
    Node **array = new Node*[6];
    Node *a = new_node("f", "a", NULL);
    array[0] = a;
    Node *b = new_node("b", "a", NULL);
    array[1] = b;
    Node *c = new_node("a", "a", NULL);
    array[2] = c;
    Node *d = new_node("p", "a", NULL);
    array[3] = d;
    d->n_searches = 2;
    Node *e= new_node("y", "a", NULL);
    array[4] = e;
    Node *f = new_node("w", "a", NULL);
    array[5] = f;
    print_ordered_treap(array, 6);

    return 0;
}
#endif