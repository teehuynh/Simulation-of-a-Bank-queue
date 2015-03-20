//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// PARITALLY COMPLETE.

/** @file LinkedQueue.cpp */

#include "LinkedQueue.h"  
#include <cassert>

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() : backPtr(nullptr), frontPtr(nullptr){}

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue(){
	while(!isEmpty()) {
		dequeue();
	}
}

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
   Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);	

   // Insert the new node
   if (isEmpty())
      frontPtr = newNodePtr;        // Insertion into empty queue
   else
      backPtr->setNext(newNodePtr); // Insertion into nonempty queue
   
   backPtr = newNodePtr;            // New node is at back
   
	return true;
}  // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
      // Queue is not empty; delete front
		Node<ItemType>* nodeToDeletePtr = frontPtr;
      if (frontPtr == backPtr)
      {  // Special case: one node in queue
         frontPtr = nullptr;
         backPtr = nullptr;
      }
      else
		   frontPtr = frontPtr->getNext();
		
		// Return deleted node to system
      nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr;
      
      result = true;
	}  // end if
   
	return result;	
}  // end dequeue

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const {
	return frontPtr == nullptr;
} // end isEmpty

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const {
	return frontPtr->getItem();
}