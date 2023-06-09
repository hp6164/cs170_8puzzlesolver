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
        double costAndHeuristic = -1;

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
        bool in(priority_queue<Node*>);
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
        void setParent(Node * n) {this->parent = n;}
    // create unique id for each board configuration
        string createHash();
    //returns the board stored in the root
        vector<vector<int>> getBoard() {return board;};

    //prints the move last used
        void printLastMove();
    //returns move used to reach that board, stops at root
        validMoves getLastMove();
        void setLastMove(validMoves);

    // sets cost of node
        void setCost(int newCost) { cost = newCost; }
    // get cost of node;
        int getCost() {return cost;}

    //checks against a small list of state deemed impossible
        bool checkImpossible(const vector<string>&);

    // return and set function: h(x) + g(x)
    // void setEstimation(double d) {costAndHeuristic = d + cost; }
    // get heuristics
    double getEstimation() { return costAndHeuristic; }

    void calculateEuclidHeuristic(vector<vector<int>>);
    void calculateTileHeuristic(vector<vector<int>>);

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

    //override the < operator so that it marks nodes with the lease cost higher up in the priority quue
    // friend bool operator<(const Node* lhs, const Node* rhs)
    // {
    //     return (lhs->costAndHeuristic > rhs.->costAndHeuristic);
    // }
        

};//end of node class

    
    

        
#endif