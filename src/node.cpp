#include "node.h"

using namespace std;

Node::Node(vector<vector<int>> initTable, Node* p)
{
    try
    {
        parent = p;
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

Node::Node(vector<vector<int>> initTable)
{
    try
    {
        parent = nullptr;
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

Node::Node()
{
    parent = nullptr;
    board = { {1, 0, 3}, 
              {4, 2, 6},
              {7, 5, 8} };
    zero_col = 1;
    zero_row = 0;
}

Node::Node(Node &temp)
{
    parent = temp.parent;
    board = temp.board;
    zero_col = temp.zero_col;
    zero_row = temp.zero_row;
}//end of copy Consturctor

Node::~Node()
{
    delete parent;
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

