#include "Heap.h" // include the header file for the Heap class
#include <iostream> // include the standard input/output library

using namespace std; // use the standard namespace

// constructor for Heap class
Heap::Heap()
{
  numItems = 0 ; // initialize the number of items to zero
}

// enqueue a new element into the heap
void Heap::enqueue(PrintJob* addElement)
{
  if (numItems != MAX_HEAP_SIZE) // if the heap is not full
  {
    if (numItems == 0) // if this is the first element
    {
      arr[numItems] = addElement ; // add the new element at the root
      numItems++ ;
    }

    else // otherwise, find the correct position in the heap based on priority
    {
      int currentIndex = numItems ;

      while (currentIndex > 0 && arr[(currentIndex - 1) / 2]->getPriority() < addElement->getPriority())
      {
      arr[currentIndex] = arr[(currentIndex - 1) / 2] ;
      currentIndex = (currentIndex - 1) / 2 ;
      }

      arr[currentIndex] = addElement ;
      numItems++ ;
    }
  }
}

// remove the element with the highest priority from the heap
void Heap::dequeue()
{
  if (numItems != 0) // if the heap is not empty
  {
    if (numItems != 1) // if the heap has more than one element
    {
      arr[0] = arr[numItems - 1] ; // move the last element to the root
    }
    numItems--;
    trickleDown(0); // move the new root down the heap to the appropriate location
  }
}

// return the element with the highest priority
PrintJob* Heap::highest()
{
  return numItems == 0 ? nullptr : arr[0] ;
}

// print the element with the highest priority
void Heap::print()
{
  if (numItems != 0)
  {
    cout << "Priority: " << highest()->getPriority() // print priority
          << ", Job Number: " << highest()->getJobNumber() // print job number
          << ", Number of Pages: " << highest()->getPages() ; // print number of pages
  }
  cout << endl ; // print a new line
}

// move the new root down the heap to the appropriate location
void Heap::trickleDown(int index)
{
  if (numItems < index * 2 + 2) // if the current index is a leaf node
  {
    return ; // return and do nothing
  }
  else if (numItems == index * 2 + 2) // if the current index has only one child
  {
    if (arr[index] -> getPriority() < arr[numItems - 1] -> getPriority())
    {
      swap(index, numItems - 1); // swap if necessary
    }
  }
  else // if the current index has two children
  {
    PrintJob* leftChild = arr[index * 2 + 1] ;
    PrintJob* rightChild = arr[index * 2 + 2] ;
    if (leftChild->getPriority() > rightChild->getPriority()) // compare priority of the two children
    {
      if (leftChild->getPriority() > arr[index]->getPriority()) // compare priority with the left child
      {
        swap(index, index * 2 + 1); // swap if necessary
      }
      trickleDown(index * 2 + 1); // recurse on the left child
    }
    else
    {
      if (rightChild -> getPriority() > arr[index] -> getPriority())
      {
        swap(index, index * 2 + 2) ;
      }
      trickleDown(index * 2 + 2) ; 
    }
  }
}

//swap function
void Heap::swap(int first_Pos, int sec_Pos) 
{
  PrintJob* swap_value = arr[first_Pos] ;
  arr[first_Pos] = arr[sec_Pos] ;
  arr[sec_Pos] = swap_value ; 
}
