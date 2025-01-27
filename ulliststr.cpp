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


void ULListStr::push_back(const std::string& val)
{
  if (!tail_ || tail_->last == ARRSIZE){
    Item* nItem = new Item();
    if (tail_ != nullptr){
      tail_->next = nItem;
      nItem->prev = tail_;
    }
    tail_ = nItem;
    if (head_ == nullptr){
      head_ = nItem;
    }
  }
  tail_->val[tail_->last++] = val;
  size_++;
}

void ULListStr::pop_back()
{
  if (tail_ == nullptr){
    return;
  }
  tail_->last--;
  size_--;
  if (tail_->first == tail_->last) {
    Item* temp = tail_;
    tail_ = tail_->prev;
    if (tail_ != nullptr){
      tail_->next = nullptr;
    } else{
      head_ = nullptr;
    }
    delete temp;
  }
}

void ULListStr::push_front(const std::string& val)
{
  if (!head_ || head_->first == 0) {
    Item* nItem = new Item();
    nItem->last = ARRSIZE;
    nItem->first = ARRSIZE - 1;
    nItem->val[nItem->first] = val;
    nItem->next = head_;
    if (head_) head_->prev = nItem;
    head_ = nItem;
    if (tail_ == nullptr){
      tail_ = nItem;
    }
  } else {
    head_->val[--head_->first] = val;
  }
  size_++;
}

void ULListStr::pop_front()
{
  if (head_ == nullptr){
    return;
  }
  head_->first++;
  size_--;
  if (head_->first == head_->last){
    Item* temp = head_;
    head_ = head_->next;
    if (head_ != nullptr){
      head_->prev = nullptr;
    } else{
      tail_ = nullptr;
    } 
    delete temp;
  }
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  Item* curr = head_;
  while (curr != nullptr){
    size_t num = curr->last - curr->first;
    if (loc < num) {
      return &curr->val[curr->first+loc];
    }
    loc -= num;
    curr = curr->next;
  }
  return NULL; 
}