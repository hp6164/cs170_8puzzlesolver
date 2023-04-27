
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
    public:
        // Game(Node *);
        Game();
        Game(vector<vector<int>>);
        Game(Node *, Node *);
        ~Game() 
        {
            delete initial;
            delete goal;
        }
        bool search_Euclidean();
        bool search_Misplace();
        bool search_UCS();

        void printSolutionFound(Node*);

};

#endif