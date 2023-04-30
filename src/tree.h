#ifndef __TREE_H
#define __TREE_H

#include <iostream>
#include "node.h"
// #include "queue"
#include <unordered_map>

class Tree
{
    private:
        Node* root;
        Node* goal;
        unordered_map<string, Node*> nodesFound;
        int nodesExpanded;
        int nodeSeen;

        // can optimize with hashmap of each node in tree to avoid duplicates
    public:
        Tree(Node * r, Node* g) 
        {
            root = new Node(r); 
            goal = new Node(g);
            nodeSeen = 1; // just the root
            nodesExpanded = 0;//none expanded yet

        }
        ~Tree()
        {
            delete root;
            delete goal;
            
            for(unordered_map<string, Node*>::iterator itr = nodesFound.begin(); itr != nodesFound.end(); itr++)
            {
                delete (itr->second);
            }
            nodesFound.clear();
        
        }

        Node* getRoot() {return root;}
        Node* getGoal() {return goal;}

        void increaseNodeExpanded() {nodesExpanded++;}
        void increaseNodeSeen() {nodeSeen++;}

        bool nodeAlreadySeen(Node* n)
        {
            if(nodesFound.find(n->createHash()) == nodesFound.end() )
            {
                return false;
            }
            return true;
        }
        void addNodeToSeen(Node* n) { nodesFound[n->createHash()] = n; }


};

#endif