#include "ring.h"
int main() {
 ring<int, 3> l;
 cout << l << "\n";
 try {
 l.push_back(1);
 l.push_back(2);
 l.push_back(3);
 l.push_back(4);
 } catch (ring_overflow e) {
 cout << "overflow" << l << "\n";
 }
 try {
 l.pop_front();
 l.pop_front();
 l.pop_front();
 l.pop_front();
 } catch (ring_underflow e) {
 cout << "underflow" << l << "\n";
 }
 l.push_back(5);
 l.push_back(7);
 cout << l << "\n";
 cout << "pop() = " << l.pop_front() << "\n";
 cout << l << "\n";
 l.push_back(4);
 cout << l << "\n";
  l.push_back(5);
 cout << "pop() = " << l.pop_front() << "\n";

cout << l << "\n";

 for (auto x : l){
 cout << x << " ";
 cout << "\n";
 }
}