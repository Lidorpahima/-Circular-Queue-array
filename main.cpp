#include "ring.h"
// Include your ring and ring_it implementation or the header file where they are defined.
// Assuming "ring.h" contains the ring and ring_it class definitions.

int main() {
    ring<int, 5> myRing; // Create a ring with a capacity for 5 integers.

    // Adding elements to the ring.
    std::cout << "Adding elements to the ring:\n";
    for(int i = 1; i <= 5; ++i) {
        myRing.push_back(i);
        std::cout << "Added " << i << std::endl;
    }

    // Attempt to add another element, which should cause an overflow.
    std::cout << "\nAttempting to add an element to a full ring...\n";
    try {
        myRing.push_back(6); // This should throw a ring_overflow exception.
    } catch(const ring_overflow& e) {
        std::cout << "Exception caught: Ring is full!\n";
    }

    // Removing two elements from the ring to test underflow.
    std::cout << "\nRemoving two elements from the ring.\n";
    myRing.pop_front();
    myRing.pop_front();
    std::cout << "Two elements removed.\n";

    // Display current contents.
    std::cout << "\nCurrent ring contents: ";
    for(auto it = myRing.begin(); it != myRing.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Clear the ring to demonstrate underflow.
    while(myRing.getCount() > 0) {
        myRing.pop_front();
    }

    // Attempt to remove from an empty ring.
    std::cout << "\nAttempting to remove an element from an empty ring...\n";
    try {
        myRing.pop_front(); // This should throw a ring_underflow exception.
    } catch(const ring_underflow& e) {
        std::cout << "Exception caught: Ring is empty!\n";
    }

    return 0;
}
