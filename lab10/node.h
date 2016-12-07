
#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

using namespace std;

class node {
  public:
    node();
    node(int, string);
    ~node();
    void setKey(int);
    void setData(string);
    void setLeft(node*);
    void setRight(node*);
    int getKey();
    string getData();
    node *getLeft();
    node *getRight();
    void print();
  private:
    int key;
    string data;
    node *left;
    node *right;
};

#endif
