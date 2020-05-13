#ifndef _GENSTACK_H_
#define _GENSTACK_H_

#include <iostream>
using namespace std;

template<typename object>
class GenStack{
public:
  GenStack(){
    myObjects = new object[128];
    mSize = 0;
    top = -1;
  } //default ctor

  GenStack(int maxSize){
    myObjects = new object[maxSize];
    mSize = maxSize;
    top = -1;
  } //overloaded ctor

  ~GenStack(){
    //delete the array
    //delete myObjects;
  } //dtor

  //core functions
  void push(object data){
    if(isFull()){
      mSize++;
    }
      myObjects[++top] = data;
  } //insert

  object pop(){
    if(isEmpty()){
      cout << "ERROR: There is nothing to undo" << endl;
    }else{
      return myObjects[top--];
    }
  } //remove

  //aux/helper functions
  object peek(){
    return myObjects[top];
  } //AKA top

  bool isEmpty(){
    return(top==-1);
  }

  bool isFull(){
      return(top==mSize-1);
  }


  int top;
  int mSize;

//use objects to make the stack generic
//all classes inherit from object
  object *myObjects;
private:
  //nada
};

#endif
