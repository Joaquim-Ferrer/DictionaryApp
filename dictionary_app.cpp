using namespace std;
using namespace std::chrono;

#include "header_avl.h"
#include "header_treap.h"
#include "header_heapsort.h"
#include <chrono>

#define DEBUG 1
#define END_LOAD_WORD "end$dictionary"

void load_dict(AVL_Node *&root);
void debug(AVL_Node *root);
void load_array(treap::Node **array, treap::Node *root, int &first_index);

int main() {
    AVL_Node *main_root = NULL, *tagged_root = NULL;
    treap::Node *searched_root = NULL;
    string command, arguments, command_line;
    int n_searched_words = 0;

    while(1) {
        getline(cin, command_line);
        int first_space = command_line.find_first_of(' ');

        //No arguments
        if(first_space == -1) {
            command = command_line;
        }
        else {
            command = command_line.substr(0, first_space);
            arguments = command_line.substr(first_space + 1, command_line.length());
        }

        if(command.empty()) {
            break;
        }
        else if(command_line == "LOAD") {
            //Loads several words
            load_dict(main_root);
            cout << "LOADED!\n";
        }
        else if(command == "ADD") {
            //Adds a single word and translation passed as argument
            string word, translation;

            int delim_i = arguments.find_first_of(' ');
            word = arguments.substr(0, delim_i);
            translation = arguments.substr(delim_i + 1, arguments.length());

            if( insert_word(main_root, word, translation) ) {
                cout << "WORD ADDED!" << endl;
            }
            else {
                cout << "WORD ALREADY EXISTS..." << endl;
            }
        }
        else if(command == "SEARCH") {
            string word;

            word = arguments;

            AVL_Node *word_node_ptr;
            treap::Node *treap_node_ptr;
            //Search in the already searched words
            treap_node_ptr = treap::search_node(searched_root, word);
            if(treap_node_ptr != NULL) {
                cout << word << " " << treap_node_ptr->translation << endl;
                continue;
            }
            
            word_node_ptr = search_node(main_root, word);
            if(word_node_ptr == NULL) {
                cout << "THE WORD DOESNT EXIST..." << endl;
            }
            else {
                //if it's found in the main tree add it to the searched tree
                treap::insert_word(searched_root, word, word_node_ptr->translation);
                cout << word << " " << word_node_ptr->translation << endl;
                n_searched_words++;
            }
        }
        else if(command == "TAG") {
            string word;
            word = arguments;
            AVL_Node *word_node_ptr;

            word_node_ptr = search_node(main_root, word);
            if(word_node_ptr == NULL) {
                cout << "THE WORD DOESNT EXIST..." << endl;    
            }
            else {
                word_node_ptr->tagged = true;
                //Adds the word ti the binary tree of tagged words
                insert_word(tagged_root, word, word_node_ptr->translation);
                cout << word << " TAGGED" << endl;
            }
        }
        else if(command == "LIST") {
            print_node_and_descents_ordered(main_root);
            cout << "END OF LIST" << endl;
        }
        else if(command == "TAGGED_LIST") {
            print_node_and_descents_ordered(tagged_root);
            cout << "END OF TAGGED LIST" << endl;
        }
        else if(command == "MOST_ACCESSED_LIST") {
            int first_index = 0;
            treap::Node **array = new treap::Node*[n_searched_words];
            load_array(array, searched_root, first_index);
            print_ordered_treap(array, n_searched_words);
            free(array);
        }
        #ifdef DEBUG
            else if(command == "DEBUG") {
                debug(main_root);
                cout << "\nTreap: \n";
                treap::print_node_and_descents_ordered(searched_root);
            }
        #endif
    }
}

void load_dict(AVL_Node *&root) {
    string word, translation;

    while(1) {
        cin >> word;
        if(word == END_LOAD_WORD) {
            //ends the loading process
            break;
        }
        cin.get(); //To remove the extra space cin leaves in the buffer
        getline(cin, translation);

        insert_word(root, word, translation);
    }
    cin.get();
}

void load_array(treap::Node **array, treap::Node *root, int &first_index) {
    if(root == NULL) {
        return;
    }

    if(root->son_left != NULL) {
        load_array(array, root->son_left, first_index);
    }

    array[first_index] = root;
    first_index++;
    
    if(root->son_right != NULL) {
        load_array(array, root->son_right, first_index);
    }
}


void debug(AVL_Node *root) {
    if(root == NULL) {
        return;
    }

    if(root->son_left != NULL) {
        debug(root->son_left);
    }
    if(root->parent == NULL) {
        cout << root->word << " " << root->height << "\n";
    }
    else {
        cout << root->word << " " << root->height << " parent: "
            << root->parent->word << "\n";
    }
    if(root->son_right != NULL) {
        debug(root->son_right);
    }
}