#include <iostream>
#include <string>
#include <cstdlib>
#include "lliststr.h"

using namespace std;
using std::string;



  /**
   * Default constructor
   */
  LListStr::LListStr()
  {

    
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
  }

  /**
   * Destructor
   */
  LListStr:: ~LListStr()
  {
    while(head_!=NULL)
    {
      Item *temp = head_->next;
      delete head_;
      head_ = temp;
    }
    tail_ = NULL;
    size_ = 0;
  }
  /**
   * Returns the current number of items in the list
   */
  int LListStr::size() const
  {
    return size_;
  }

  /**
   * Returns true if the list is empty, false otherwise
   */
  bool LListStr::empty() const
  {
    return size_ == 0;
  }

  /**
   * Inserts val so it appears at the index given as pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void LListStr::insert(int pos, const string &value)
  {
    if (pos >= 0 && pos <= size_)
    {
      

      if (pos == 0)
      {
        Item *temp = position(pos);
        head_ = new Item;
        head_->next = temp;
        head_->prev = NULL;
        head_-> val = value;
        size_++;
       
       if(size_ == 1)
       {
          tail_ = head_;
       }
       else
       {
          temp -> prev = head_;
       }
      }

     

      else if (size_ == pos)
      {
        Item *temp = position(pos-1); 
        temp-> next  =  new Item;
        Item* ptr = temp->next;
        ptr->prev = temp;
        ptr->next = NULL;
        ptr->val = value;
        size_++;
        tail_ = ptr;


      }

      else
      {
       
        Item *temp = position(pos);
         Item *newNode = temp ->prev;
         newNode-> next = new Item;

         Item* pa = newNode-> next;
         temp->prev = pa;
         pa->next = temp;
         pa->prev = newNode;
         pa->val = value;

         size_++;
      }
    }

    
  }

  /**
   * Removes the value at the index given by pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void LListStr::remove(int pos)
  {
    if (pos >= 0 && pos <= size_)
    {
      
      if (pos == 0)
      {

        Item *temp = position(pos);
        Item *ptr = temp->next;
        delete temp;
        head_ = ptr;
        size_--;
        if(size_ == 0)
        {
          tail_ = NULL;
        }

        else
        {
          ptr->prev = NULL;
        }
  
       }

      else if (pos == size_-1)
      {
        Item *temp = position(pos);
        Item *ptrb = temp->prev;
        delete temp;
        ptrb->next = NULL;
        tail_ = ptrb;
        size_--;

        
      }

      else
      {
        Item *temp = position(pos);
        Item *pa = temp->prev;
        Item *pb = temp->next;
        pa->next = pb;
        pb->prev = pa;

        delete temp;
        
        size_--;


    
      }
    }

    return;
  }

  /**
   * Overwrites the old value at the index given by pos with val. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */
  void LListStr::set(int pos, const string &value)
  {

    if (pos >= 0 && pos <= size_)
    {
      Item *temp = position(pos);
      temp->val = value;
    }

    return;
  
  }

  /**
   * Returns the value at the index given by pos.  If the index pos is invalid,
   * then you should return the empty string.
   */
  string LListStr::get(int pos) const
  {
    string s = "";
    if (pos >= 0 && pos < size_)
    {
      Item *temp = position(pos);
      return temp->val;
    }

    else
    {
      return s;
    }
     
  }

  LListStr::Item* LListStr::position(int pos) const
  {
    Item *temp;
    temp = head_;
   if(pos>=0 && pos <size_)
    {
      while(temp!=NULL && pos >0){
        temp = temp->next;
        pos--;
      }

      return temp;
      
  }
      else
      {
          return NULL;
      }
    

    return temp;
  }


