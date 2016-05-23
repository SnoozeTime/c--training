#include "vector.hpp"
#include <iostream>
#include "hashmap.hpp"
#include <string>

#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */

struct StringHash {
    unsigned long operator()(const std::string& key) const
    {
        unsigned long h = 31;
        for (auto c : key) {
            h = (h * A) ^ (c * B);
        }
        return h % TABLE_SIZE;
    }
};

int main()
{
    HashMap<std::string, std::string, StringHash> map;
    map.put("one", "two");
    std::string value;
    if (map.get("one", value)) {
        std::cout << value << std::endl;
    }
}
