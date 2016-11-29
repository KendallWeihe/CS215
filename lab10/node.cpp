#include <iostream>
#include "node.h"

using namespace std;

node::node(){
  key = 0;
  data = "";
  left = NULL;
  right = NULL;
  cout << "node: default construction" << endl;
}

node::node(int k, string d){
  key = k;
  data = d;
  left = NULL;
  right = NULL;
  cout << "construction: key=" << k << " data=" << d << endl;
}

node::~node(){
  delete left;
  delete right;
}

void node::setKey(int k){
  key = k;
}

void node::setData(string d){
  data = d;
}

void node::setLeft(node *n){
  left = n;
}

void node::setRight(node *n){
  right = n;
}

void node::print(){

}

node node::getLeft(){
  return left;
}

node node::getRight(){
  return right;
}

int node::getKey(){
  return key;
}

string node::getData(){
  return data;
}
