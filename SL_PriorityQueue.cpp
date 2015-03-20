//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.
// PARITALLY COMPLETE.

/** ADT priority queue: ADT sorted list implementation.
 @file SL_PriorityQueue.cpp */
 
#include "SL_PriorityQueue.h"  // Header file

template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue(){
   slistPtr = new LinkedSortedList<ItemType>();
}

template<class ItemType>
SL_PriorityQueue<ItemType>::~SL_PriorityQueue() {
	while(!isEmpty()) {
		remove();
	}
}

template<class ItemType>
bool SL_PriorityQueue<ItemType>::add(const ItemType& newEntry)
{ 
   slistPtr->insertSorted(newEntry);
   return true;
}  // end add

template<class ItemType>
bool SL_PriorityQueue<ItemType>::remove()
{
   // The highest priority item is at the end of the sorted list
   return slistPtr->remove(1);
}  // end remove
  
template<class ItemType>
ItemType SL_PriorityQueue<ItemType>::peek() const  {
	//if (isEmpty())
		//throw PrecondViolatedExcep("peekFront() called with empty queue.");
	return slistPtr->getEntry(1);
} // end peek

template<class ItemType>
bool SL_PriorityQueue<ItemType>::isEmpty() const {
	return slistPtr->isEmpty();
} // end isEmpty
