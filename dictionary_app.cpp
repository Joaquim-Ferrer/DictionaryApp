using namespace std;

#include "header_avl.h"
#include <iostream>

#define END_LOAD_WORD "end$dictionary"

void load_dict(AVL_Node *&root);

int main() {
    AVL_Node *main_root = NULL, *tagged_root = NULL;
    string command, arguments, command_line;

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

            word_node_ptr = search_node(main_root, word);
            if(word_node_ptr == NULL) {
                cout << "THE WORD DOESNT EXIST..." << endl;
            }
            else {
                cout << word << " " << word_node_ptr->translation << endl;
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