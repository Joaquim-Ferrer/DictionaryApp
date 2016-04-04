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
            load_dict(main_root);
            cout << "LOADED!\n";

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