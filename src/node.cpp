#include "node.h"

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

        lastMove = last;

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
}//end of copy Consturctor

Node::~Node()
{
    delete parent;
    delete upMove;
    delete downMove;
    delete rightMove;
    delete downMove;
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
            upMove = new Node(this);
            upMove->board.at(zero_row).at(zero_col) = upMove->board.at(zero_row-1).at(zero_col);
            upMove->board.at(zero_row-1).at(zero_col) = 0; 

            upMove->zero_row--;

            upMove->parent = this;
            upMove->lastMove = UP;
            
            return upMove;
        }
        else
        {
            throw invalid_argument("Error in UP");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of up

Node* Node::Down()
{
    try
    {
        if(zero_row != board.size()-1 && lastMove != UP)
        {
            downMove = new Node(this);
            downMove->board.at(zero_row).at(zero_col) = downMove->board.at(zero_row+1).at(zero_col);
            downMove->board.at(zero_row+1).at(zero_col) = 0; 

            downMove->zero_row++;

            downMove->parent = this;
            downMove->lastMove = DOWN;
            return downMove;
        }
        else
        {
            throw invalid_argument("Error in DOWN");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of down


Node* Node::Left()
{
    try
    {
        if(zero_col != 0 && lastMove != RIGHT)
        {
            leftMove = new Node(this);
            leftMove->board.at(zero_row).at(zero_col) = leftMove->board.at(zero_row).at(zero_col-1);
            leftMove->board.at(zero_row).at(zero_col-1) = 0; 

            leftMove->zero_col--;

            leftMove->parent = this;
            leftMove->lastMove = LEFT;


            return leftMove;
        }
        else
        {
            throw invalid_argument("Error in LEFT");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of left

Node* Node::Right()
{
    try
    {
        if(zero_col !=  board.at(0).size()-1 && lastMove != LEFT)
        {
            rightMove = new Node(this);
            rightMove->board.at(zero_row).at(zero_col) = rightMove->board.at(zero_row).at(zero_col+1);
            rightMove->board.at(zero_row).at(zero_col+1) = 0; 

            rightMove->zero_col++;

            rightMove->parent = this;
            rightMove->lastMove = RIGHT;
            return rightMove;
        }
        else
        {
            throw invalid_argument("Error in RIGHT");
        }
    }//end of try
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }//end of catch
}//end of Right

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

bool Node::in(queue<Node*> input)
{
    while(!input.empty())
    {
        if( this == input.front())
        {
            return true;
            break;
        }
        input.pop();
    }
    return false;
}

validMoves Node::getLastMove()
{
    return this->lastMove;
}

string Node::createHash()
{
    string hash = "";
    for (vector<int> v : board)
    {
        for(int i : v)
        {
            hash.push_back(i);
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