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
        ~Game();
        void search_Euclidean(Node *);
        void search_Misplace(Node *);
        void search_UCS(Node *);

};

#endif