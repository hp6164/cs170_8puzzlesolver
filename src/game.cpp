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

/**
 * Original, does not use tree
*/
// bool Game::search_UCS()
// {
//     queue<Node*> frontier;
//     frontier.push(initial);
//     vector<Node*> explored;
//     Node* curr;

//     while(!frontier.empty())
//     {        
//         curr = frontier.front();
//         curr->printNode();
        
//             // curr->printNode();
//         if(curr->getBoard() == goal->getBoard())
//         {
//             cout<<endl<<endl<<"Goal Reached"<<endl;
//             printSolutionFound(curr);
//             return true;
//         }
//         else//do the operations;
//         {
            
//             Node* temp = curr->Up();
//             if(temp != nullptr && !(temp->in(explored)))
//             {   
//                 // frontier.push(temp);
//                 cout<<"add up"<<endl;
//             }
//             temp = curr->Left();
//             if(temp != nullptr && !(temp->in(explored)))
//             {
//                 // temp->printNode();
//                 frontier.push(temp);
//                 cout<<"added left"<<endl;
//             }
//             temp = curr->Down();
//             if(temp != nullptr && !(temp->in(explored)))
//             {    
//                 // temp->printNode();
//                 frontier.push(temp);
//                 cout<<"added down"<<endl;
//             }
//             temp = curr->Right();
//             if(temp != nullptr && !(temp->in(explored)))
//             {
//                 // temp->printNode();
//                 frontier.push(temp);
//                 cout<<"added right" <<endl;
//             }

//             explored.push_back(curr);
//             frontier.pop();
//         }
//         // string s;
//         // cin>>s;
//     }

//     cout<<"frontier is empty"<<endl;
//     return false;
// }

bool Game::search_UCS()
{
    
    Tree* t = new Tree(initial, goal);//create tree to keep track of stats
    t->startTime();
    queue<Node*> frontier;//initialize the frontier with the tree's root node
    frontier.push(t->getRoot());
    
    vector<Node*> explored;//keep track of boards you have already explored
    Node* curr;// curr is the current node to be expanded

    while(!frontier.empty())//if frontier is empty no solution was found, otherwise continue searching for solution
    {        
        curr = frontier.front();// make curr the next node in the frontier
        // curr->printNode();
        cout<<"Current Hash: "<<curr->createHash()<<"\t cost: "<<curr->getCost()<<endl;
        
        
        if(curr->getBoard() == goal->getBoard())//if curr is equal to goal that means we have expanded up to our goal, and can conclude goal reached optimally 
        {
            cout<<endl<<endl<<"Goal Reached"<<endl;
            t->stopTime();
            t->updateGoal(curr);
            printSolutionFound(t->getGoal());
            t->printStats();
            return true;
        }
        else//do the operations;
        {
        // general idea: 
            // try operation
            // if operation possible then make sure its not undoing progress by returning to parent
            //  then check if another combination of moves has already found that board combination
            //      if it has then dont bother expanding that node further(this is a UCS with equal costs, essentiall a BFS)
            //          thus if its already been encoutered the same board combination can be found at the same depth or earlier
            //          meaning no need to add the board to the tree again, regarldess of that board combination has been
            //          expanded or not  
            //      otherwise add the branch and push to the hash map.
            explored.push_back(curr);
            frontier.pop();
            t->increaseNodeExpanded();
            // string s;
            // cin>>s;
            Node* temp = curr->Up();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    frontier.push(temp);        //add it to frontier
                    curr->addUpChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"add up"<<endl;       //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    curr->addUpChild(t->returnNodeByHash(temp->createHash())); 
                }
            } //end of check Up operator
            temp = curr->Left();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    frontier.push(temp);        //add it to frontier
                    curr->addLeftChild(temp);   //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"add left"<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                }
                else
                {
                    //make it a graph implementation, since it was already seen, we can make the 
                        //child of current point to the already seen node
                    curr->addLeftChild(t->returnNodeByHash(temp->createHash())); 
                }
            }//end of check for left op
            temp = curr->Down();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    frontier.push(temp);        //add it to frontier
                    curr->addDownChild(temp);   //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"add down"<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                }
                else
                {
                    //make it a graph implementation, since it was already seen, we can make the 
                        //child of current point to the already seen node
                    curr->addDownChild(t->returnNodeByHash(temp->createHash())); 
                }
            }//end of check for down op
            temp = curr->Right();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    frontier.push(temp);        //add it to frontier
                    curr->addRightChild(temp);  //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"add right"<<endl;    //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                }
                else
                {
                    //make it a graph implementation, since it was already seen, we can make the 
                        //child of current point to the already seen node
                    curr->addRightChild(t->returnNodeByHash(temp->createHash())); 
                }
            }//end of check for left op
            t->checkNewMaxQueueSize(frontier.size());
        }
        // string s;
        // cin>>s;
    }

    cout<<"frontier is empty"<<endl;
    return false;
}

void Game::printSolutionFound(Node* n)
{
    // cout<<"Test"<<endl;
    // n->printAllNodeData();
    // cout<<endl;
    if(n->getLastMove() == START)
    {
        // n->printLastMove();
        // cout<<"reaced end"<<endl;
        cout<<n;
    }
    else
    {
        printSolutionFound(n->getParent());
        cout<<n;
    }
}