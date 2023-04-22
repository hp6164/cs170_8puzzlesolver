#include "game.h"


Game::Game(Node * start)
{
    initial = start;
    goal  = new Node({ {1, 2, 3}, {4, 5, 6}, {7, 8, 0} } );
}//end of constructor

Game::Game(Node * start, Node * end)
{
    initial = start;
    goal = end;
}


//         void search_Euclidean();
//         void search_Misplace();
//         void search_UCS();