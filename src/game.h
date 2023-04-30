
#ifndef __GAME_H
#define __GAME_H

#include <iostream>
#include "node.h"
#include "tree.h"

class Game
{
    private:
        Node* initial;
        Node* goal;

        // Tree* tree_ucs;
        // Tree* tree_euclidian;
        // Tree* tree_tile;

    public:
        Game();
        Game(vector<vector<int>>);
        Game(Node *, Node *);
        ~Game() 
        {
            delete initial;
            delete goal;
            // delete tree_ucs;
            // delete tree_euclidian;
            // delete tree_tile;
        }
        bool search_Euclidean();
        bool search_Misplace();
        bool search_UCS();

        void printSolutionFound(Node*);
        

};

#endif