#include <iostream>
#include <string>
#include "node.h"

using namespace std;

Node::Node(){
  key = 0;
  data = "";
}

Node::Node(string d, int k){
  key = k;
  data = d;
}

Node::~Node(){
  delete left;
  delete right;
}

int Node::getKey(){
  return key;
}

int Node::getData(){
  return data;
}

Node *Node::getLeft(){
  return left;
}

Node *Node::getRight(){
  return right;
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
