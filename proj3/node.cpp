#include <iostream>
#include <string>
#include "node.h"

using namespace std;

Node::Node(){
  key = 0;
  data = "";
  left = NULL;
  right = NULL;
}

Node::Node(int k, string d){
  key = k;
  data = d;
  left = NULL;
  right = NULL;
}

Node::~Node(){
  if (left != NULL)
    delete left;
  if (right != NULL)
    delete right;
}

int Node::getKey(){
  return key;
}

string Node::getData(){
  return data;
}

Node *Node::getLeft(){
  if (left == NULL){
    return nullptr;
  }
  else {
    return left;
  }
}

Node *Node::getRight(){
  if (right == NULL){
    return nullptr;
  }
  else {
    return right;
  }
}

void Node::setKey(int k){
  key = k;
}

void Node::setData(string d){
  data = d;
}

void Node::setLeft(Node *l){
  left = l;
}

void Node::setRight(Node *r){
  right = r;
}
