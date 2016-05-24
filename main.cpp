#include "vector.hpp"
#include <iostream>
#include "hashmap.hpp"
#include <string>
#include "graph.hpp"

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
    SGraph<std::string, int> graph;
    graph.AddVertex("Washington");
    graph.AddVertex("Paris");
    graph.AddVertex("Tokyo");
    graph.AddVertex("London");

    graph.AddEdge(0, 1, 1);
    graph.AddEdges(0, 2, 5);
    graph.AddEdge(1, 2, 2);
    graph.AddEdge(3, 1, 4);


    graph.PrintGraph();
}
