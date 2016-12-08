#include <iostream>
#include <string>
#include "BST.h"
#include "node.h"

using namespace std;

//-------------------------------------------------------------------------------------
//                                BST() -- default constructor
//-------------------------------------------------------------------------------------
BST::BST(){
  root = NULL;
}

//-------------------------------------------------------------------------------------
//                                ~BST() -- destructor
//-------------------------------------------------------------------------------------
BST::~BST(){
  if (root == NULL)
    delete root;
}

//-------------------------------------------------------------------------------------
//                                insert()
//-------------------------------------------------------------------------------------
void BST::insert(int k, string d){
  insert(root, k, d);
}

//-------------------------------------------------------------------------------------
//                                search()
//-------------------------------------------------------------------------------------
string BST::search(int k){
  return search(root, k);
}

//-------------------------------------------------------------------------------------
//                                numNodes()
//-------------------------------------------------------------------------------------
int BST::numNodes(){
  int n_nodes = 0;
  numNodes(root, n_nodes);
  return n_nodes;
}

//-------------------------------------------------------------------------------------
//                                depth()
//-------------------------------------------------------------------------------------
int BST::depth(){
  int max_depth = 0;
  depth(root, max_depth, 0);
  if (max_depth == 0){
    return -1;
  }
  else {
    return max_depth;
  }
}

//-------------------------------------------------------------------------------------
//                                minKey()
//-------------------------------------------------------------------------------------
int BST::minKey(){
  return minKey(root);
}

//-------------------------------------------------------------------------------------
//                                insert()
//-------------------------------------------------------------------------------------
void BST::insert(Node *n, int k, string d){

  if (n == NULL){
    root = new Node(k, d);
  }
  else {
    if (k <= n->getKey()){
      if (n->getLeft() == NULL){
        Node *new_node = new Node(k, d);
        n->setLeft(new_node);
      }
      else {
        insert(n->getLeft(), k, d);
      }
    }
    else {
      if (n->getRight() == NULL){
        Node *new_node = new Node(k, d);
        n->setRight(new_node);
      }
      else {
        insert(n->getRight(), k, d);
      }
    }
  }

}

//-------------------------------------------------------------------------------------
//                                search()
//-------------------------------------------------------------------------------------
string BST::search(Node *n, int k){
  if (n == NULL){
    return "";
  }
  else {
    if (n->getKey() == k){
      return n->getData();
    }
    else if (n->getKey() <= k){
      return search(n->getRight(), k);
    }
    else {
      return search(n->getLeft(), k);
    }
  }
}

//-------------------------------------------------------------------------------------
//                                numNodes()
//-------------------------------------------------------------------------------------
void BST::numNodes(Node *n, int &n_nodes){
  if (n == NULL){
    return;
  }
  else {
    n_nodes += 1;
    numNodes(n->getLeft(), n_nodes);
    numNodes(n->getRight(), n_nodes);
  }
}

//-------------------------------------------------------------------------------------
//                                depth()
//-------------------------------------------------------------------------------------
void BST::depth(Node *n, int &max_depth, int level){
  if (n == NULL){
    return;
  }
  else {
    depth(n->getLeft(), max_depth, level+1);
    if (level > max_depth){
      max_depth = level;
    }
    depth(n->getRight(), max_depth, level+1);
    if (level > max_depth){
      max_depth = level;
    }
  }
}

//-------------------------------------------------------------------------------------
//                                minKey()
//-------------------------------------------------------------------------------------
int BST::minKey(Node *n){
  if (n == NULL){
    return -1;
  }

  if (n->getLeft() == NULL){
    return n->getKey();
  }
  else {
    return minKey(n->getLeft());
  }
}
