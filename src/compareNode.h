// So priorities queues sort by a specific value, for nodes that is their addresss, meaning it always always picks the last option added
// to fix this we need to add a function comparision that works directly with the nodes
// SOltion to this was found on: https://stackoverflow.com/questions/40794566/operator-overloading-on-priority-queue-of-object-pointers

#include "node.h"
#include <iostream>
using namespace std;
class compareNodes
{
public:
    bool operator() (Node* lhs, Node* rhs)
    {
        // cout<<"test"<<endl;
        return lhs->getEstimation() > rhs->getEstimation();
    }
};