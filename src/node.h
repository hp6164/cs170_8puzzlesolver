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
        int cost = -1;
        double euclid_heuristic = -1;
        int tile_heuristic = -1;

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

    //returns a new node that would be create by taking that move, nullptr if ( its impossible or returns to parent )
        Node* Up();
        Node* Down();
        Node* Right();
        Node* Left();



//adds the 
        void addUpChild(Node *n) {upMove = n; }
        void addDownChild(Node *n) {downMove = n; }
        void addRightChild(Node *n) {rightMove = n; }
        void addLeftChild(Node *n ) {leftMove = n; }

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

    // sets cost of node
        void setCost(int newCost) { cost = newCost; }
    // get cost of node;
        int getCost() {return cost;}


    // set heuristics
    void setEuclidHeuristic(double d) {euclid_heuristic = d;}
    void setTileHeuristic(double d) {tile_heuristic = d;}
    // get heuristics
    double getEuclidHeuristic() { return euclid_heuristic; }
    double getTileHeurisitic() { return tile_heuristic; }


    //prints all nodes data
        void printAllNodeData();

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