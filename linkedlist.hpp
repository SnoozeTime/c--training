#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>


template<typename T>
class LinkedList
{

private:
    struct Node;
    typedef std::shared_ptr<Node> NodePtr;

    struct Node {
        Node(T value): data(value) {};
        NodePtr next;
        std::weak_ptr<Node> previous;
        T data;
    }

    /*
        First node of the list.
    */
    NodePtr head_;

    /*
        Last node of the list.
    */
    NodePtr tail_;

public:
    /*
        Create a new node at the end of the list.
    */
    void push_back(T value)
    {
        auto new_node = std::make_shared<Node>(value);
        if (new_node) {
            tail_->next = new_node;
            std::swap(tail_, tail_->next);
        }
    }

    /*
        Create new node at the beginning of the list.
    */
    void push_front(data)
    {
        auto new_node = std::make_shared<Node>(value);
        if (new_node) {
            head_->previous = new_node;
            std::swap(head_, head_->previous);
        }
    }

};
#endif
