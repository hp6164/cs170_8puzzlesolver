#include "node.h"
#include <math.h>

using namespace std;

Node::Node(vector<vector<int>> initTable, Node* p, validMoves last)//use this to create a child node
{
    try
    {
        parent = p;
        upMove = nullptr;
        downMove = nullptr;
        rightMove = nullptr;
        downMove = nullptr;
        cost = p->getCost()+1;

        lastMove = last;
        costAndHeuristic = -1;

        board = initTable;
        for(int i = 0; i < initTable.size(); i++)
        {
            for(int j = 0; j < initTable.at(i).size(); j++)
            {
                if(initTable.at(i).at(j) == 0)
                {
                    zero_col = j;
                    zero_row = i;
                    break;
                }//end of if that finds 0 positon
            }//end of inner loop
        }//end of outer loop
        if(zero_col < 0 || zero_row < 0)
        {
            throw invalid_argument("Not a valid input");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}//end of node constuctor

Node::Node(vector<vector<int>> initTable)// use this to make root node
{
    try
    {
        parent = nullptr;
        upMove = nullptr;
        downMove = nullptr;
        rightMove = nullptr;
        downMove = nullptr;

        cost = 0;

        lastMove = START;
        costAndHeuristic= -1;

        board = initTable;
        for(int i = 0; i < initTable.size(); i++)
        {
            for(int j = 0; j < initTable.at(i).size(); j++)
            {
                if(initTable.at(i).at(j) == 0)
                {
                    zero_col = j;
                    zero_row = i;
                    break;
                }//end of if that finds 0 positon
            }//end of inner loop
        }//end of outer loop
        if(zero_col < 0 || zero_row < 0)
        {
            throw invalid_argument("Not a valid input");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}//end of node constuctor

Node::Node()//default input
{
    parent = nullptr;
    upMove = nullptr;
    downMove = nullptr;
    rightMove = nullptr;
    downMove = nullptr;

    lastMove = START;

    board = { {1, 0, 3}, 
              {4, 2, 6},
              {7, 5, 8} };
    zero_col = 1;
    zero_row = 0;
    cost = 0;
    costAndHeuristic = -1;
}

Node::Node(Node* temp)//Will make a copy of the board and nothing else 
{
    parent = nullptr;
    upMove = nullptr;
    downMove = nullptr;
    rightMove = nullptr;
    downMove = nullptr;
    board = temp->board;
    zero_col = temp->zero_col;
    zero_row = temp->zero_row;
    cost = -1;
    costAndHeuristic = -1;
}//end of copy Consturctor

Node::~Node()
{
    delete parent;
    delete upMove;
    delete downMove;
    delete rightMove;
    delete leftMove;
    
}


bool Node::tryUp()
{
    try
    {
        if(zero_row != 0)
        {
            return true;
        }
        else
        {
            throw invalid_argument("Error in tryUp");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }//end of catch
}//end of tryUp

bool Node::tryDown()
{
    try
    {
        if(zero_row != board.size()-1)
        {
            return true;
        }
        else
        {
            throw invalid_argument("Error in tryDown");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }//end of catch
}//end of tryDown


bool Node::tryLeft()
{
    try
    {
        if(zero_col != 0)
        {
            return true;
        }
        else
        {
            throw invalid_argument("Error in tryLeft");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }//end of catch
}//end of tryLeft

bool Node::tryRight()
{
    try
    {
        if(zero_col != board.size()-1)
        {
            return true;
        }
        else
        {
            throw invalid_argument("Error in tryRight");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }//end of catch
}//end of tryRight

void Node::printNode()
{
    for(int i = 0; i < board.size(); i++)
        {
            for(int j = 0; j < board.at(i).size(); j++)
            {
                cout<<board.at(i).at(j)<<"\t";
            }//end of inner loop
            cout<<endl;
        }//end of outer loop
}//end of Print Node


Node* Node::Up()
{
    try
    {
        if(zero_row != 0  && lastMove != DOWN)
        {
            Node* temp = new Node(this);
            temp->board.at(zero_row).at(zero_col) = temp->board.at(zero_row-1).at(zero_col);
            temp->board.at(zero_row-1).at(zero_col) = 0; 

            temp->zero_row--;

            temp->parent = this;
            temp->cost = temp->parent->getCost()+1;
            temp->lastMove = UP;
            
            return temp;
        }
        else
        {
            throw invalid_argument("Error in UP");
        }
    }//end of try
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of up

Node* Node::Down()
{
    try
    {
        if(zero_row != board.size()-1 && lastMove != UP)
        {
            Node* temp = new Node(this);
            temp->board.at(zero_row).at(zero_col) = temp->board.at(zero_row+1).at(zero_col);
            temp->board.at(zero_row+1).at(zero_col) = 0; 

            temp->zero_row++;

            temp->parent = this;
            temp->cost = temp->parent->getCost()+1;
            temp->lastMove = DOWN;
            return temp;
        }
        else
        {
            throw invalid_argument("Error in DOWN");
        }
    }//end of try
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of down


Node* Node::Left()
{
    try
    {
        if(zero_col != 0 && lastMove != RIGHT)
        {
            Node* temp = new Node(this);
            temp->board.at(zero_row).at(zero_col) = temp->board.at(zero_row).at(zero_col-1);
            temp->board.at(zero_row).at(zero_col-1) = 0; 

            temp->zero_col--;

            temp->parent = this;
            temp->cost = temp->parent->getCost()+1;
            temp->lastMove = LEFT;


            return temp;
        }
        else
        {
            throw invalid_argument("Error in LEFT");
        }
    }//end of try
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of left

Node* Node::Right()
{
    try
    {
        if(zero_col !=  board.at(0).size()-1 && lastMove != LEFT)
        {
            Node* temp = new Node(this);
            temp->board.at(zero_row).at(zero_col) = temp->board.at(zero_row).at(zero_col+1);
            temp->board.at(zero_row).at(zero_col+1) = 0; 

            temp->zero_col++;

            temp->parent = this;
            temp->cost = temp->parent->getCost()+1;
            temp->lastMove = RIGHT;
            return temp;
        }
        else
        {
            throw invalid_argument("Error in RIGHT");
        }
    }//end of try
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of Right

void Node::calculateEuclidHeuristic(vector<vector<int>> goal)
{
    //could defenitely be made more optimal/efficient
    double heuristic = 0;
    for(int i = 0; i < board.size(); i++)//for each value
    {
        for( int j = 0; j < board.at(i).size(); j++)
        {
            if(board.at(i).at(j) != goal.at(i).at(j) && board.at(i).at(j) != 0)
            {
                for(int k = 0; k < goal.size(); k++)//find where it should be
                {
                    for( int l = 0; l < goal.at(i).size(); l++)
                    {
                        if(goal.at(k).at(l) == board.at(i).at(j))  
                        {
                            // cout<<"checking row "<<i<<", "<<j<<endl;
                            heuristic += ( sqrt(pow(i-k, 2)+pow(j-l,2)) );
                        }
                    }
                }
            }
        }
    }
    costAndHeuristic = (cost + heuristic);
}

void Node::calculateTileHeuristic(vector<vector<int>> b)
{
    //could defenitely be made more optimal/efficient
    double heuristic = 0;
    for(int i = 0; i < board.size(); i++)//for each value
    {
        for( int j = 0; j < board.at(i).size(); j++)
        {
            if(board.at(i).at(j) != b.at(i).at(j) && board.at(i).at(j) != 0)
            {
                for(int k = 0; k < b.size(); k++)//find where it should be
                {
                    for( int l = 0; l < b.at(i).size(); l++)
                    {
                        if(b.at(k).at(l) == board.at(i).at(j))  
                        {
                            // cout<<"checking row "<<i<<", "<<j<<endl;
                            heuristic += abs(k-i);
                            heuristic += abs(l-j);
                        }
                    }
                }
            }
        }
    }
    costAndHeuristic = (cost + heuristic);
}

bool Node::in(vector<Node*> input)
{
    for(Node* n : input)
    {
        if( this == n)
        {
            return true;
            break;
        }
    }
    return false;
}

bool Node::in(priority_queue<Node*> input)
{
    while(!input.empty())
    {
        if( this == input.top())
        {
            return true;
            break;
        }
        input.pop();
    }
    return false;
}

bool Node::checkImpossible(const vector<string> &impossibleStates)
{
    // string impossibleHashes[10] = {"1.2.3.4.6.5.7.8.0.", 
    //                                "1.2.3.4.0.6.7.8.5.",
    //                                 "1.2.3.4.5.6.8.7.0.", ""}; //list of hashes that are impossible, these have low heursitics so ideally the A* algorithms will gravitate torwards them
    string hash = this->createHash();
    for(string s : impossibleStates)
    {
        if(hash.compare(s) == 0)
            return true;
    }
    return false;
}

validMoves Node::getLastMove()
{
    return this->lastMove;
}
void Node::setLastMove(validMoves v)
{
    lastMove = v;
}

string Node::createHash()
{
    string hash = "";
    for (vector<int> v : board)
    {
        for(int i : v)
        {
            string temp = to_string(i);
            for(char c : temp)
                hash.push_back(c);
            hash.push_back('.');
        }
    }
    return hash;
}

void Node::printLastMove()
{
    if(lastMove == UP)
        cout << "Moved UP" << endl;
    else if(lastMove == DOWN)
        cout << "Moved DOWN" << endl;
    else if(lastMove == LEFT)
        cout << "Moved LEFT" << endl;
    else if(lastMove == RIGHT)
        cout << "Moved RIGHT" << endl;
    else
        cout << "Starting State" <<endl;
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board.at(i).size(); j++)
        {
            cout<<board.at(i).at(j)<<"\t";
        }//end of inner loop
        cout<<endl;
    }//end of outer loop
    cout<<endl;
}//end of print last move


void Node::printAllNodeData()
{
    cout<<"Node Data"<<endl;
    cout<<"Board: "<<endl;
    cout<<this<<endl;
    cout<<"Zero at: "<<zero_row<<", "<<zero_col<<endl;
    cout<<"Cost: "<<cost<<endl;
    cout<<"Children: "<<endl;
    if(rightMove != nullptr)
        cout<<"\t Has Right Child"<<endl;
    if(leftMove != nullptr)
        cout<<"\t Has Left Child"<<endl;
    if(upMove != nullptr)
        cout<<"\t Has Up Child"<<endl;
    if(downMove != nullptr)
        cout<<"\t Has Down Child"<<endl;
    cout<<"Parent"<<endl;
    if(getParent() == nullptr)
        cout<<"None"<<endl;
    else
        cout<<getParent();
}