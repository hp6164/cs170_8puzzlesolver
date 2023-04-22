
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
        Game(Node *);
        Game(Node *, Node *);
        ~Game() 
        {
            delete initial;
            delete goal;
        }
        void search_Euclidean();
        void search_Misplace();
        void search_UCS();

};

#endif