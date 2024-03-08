#include "std_lib_facilities.h"
#pragma once


struct ring_overflow : std::exception {};
struct ring_underflow : std::exception {};
template<class T, int N>
class ring {
     T data[N];
    int head = 0;
    int tail = 0;
    int count = 0;
    
  public:
  mutable bool Overflow = false;
  void push_back(T element){
    if(count == N) {
      Overflow = true;
      throw ring_overflow();
    }
    data[head] = element;
    head = (head +1) % N;
    count++;
    }

  T pop_front(){
    if(count == 0)throw ring_underflow();
  T element = data[tail];
  tail = (tail + 1) % N;
  count--;
  return element;
  }

    T GetElement(int index) const {
        return data[(tail + index) % N];
    }


T* begin() { 
        return &data[tail]; 
    }

    T* end() { 
        if (head >= tail) {
            return &data[head]; 
        } else {
            return &data[N]; 
        }
    }

      int size() const { 
      return count; 
      }

};
template<class T, int N>
std::ostream& operator<<(std::ostream& os, const ring<T, N>& r) {
  if(r.Overflow){
    os <<" ";
    r.Overflow =false;
  }else{
   if(r.size() == 0 ){
    os << " ";
   }else{
    for (int i = 0; i < r.size(); i++) {
        os << r.GetElement(i) << " ";
    }
   }
   }
   return os;
    
}
     
template<class T, int N>
class ring_it {
private:
    const ring<T, N>& r;
    int position;

public:
    ring_it(const ring<T, N>& ring, int pos) : r(ring), position(pos) {}

    ring_it& operator++() {
        position = (position + 1) % N;
        return *this;
    }

    bool operator!=(const ring_it& other) const {
        return position != other.position;
    }

    const T& operator*() const {
        return r.at(position);
    }
};
