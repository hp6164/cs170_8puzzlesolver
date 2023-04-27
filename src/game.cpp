#include "game.h"
#include <queue>

using namespace std;

Game::Game()
{
    initial = new Node();
    goal  = new Node({ {1, 2, 3}, {4, 5, 6}, {7, 8, 0} } );
}//end of constructor

Game::Game(vector<vector<int>> start)
{
    initial = new Node(start);
    goal  = new Node({ {1, 2, 3}, {4, 5, 6}, {7, 8, 0} } );
}//end of constructor

Game::Game(Node * start, Node * end)
{
    initial = start;
    goal = end;
}


//         void search_Euclidean();
//         void search_Misplace();
bool Game::search_UCS()
{
    // Tree* t = new Tree(initial);
    queue<Node*> frontier;
    frontier.push(initial);
    vector<Node*> explored;
    Node* curr;

    while(!frontier.empty())
    {        
        curr = frontier.front();
        curr->printNode();
        
            // curr->printNode();
        if(curr->getBoard() == goal->getBoard())
        {
            cout<<endl<<endl<<"Goal Reached"<<endl;
            printSolutionFound(curr);
            return true;
        }
        else//do the operations;
        {
            Node* temp = curr->Up();
            if(temp != nullptr && !(temp->in(explored)))
            {   
                // frontier.push(temp);
                cout<<"add up"<<endl;
            }
            temp = curr->Left();
            if(temp != nullptr && !(temp->in(explored)))
            {
                // temp->printNode();
                frontier.push(temp);
                cout<<"added left"<<endl;
            }
            temp = curr->Down();
            if(temp != nullptr && !(temp->in(explored)))
            {    
                // temp->printNode();
                frontier.push(temp);
                cout<<"added down"<<endl;
            }
            temp = curr->Right();
            if(temp != nullptr && !(temp->in(explored)))
            {
                // temp->printNode();
                frontier.push(temp);
                cout<<"added right" <<endl;
            }

            explored.push_back(curr);
            frontier.pop();
        }
        // string s;
        // cin>>s;
    }

    cout<<"frontier is empty"<<endl;
    return false;
}

void Game::printSolutionFound(Node* n)
{
    if(n->getLastMove() == START)
    {
        // n->printLastMove();
        cout<<n;
    }
    else
    {
        printSolutionFound(n->getParent());
        cout<<n;
    }
}