#ifndef __NODE_H
#define __NODE_H

#include <vector>
#include <queue>
#include <iostream>


using namespace std;

enum validMoves {UP, DOWN, RIGHT, LEFT, START};
class Node
{
    private:
        Node* parent;
        vector<vector<char>> board;
        int zero_row = -1;
        int zero_col = -1;

        validMoves lastMove;

        Node* rightMove;
        Node* leftMove;
        Node* upMove;
        Node* downMove;
    public:
    //Constructors 
        Node(); //default
        ~Node();//destrutro
        Node(vector<vector<int>>, Node*, validMoves);//will be used to create a child and will save the move used
        Node(vector<vector<int>>); //will be used to make the root node
        Node(Node *);//copy constuctor that create soft copy of the node (only the table, no parent, child or move data)
        
        // bool operator==(const Node rhs) 
        // {
        //     cout<<"test test"<<endl;
        //     if(board == rhs.board)
        //         return true;
        //     return false;
        // }

        //checks if operators are valid given te board
        bool tryUp();
        bool tryDown();
        bool tryRight();
        bool tryLeft();

    //checks if a board is alreadyin a vector of boards
        bool in(vector<Node*>);
    //checks if a board is alreadyin a queue of boards 
        bool in(queue<Node*>);
        void printNode();

    //creates the child using that operation
        Node* Up();
        Node* Down();
        Node* Right();
        Node* Left();
    //returns parent of the current node
        Node* getParent() {return this->parent;}
    // create unique id for each board configuration
        string createHash();
    //returns the board stored in the root
        vector<vector<int>> getBoard() {return board;};

    //prints the move last used
        void printLastMove();
    //returns move used to reach that board, stops at root
        validMoves getLastMove();

    //override << to make it easier to jsut print the boards off node
        friend ostream& operator<<(ostream& out, const Node* n)
        {
            // cout<<"test teste "<<endl;
        if(n->lastMove == UP)
            out << "Moved UP" << endl;
        else if(n->lastMove == DOWN)
            out << "Moved DOWN" << endl;
        else if(n->lastMove == LEFT)
            out << "Moved LEFT" << endl;
        else if(n->lastMove == RIGHT)
            out << "Moved RIGHT" << endl;
        else
            out << "Starting State" <<endl;
        for(int i = 0; i < n->board.size(); i++)
        {
            for(int j = 0; j < n->board.at(i).size(); j++)
            {
                out<<n->board.at(i).at(j)<<"\t";
            }//end of inner loop
            out<<endl;
        }//end of outer loop
        out<<endl;
        return out;
    }//end pf << overload

        

};//end of node class

        
#endif