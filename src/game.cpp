#include "game.h"
#include <queue>
#include "compareNode.h"

using namespace std;

Game::Game()
{
    initial = new Node();
    goal  = new Node({ {1, 2, 3}, {4, 5, 6}, {7, 8, 0} } );
}//end of constructor

Game::Game(vector<vector<int>> start)
{
    initial = new Node(start);
    // goal  = new Node({ {1, 2, 3}, {4, 5, 6}, {7, 8, 0} } ); //#TODO fix it so it automatically creates a goal state based on the initial board
    vector<vector<int>> goalBoard = initial->getBoard();
    int tile = 1;
    for(int i = 0; i < goalBoard.size(); i++)
    {
        for(int j = 0; j < goalBoard.at(i).size(); j++)
        {
            goalBoard.at(i).at(j) = tile;
            tile++;
        }
    }
    goalBoard.at(goalBoard.size()-1).at(goalBoard.at(0).size()-1) = 0;
    goal = new Node(goalBoard);
}//end of constructor

Game::Game(Node * start, Node * end)
{
    initial = start;
    goal = end;
}

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
       
            Node* temp = curr->Up();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    frontier.push(temp);        //add it to frontier
                    curr->addUpChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
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
                    t->increaseNodeSeen();      //document that we found a new board combination
                }
                else
                {
                    //isnt necessary but when plotted will show connection to repeat boards
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
                    t->increaseNodeSeen();      //document that we found a new board combination
                }
                else
                {
                    //isnt necessary but when plotted will show connection to repeat boards
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
                    //isnt necessary but when plotted will show connection to repeat boards
                    curr->addRightChild(t->returnNodeByHash(temp->createHash())); 
                }
            }//end of check for left op
            t->checkNewMaxQueueSize(frontier.size());
        }
    }//end of while

    cout<<"frontier is empty"<<endl;
    t->stopTime();
    t->printStats();
    return false;
}

bool Game::search_Euclidean()
{
    
    Tree* t = new Tree(initial, goal);//create tree to keep track of stats
    t->startTime();
    priority_queue<Node*, vector<Node*>, compareNodes> frontier;//initialize the frontier with custom comparison operator

    t->getRoot()->calculateEuclidHeuristic(goal->getBoard());
    frontier.push(t->getRoot());
    
    vector<Node*> explored;//keep track of boards you have already explored
    Node* curr;// curr is the current node to be expanded

    while(!frontier.empty())//if frontier is empty no solution was found, otherwise continue searching for solution
    {        
        curr = frontier.top();// make curr the next node in the frontier
        cout<<"Expanding Node with Hash: "<<curr->createHash()<<"\t Estimate: "<<curr->getEstimation()<<"\t g(n): "<<curr->getCost()<<"\th(n): "<<curr->getEstimation()-curr->getCost()<<endl;
        
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
            
            Node* temp = curr->Up();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addUpChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\t add up: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier
                    
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(UP);
                    }
                    curr->addUpChild(retrieveNode); 
                }
            } //end of check Up operator
            temp = curr->Down();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp) )//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addDownChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\tadd down: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier

                    // cout<<"\t\t"<<temp->getCost()<<endl;
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(DOWN);
                    }
                    curr->addDownChild(retrieveNode); 
                }
            } //end of check DOwn operator
            temp = curr->Left();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp) )//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addLeftChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\tadd left: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(LEFT);
                    }
                    curr->addLeftChild(retrieveNode); 
                }
            } //end of check Left operator
            temp = curr->Right();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp) )//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addRightChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\tadd right: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(RIGHT);
                    }
                    curr->addRightChild(retrieveNode); 
                }
            } //end of check RIght operator
            t->checkNewMaxQueueSize(frontier.size());
        }
            
    }

    cout<<"frontier is empty"<<endl;
    t->stopTime();
    t->printStats();
    return false;
}

bool Game::search_Misplace()
{
    
    Tree* t = new Tree(initial, goal);//create tree to keep track of stats
    t->startTime();
    priority_queue<Node*, vector<Node*>, compareNodes> frontier;//initialize the frontier with custom comparison operator

    t->getRoot()->calculateTileHeuristic(goal->getBoard());
    frontier.push(t->getRoot());
    
    vector<Node*> explored;//keep track of boards you have already explored
    Node* curr;// curr is the current node to be expanded

    while(!frontier.empty())//if frontier is empty no solution was found, otherwise continue searching for solution
    {        
        curr = frontier.top();// make curr the next node in the frontier
        cout<<"Expanding Node with Hash: "<<curr->createHash()<<"\t Estimate: "<<curr->getEstimation()<<"\t g(n): "<<curr->getCost()<<"\th(n): "<<curr->getEstimation()-curr->getCost()<<endl;
        
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
            
            Node* temp = curr->Up();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp))//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addUpChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\t add up: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier
                    
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<temp->createHash()<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(UP);
                    }
                    curr->addUpChild(retrieveNode); 
                }
            } //end of check Up operator
            temp = curr->Down();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp) )//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addDownChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\tadd down: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier

                    // cout<<"\t\t"<<temp->getCost()<<endl;
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<temp->createHash()<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(DOWN);
                    }
                    curr->addDownChild(retrieveNode); 
                }
            } //end of check DOwn operator
            temp = curr->Left();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp) )//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateTileHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addLeftChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\tadd left: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found"<<temp->createHash()<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(LEFT);
                    }
                    curr->addLeftChild(retrieveNode); 
                }
            } //end of check Left operator
            temp = curr->Right();
            if(temp != nullptr)//checks if move is valid/doesnt undo a move a
            {   
                if(!t->nodeAlreadySeen(temp) )//check if this board combination has not been seen
                {                           //if it hasnt:
                    temp->calculateEuclidHeuristic(t->getGoal()->getBoard()); //give the child an estimation
                    curr->addRightChild(temp);     //add it as the correct child of curr
                    t->addNodeToSeen(temp);     //add it to the hashmap to make it easy to find
                    // cout<<"\tadd right: "<<endl<<temp<<"Estimate: "<<temp->getEstimation()<<"\t Cost" <<temp->getCost()<<endl;     //print to make it easy to follow
                    t->increaseNodeSeen();      //document that we found a new board combination
                    frontier.push(temp);        //add it to frontier
                }
                else//make it a graph implementation, since it was already seen, we can make the child of current point to the already seen node
                {
                    //in the event we find a cheaper path to an already existing node
                    Node * retrieveNode = t->returnNodeByHash(temp->createHash());
                    if(retrieveNode->getCost() > temp->getCost())
                    {
                        cout<<"Should not run unless more optimal path was found\t "<<temp->createHash()<<endl;
                        retrieveNode->setCost(temp->getCost());
                        retrieveNode->getEstimation();//should already match
                        retrieveNode->setParent(curr);
                        retrieveNode->setLastMove(RIGHT);
                    }
                    curr->addRightChild(retrieveNode); 
                }
            } //end of check RIght operator
            t->checkNewMaxQueueSize(frontier.size());
        }
            
    }
    cout<<"frontier is empty"<<endl;
    t->stopTime();
    t->printStats();
    return false;
}

void Game::printSolutionFound(Node* n)
{
    if(n->getLastMove() == START)
    {
        cout<<n;
    }
    else
    {
        printSolutionFound(n->getParent());
        cout<<n;
    }
}