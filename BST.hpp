#include <iostream>
#include "TreeNode.hpp"
#include "Student.hpp"
using namespace std;

template<typename t>
class BST{
public:
  BST(){
    root = NULL;
  }
  virtual ~BST(){
  }

//---------------------- BST FUNCTIONS -------------------------------

  TreeNode<t>* getRoot(){
    return root;
  }

  void insert(t value){
    TreeNode<t> *node = new TreeNode<t>(value);
    //cout << "the node is holding" << node->key << endl;

    if(isEmpty()){
      //empty Tree
      root = node;
    }

    //working up until line 30
    else{
      //not an empty tree
      TreeNode<t> *curr = root; //start at the root
      TreeNode<t> *parent;

      while(curr!=NULL){ //could do while(curr!=NULL)
        parent = curr;
        if(value< curr->key){
          //cout << "kevin is going to the left" << endl;
          //go left
          curr = curr->left;
          if(curr == NULL){
            parent->left = node;
            //cout << "kevin is left " << endl;
            break;
          }
        }
        else{
          //cout << "kevin is going to the right" << endl;
          //go right
          curr = curr->right;
          if(curr == NULL){
            parent->right = node;
            //cout << "the value of the node to the right is " << parent->right->key.getName() << endl;
            //cout << "kevin is right " << endl;
            break;
          }
        }
      }
    }
  }

  //which in this example is also our key

  //dont fuck with this, it works
  TreeNode<t>* search(t value){
    if(isEmpty()){
      return NULL;
    }
    else{
      //its not an empty Tree
      TreeNode<t> *current = root;

      while(current->key != value){
        if(value < current->key){
          current = current->left;
        }
        else{
          current = current->right;
        }

        if(current == NULL){
          //didnt find the value 
			//cout << "No person with ID " << value.getid() << endl;
          return NULL;
        }
      }

	  return current;
    }
  }

  bool exists(t value) {
	  t searchResult = search(value)->key;
	  if (searchResult != NULL) {
		  return true;
	  }

	  return false;
  }
  //which in this example is also our key
  bool deleteNode(t k){
    if(isEmpty()){
      return false;
    }

    TreeNode<t> *parent = root;
    TreeNode<t> *current = root;
    bool isLeft = true;
	bool exitLoop = false;
    while(!exitLoop){
      parent = current;
      if(k < current->key){
        isLeft = true;
        current = current->left;
      }
      else{
        isLeft = false;
		if (current->key != k) {
			current = current->right;
		}
      }

      if(current == NULL){
        return false;
      }

      //if we make it here, we found the value, let's proceed to delete
      if(current->left == NULL && current->right == NULL){
        //then we have a leaf treenode
        if(current == root){
          root = NULL;
		  exitLoop = true;
        } else if(isLeft){
          parent->left = NULL;
		  exitLoop = true;
        }else{
          parent->right = NULL;
		  exitLoop = true;
        }
      }
      else if(current->right == NULL){
        //node we are deleting has one child, but it is not a right child
		  parent->right = current->left;
		  exitLoop = true;
      }

      //no left child, so must have a right child
      //this else if determines position of children of node to be deleted
      else if(current->left == NULL){
        //these branching statements identify position of node to be deleteNode
        if(current == root){
          root = current->right;
		  exitLoop = true;
        }
        else if(isLeft){
          parent->left = current->right;
		  exitLoop = true;
        }
        else{
          parent->right = current->right;
		  exitLoop = true;
        }
      }
      else{
        //the node to be deleted has two children
        //at this point we bang our head on the keyboard and cry
        //TreeNode<t> *successor = getSuccessor(current);

        ///*if(current == root){
        //  root = successor;
        //}
        //else if(isleft){
        //  parent->left = successor;
        //}
        //else{*/
		
		// get the min of our right subtree
		  if (isLeft) {
			  TreeNode<t> *maxReplacement = getMax(current->left->key);
			  
			  maxReplacement->right = current->right;
			  parent->left = maxReplacement;

			  if (maxReplacement->key != current->left->key) {
				  maxReplacement->left = current->left;
				  current->left->right = NULL;
			  }
			  else {
				  maxReplacement->left = NULL;
			  }


			  exitLoop = true;

			  //maxReplacement->
		  }
		  else {
			  TreeNode<t> *minReplacement = getMin(current->right->key);
			 // cout << " our replacement for kevin is " << minReplacement->key.getName() << endl;

			  // set the parent, right and left of the new replacement
			  //minReplacement->parent = current->parent;
			  minReplacement->left = current->left;

			  //if the minReplacement isnt the current's left
			  if (minReplacement->key != current->right->key) {
				  minReplacement->right = current->right;
				  current->right->left = NULL;
			  }
			  //if our minReplacement is the current's left (only three levels of trees)
			  else {
				  minReplacement->right = NULL;
			  }
			  // replace our current node with the min
			  if (current != root) {
				  parent->right = minReplacement;
			  }
			  else {
				  //we are replacing the root
				  root = minReplacement;
			  }
			  
			  exitLoop = true;

			  //parent->right = successor;
			//}

			//connect/link successor to current's (d) left child
		  }
      }
    }
  }
  /*bool deleteNode(t k) {
	  if (isEmpty()) {
		  return false;
	  }

	  t searchResult = search(k);

	  if (searchResult == NULL) {
		  return false;
	  }

	  TreeNode<t> *parent = root;
	  TreeNode<t> *current = root;
	  bool isLeft = true;

	  if (searchResult == root->key) {
		  root = current->left;

	  }
	  

	  

	  
  }*/


  bool isEmpty(){
    return(root == NULL);
  }


  TreeNode<t>* getMin(t stu){
	TreeNode<t> *curr = search(stu);

    if(root == NULL){
      //empty Tree
      return NULL;
    }
    while(curr->left != NULL){
      curr = curr->left;
    }
    return curr;
  }

  TreeNode<t>* getMax(t stu){
    TreeNode<t> *curr = search(stu);

    if(root == NULL){
      //empty Tree
      return NULL;
    }
    while(curr->right != NULL){
      curr = curr->right;
    }
    return curr;
  }

  TreeNode<t>* getSuccessor(TreeNode<t> *d){
    //the parameter d represents the node to be deleted

    TreeNode<t> *current = d->right;
    TreeNode<t> *sp = d;
    TreeNode<t> *successor =d;

    while(current != NULL){
      sp = successor;
      successor = current;
      current = current->left;
    }

    if(successor != d->right){
      sp->left = successor->right;
      successor->right = d->right;
    }

    return successor;
  }

  /*void printTree(TreeNode<t> *node){
    if(node == NULL){
      return;
    }

    printTree(node->left);
    cout << node->key << endl;
    printTree(node->right);
  };*/

private:
  TreeNode<t> *root;
};


  //}; //end of class
