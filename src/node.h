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
        vector<vector<int>> board;
        int zero_row = -1;
        int zero_col = -1;

        validMoves lastMove;

        Node* rightMove;
        Node* leftMove;
        Node* upMove;
        Node* downMove;
    public:
        Node();
        ~Node();
        Node(vector<vector<int>>, Node*, validMoves);
        Node(vector<vector<int>>);
        Node(Node *);//copy constuctor
        
        // bool operator==(const Node rhs) 
        // {
        //     cout<<"test test"<<endl;
        //     if(board == rhs.board)
        //         return true;
        //     return false;
        // }

        //operators
        bool tryUp();
        bool tryDown();
        bool tryRight();
        bool tryLeft();

        bool in(vector<Node*>);
        bool in(queue<Node*>);
        void printNode();

        Node* Up();
        Node* Down();
        Node* Right();
        Node* Left();

        Node* getParent() {return this->parent;}

        validMoves getLastMove();
        vector<vector<int>> getBoard() {return board;};

        
        void printLastMove();
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