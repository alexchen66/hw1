/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>


/* Add a prototype for a helper function here if you need */
void splithelper(Node*& in, Node*& odds, Node*& evens, Node*& oddscur, Node*& evenscur);

void split(Node*& in, Node*& odds, Node*& evens)
{
  Node* oddscur = NULL;
  Node* evenscur = NULL;
  odds = NULL;
  evens = NULL;
  splithelper(in, odds, evens, oddscur, evenscur);
}

/* If you needed a helper function, write it here */
void splithelper(Node*& in, Node*& odds, Node*& evens, Node*& oddscur, Node*& evenscur){
  if(in == NULL){
    return;
  }
  if(in->value % 2 == 1){
    if(odds == NULL){
      odds = in;
      in = in->next;
      odds->next = NULL;
      oddscur = odds;
    }
    else{
      oddscur->next = in;
      in = in->next;
      oddscur->next->next = NULL;
      oddscur = oddscur->next;
    }
  }
  else if(in->value % 2 == 0 || in->value == 0){
    if(evens == NULL){
      evens = in;
      in = in->next;
      evens->next = NULL;
      evenscur = evens;
    }
    else{
      evenscur->next = in;
      in = in->next;
      evenscur->next->next = NULL;
      evenscur=evenscur->next;
    }
  }
  splithelper(in, odds, evens, oddscur, evenscur);
}