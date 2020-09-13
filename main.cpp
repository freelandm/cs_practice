#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Hash.h" 
namespace exp = experiment;

void fill_integer_hash(exp::Hash<int>& integer_hash)
{
    auto capacity = integer_hash.capacity();
    for (size_t i = 0; i <= capacity; ++i) {
        integer_hash.insert(i);
    }
}

int main(int argc, char* argv [])
{
    exp::Hash<int> my_hash;

    // fill the hash with integers
    fill_integer_hash(my_hash);
    std::cout << "Hash size: " << my_hash.size() << ", Hash capacity: " << my_hash.capacity() << std::endl;

    // try to fill the hash again... it shouldn't allow it
    fill_integer_hash(my_hash);

    // try to erase a value that doesn't exist in hash. let's log some type of notice that it wasn't successful
    my_hash.erase(350);
    // try to erase a value that does exist in hash.
    my_hash.erase(20);

    // let's insert some random value into the hash, it should go into the slot where 20 was, since we deleted it in the last call!
    my_hash.insert(1082387);
    // at capacity
    my_hash.insert(1082387);

    my_hash.erase(0);
    // existing key
    my_hash.insert(1082387);
}
