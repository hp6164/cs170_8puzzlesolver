#ifndef __NODE_H
#define __NODE_H

#include <vector>

#include <iostream>


using namespace std;

class Node
{
    private:
        Node* parent;
        ~Node();
        vector<vector<int>> board;
        int zero_row = -1;
        int zero_col = -1;

    public:
        Node();
        Node(vector<vector<int>>, Node*);
        //operators
        bool tryUp();
        bool tryDown();
        bool tryRight();
        bool tryLeft();
        
        void printNode();
};//end of node class

#endif