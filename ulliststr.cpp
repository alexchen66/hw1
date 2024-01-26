#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
/**
  * Adds a new value to the back of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::push_back(const std::string& val)
{
  if (tail_ == NULL)
  {
    tail_ = new Item();
    tail_->val[tail_->first] = val; // add value to first position of new array
    tail_->last++; // last position moved to index 1
    head_ = tail_;
  }
  else if (tail_->last < ARRSIZE)
  {
    tail_->val[tail_->last] = val; // add to the last position
    tail_->last++;
  }
  else // when full
  {
    Item* new_tail = new Item();
    new_tail->val[new_tail->first] = val;
    new_tail->last++;
    new_tail->prev = tail_;
    tail_->next = new_tail;
    tail_ = new_tail;
  }
  size_++;
}

/**
  * Removes a value from the back of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::pop_back()
{
  if (tail_ != NULL)
  {
    tail_->last--;
    if (tail_->first == tail_->last) // array empty
    {
      if (tail_->prev == NULL) // list empty
      {
        Item* temp = tail_;
        tail_ = head_ = NULL;
        delete temp;
      }
      else
      {
        Item* temp = tail_;
        tail_ = tail_->prev;
        tail_->next = NULL;
        delete temp;
      }
    }
    size_--;
  }
  return;
}

/**
  * Adds a new value to the front of the list.
  * If there is room before the 'first' value in
  * the head node add it there, otherwise, 
  * allocate a new head node.
  *   - MUST RUN in O(1)
  */
void ULListStr::push_front(const std::string& val)
{
  if (head_ == NULL)
  {
    head_ = new Item();
    head_->first = head_->last = ARRSIZE - 1;
    head_->val[ARRSIZE - 1] = val;
    head_->last++;
    tail_ = head_;
  }
  else if (head_->first != 0)
  {
    head_->first--;
    head_->val[head_->first] = val;
  }
  else
  {
    Item* new_head = new Item();
    new_head->first = new_head->last = ARRSIZE - 1; // last position of array
    new_head->val[ARRSIZE - 1] = val;
    new_head->last++;
    new_head->next = head_;
    head_->prev = new_head;
    head_ = new_head;
  }
  size_++;
}

/**
  * Removes a value from the front of the list
  *   - MUST RUN in O(1)
  */
void ULListStr::pop_front()
{
  if (head_ != NULL)
  {
    head_->first++;
    if (head_->first == head_->last) // array empty
    {
      if (head_->next == NULL) // all lists empty
      {
        Item* temp = head_;
        tail_ = head_ = NULL;
        delete temp;
      }
      else
      {
        Item* temp = head_;
        head_ = head_->next;
        head_->prev = NULL;
        delete temp;
      }
    }
    size_--;
  }
  return;
}

/**
  * Returns a const reference to the back element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::back() const
{
  // no error handling
  return tail_->val[tail_->last - 1];
}

/**
  * Returns a const reference to the front element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

/** 
  * Returns a pointer to the item at index, loc,
  *  if loc is valid and NULL otherwise
  *   - MUST RUN in O(n) 
  */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc >= size_)
  {
    return NULL;
  }
  Item* curr = head_;
  size_t item_counter = 0; // values of one list
  size_t index_counter = 0; // all values
  while (curr != NULL)
  {
    item_counter = (curr->last - curr->first);
    if (item_counter + index_counter > loc)
    {
      return& curr->val[loc - index_counter + curr->first];
    }
    index_counter += (curr->last - curr->first);
    curr = curr->next;
  }
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
