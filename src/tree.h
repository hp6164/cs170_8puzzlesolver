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
        int maxQueueSize;
        clock_t begin, end;

        // can optimize with hashmap of each node in tree to avoid duplicates
    public:
        Tree(Node * r, Node* g) 
        {
            root = new Node(r->getBoard()); 
            goal = new Node(g->getBoard());
            nodeSeen = 1; // just the root
            nodesExpanded = 0;//none expanded yet
            maxQueueSize = 1;
            r->setCost(0);
            

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

        Node* getRoot() {return root;}//returns root
        Node* getGoal() {return goal;}//returns goal

        void checkNewMaxQueueSize(int i) {  if(i > maxQueueSize) {maxQueueSize = i;}};

        void startTime() {begin = clock();}
        void stopTime() {end = clock();}

        void updateGoal(Node * n) {goal = n;}//update path to goal once found

        void increaseNodeExpanded() {nodesExpanded++;}//keep metrics of nodes expanded
        void increaseNodeSeen() {nodeSeen++;} //keep metrics of node seens

        bool nodeAlreadySeen(Node* n)//returns true if node has already been seen and added to hashmap
        {
            if(nodesFound.find(n->createHash()) == nodesFound.end() )
            {
                return false;
            }
            return true;
        }
        Node* returnNodeByHash(string hash) {return nodesFound.at(hash);}
        void addNodeToSeen(Node* n) { nodesFound[n->createHash()] = n; }//adds board to hashmap

        void printStats() {
            cout<<"Solution Cost: "<<goal->getCost()<<endl;
            cout<<"Nodes Seen: "<<nodeSeen<<endl;
            cout<<"Nodes Expanded: "<<nodesExpanded<<endl;
            cout<<"Max Queue Size: "<<maxQueueSize<<endl;
            int elapsed = static_cast<int>(end - begin);
            cout<<"Time: "<< elapsed <<" ticks"<<endl;
        }

};

#endif