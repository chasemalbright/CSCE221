#include <iostream>
#include <string>

#include "BinarySearchTree.h"

int main() {
    // Give us a random tree each time
    srand(time(NULL));
    // 15 elements in the tree
    constexpr int TREE_SIZE = 5;

    BinarySearchTree<std::string, int> simpleTree;
    //std::string names[TREE_SIZE] {"Teresa", "Carlos", "Nkemdi", "Dante", "Alexander", "Evelyn", "Dillon", "Thomas", "Armando", "Mariel", "Furkan", "Anjali", "Jeremy", "Clayton", "Jessica"};
    std::string names[TREE_SIZE] {"A","B","F","C", "J"};
    for (int i = 0; i < TREE_SIZE; ++i) {
        simpleTree.insert( { names[i], rand() % TREE_SIZE } );
    }

    //printTree(simpleTree);
    printLevelByLevel(simpleTree);
}