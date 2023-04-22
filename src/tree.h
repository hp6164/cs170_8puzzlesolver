#ifndef __TREE_H
#define __TREE_H

#include <iostream>
#include "node.h"

class Tree
{
    private:
        Node* root;
        int nodesExpanded;
        int nodesVisited;
        
        // can optimize with hashmap of each node in tree to avoid duplicates
    public:
        Tree();
};

#endif