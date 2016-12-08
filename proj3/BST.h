#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include "node.h"

using namespace std;

class BST {
  public:
    BST();
    ~BST();
    void insert(int k, string d);
    void printKeyTree();
    void printSorted();
    string search(int k);
    int numNodes();
    int depth();
    int minKey();

  private:
    void insert(Node *n, int k, string d);
    void printKT(Node *r, int level);
    void printSorted(Node *r);
    string search(Node *n, int k);
    void numNodes(Node *n, int &n_nodes);
    void depth(Node *n, int &max_depth, int level);
    int minKey(Node *n);

    Node *root;

};

#endif
