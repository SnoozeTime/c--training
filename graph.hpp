#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <vector>
#include <string>
#include <stdexcept>
/*
    Implementation with adjacent lists. This time, I will be using the stl containers
    vector and list.

    In SGraph. vertice and edges have values.
    in SGraph2, only edges have value.
*/
template<typename VV, typename EV>
class SGraph
{
    /*
        A node is not a vertice. The first node of the list is a vertex and the
        next nodes are the vertice linked to the first.
        For example
        0 -> 1 -> 2
        1 -> 0
        2 -> 0
        Is a graph of 3 vertice and 2 edges.
    */
    struct Edge
    {
        Edge(EV v, int d): value(v), destination(d) {}
        // Value of the Edge.
        EV value;

        // indice in the vector of the vertex it is pointing to.
        int destination;
    };

    struct Vertex
    {
        Vertex(VV v): value(v) {}

        // Value of the node.
        VV value;

        // list of edges.
        std::list<Edge> edges;
    };

    // Array of linked lists for the graph.
    std::vector<Vertex> graph_;

public:
    /*
        Create a graph of nb_vertice vertice
    */
    SGraph()
    {

    }

    // just push back an element to the vector.
    void AddVertex(VV value)
    {
        // No edges yet.
        graph_.emplace_back(value);
    }

    /*
        Add an edge from i to j with the value EV.
        throw out of range exception if i or j > size of graph.

        Return false if edge already exists.
    */
    bool AddEdge(int origin, int destination, EV value)
    {
        if (origin >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(origin));
        }

        if (destination >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(destination));
        }

        // Check if edge is already there.
        if (HasEdge(origin, destination)) {
            return false;
        }

        // Add the edge.
        graph_[origin].edges.emplace_back(value, destination);
        return true;
    }

    /*
        Add edges with the same value
        bool if inserting one edge failed (if already exists)
    */
    bool AddEdges(int vertex_1, int vertex_2, EV value)
    {
        return AddEdge(vertex_1, vertex_2, value) && AddEdge(vertex_2, vertex_1, value);
    }

    void PrintGraph()
    {
        for (auto v : graph_)
        {
            std::cout << v.value << " has " << v.edges.size() << " edge(s)\n";
            for (auto& e : v.edges) {
                std::cout << v.value << " - " << graph_[e.destination].value << ": " << e.value << std::endl;
            }
        }
    }

    bool HasEdge(int origin, int destination)
    {
        if (origin >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(origin));
        }

        if (destination >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(destination));
        }

        for (auto& e : graph_[origin].edges) {
            if (e.destination == destination) {
                return true;
            }
        }
        return false;
    }

    size_t nb_vertice_;
};


template<typename EV>
class SGraph2
{
    /*
        A node is not a vertice. The first node of the list is a vertex and the
        next nodes are the vertice linked to the first.
        For example
        0 -> 1 -> 2
        1 -> 0
        2 -> 0
        Is a graph of 3 vertice and 2 edges.
    */
    struct Edge
    {
        Edge(EV v, int d): value(v), destination(d) {}
        // Value of the Edge.
        EV value;

        // indice in the vector of the vertex it is pointing to.
        int destination;
    };


    // Array of linked lists for the graph.
    std::vector<std::list<Edge>> graph_;

public:
    /*
        Create a graph of nb_vertice vertice
    */
    SGraph2()
    {

    }

    // just push back an element to the vector.
    void AddVertex()
    {
        // No edges yet.
        graph_.emplace_back();
    }

    /*
        Add an edge from i to j with the value EV.
        throw out of range exception if i or j > size of graph.

        Return false if edge already exists.
    */
    bool AddEdge(int origin, int destination, EV value)
    {
        if (origin >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(origin));
        }

        if (destination >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(destination));
        }

        // Check if edge is already there.
        if (HasEdge(origin, destination)) {
            return false;
        }

        // Add the edge.
        graph_[origin].emplace_back(value, destination);
        return true;
    }

    /*
        Add edges with the same value
        bool if inserting one edge failed (if already exists)
    */
    bool AddEdges(int vertex_1, int vertex_2, EV value)
    {
        return AddEdge(vertex_1, vertex_2, value) && AddEdge(vertex_2, vertex_1, value);
    }

    void PrintGraph()
    {
        for (int i = 0; i < graph_.size(); i++)
        {
            std::cout << i << " has " << graph_[i].size() << " edge(s)\n";
            for (auto& e : graph_[i]) {
                std::cout << i << " - " << e.destination << ": " << e.value << std::endl;
            }
        }
    }

    bool HasEdge(int origin, int destination)
    {
        if (origin >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(origin));
        }

        if (destination >= graph_.size()) {
            throw std::out_of_range("Origin index is out of range: " + std::to_string(destination));
        }

        for (auto& e : graph_[origin]) {
            if (e.destination == destination) {
                return true;
            }
        }
        return false;
    }

    size_t nb_vertice_;
};

#endif
