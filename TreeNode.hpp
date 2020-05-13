#ifndef _TreeNode_HPP_
#define _TreeNode_HPP_

#include <iostream>
using namespace std;

template<typename t>
class TreeNode{
public:
  //tree node implementation
  TreeNode(){
    key = NULL;
    //key = NULL;
    left = nullptr;
    right = nullptr;
  }

  TreeNode(t v){
    //key = k;
    key = v;
    left = nullptr;
    right = nullptr;
  }

  //if we were storing key values this is what our ctor would look like
  //TreeNode(int k, <type> v);
  virtual ~TreeNode(){
    //delete code
  }
  //virtual ~TreeNode(); - when working with template class

//key is id, value is student
  //int key;
  t key;
  TreeNode *left;
  TreeNode *right;
};

#endif
