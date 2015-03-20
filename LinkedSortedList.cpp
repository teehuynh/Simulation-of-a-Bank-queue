//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// PARITALLY COMPLETE.


/** Implementation file for the class LinkedSortedList.
 @file LinkedSortedList.cpp */

#include "LinkedSortedList.h"  // Header file
#include <cassert>
  
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(): headPtr(nullptr), itemCount(0){}

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList)
{
	headPtr = copyChain(aList.headPtr);
}  // end copy constructor

template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
//	  virtual void insertSorted(const ItemType& newEntry) = 0;
{
   Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
   Node<ItemType>* prevPtr = getNodeBefore(newEntry);
   
   if (isEmpty() || (prevPtr == nullptr)) // Add at beginning
   {
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
   }
   else // Add after node before
   {
      Node<ItemType>* aftPtr = prevPtr->getNext();
      newNodePtr->setNext(aftPtr);
      prevPtr->setNext(newNodePtr);
   } // end if
   
   itemCount++;
} // end insertSorted

// Private Methods:

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(const Node<ItemType>* origChainPtr)
{
   Node<ItemType>* copiedChainPtr;
	if (origChainPtr == nullptr)
	{
      copiedChainPtr = nullptr;
   }
   else
   {
		// Build new chain from given one
		copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
	}  // end if
   
	return copiedChainPtr;
}  // end copyChain

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
   Node<ItemType>* curPtr = headPtr;
   Node<ItemType>* prevPtr = nullptr;
   
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
	   //cout << "curPtr " << curPtr->getItem() << endl;
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
   } // end while
   
   return prevPtr;
} // end getNodeBefore


  //  LinkedSortedList(const LinkedSortedList<ItemType>& aList);
template<class ItemType>
LinkedSortedList<ItemType>:: ~ LinkedSortedList()
{
	clear();
}


template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& anEntry)
//	   virtual bool removeSorted(const ItemType& anEntry) = 0;
{
	return remove (getPosition(anEntry));
}
template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType& anEntry) 
//	   virtual int getPosition(const ItemType& anEntry) = 0;
{
	Node<ItemType>* curr = headPtr;
	int pos = 1;
	while (curr != nullptr && !(anEntry == curr -> getItem()))
	{
		pos ++;
		curr = curr->getNext();

	}
	return pos;
}

// The following methods are the same as given in ListInterface
template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
//	   virtual bool isEmpty() const = 0;
{
	return headPtr == nullptr;
}
template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
//	   virtual int getLength() const = 0;
{
	return itemCount;
}
template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
//	   virtual bool remove(int position) = 0;
{
	Node<ItemType>* prev = getNodeBefore (getEntry(position));
	Node<ItemType>* curr;
	if (prev == nullptr)
	{
		curr = headPtr;
		headPtr = curr->getNext();
	}
	else 
	{
		curr = prev->getNext();
		prev->setNext(curr->getNext());
	}
	itemCount--;
	delete curr;
	return true;
}

template<class ItemType>
void LinkedSortedList<ItemType>::clear()
//	   virtual void clear() = 0;
{
	while (! isEmpty ())
		remove (1);
}

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const
//	   virtual ItemType getEntry(int position) const = 0;
{
	Node<ItemType>* curr = headPtr;
	while (position > 1)
	{
		curr = curr -> getNext();
		cout << "curr " << curr->getItem() << endl;
		position --;
	}
	return curr -> getItem();
}

/*template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::
                               getNodeBefore(const ItemType& anEntry) const
{
    Node<ItemType>* curPtr = headPtr;
    Node<ItemType>* prevPtr = nullptr;
    while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
    {
        prevPtr = curPtr;
        curPtr = curPtr->getNext();
    } // end while

    return prevPtr;
} // end getNodeBefore */

// Locates the node at a given position within the chain
template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAt(int position) const
{
	Node<ItemType>* curr = headPtr;
	while (position > 1)
	{
		curr = curr -> getNext();
		position --;
	}
	return curr;
}
