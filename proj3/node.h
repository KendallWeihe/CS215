#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {

  public:
    Node();
    Node(string d, int k);
    ~Node();
    int getKey();
    int getData();
    Node *getLeft();
    Node *getRight();
    void setKey(int k);
    void setData(string d);
    void setLeft(Node *l);
    void setRight(Node *r);

  private:
    int key;
    Node *left, *right;
    string data;

};

#endif
