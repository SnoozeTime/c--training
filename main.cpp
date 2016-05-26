#include "vector.hpp"
#include <iostream>
#include "hashmap.hpp"
#include <string>
#include "graph.hpp"
#include "binary_search_tree.hpp"

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
    Tree<int, std::string> tree;
    tree.InsertNode(5, "Paris");
    tree.InsertNode(2, "Londres");
    tree.InsertNode(3, "Luxembourg");
    tree.InsertNode(4, "Jean de la Fontaine city");
    tree.InsertNode(15, "Tokyo");
    tree.InsertNode(17, "Myougadani");
    tree.InsertNode(9, "Hayama");
    tree.InsertNode(8, "somewhere");
    tree.InsertNode(1, "Else");
    tree.InsertNode(10, "Ici et la");

    tree.PrintTree();
    TreeNode<int, std::string>* res = tree.Search(15);
    if (res) {
        std::cout << "Found node. value is " << res->other_data << std::endl;
    }
}
