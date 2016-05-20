#include "vector.hpp"
#include <iostream>

int main()
{
    SVector<int> v(10);

    for (int i = 0; i < 20; i++) {
        v.push_back(i);
    }
    std::cout << v.at(8) << std::endl;
}
