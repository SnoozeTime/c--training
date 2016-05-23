#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <memory>
#include <unistd.h>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <iostream>

template<typename T>
class SLinkedList
{

private:
    struct NodeBase;
    typedef std::shared_ptr<NodeBase> NodePtr;

    struct NodeBase {
        NodeBase() {}
        virtual ~NodeBase() {}

        NodeBase* next;
        NodeBase* previous;
    };

    struct Sentinel : public NodeBase {
        Sentinel() {}

    };

    struct Node : public NodeBase {
        Node(): T() {};
        Node(T value): data(value) {};
        ~Node() {
            data.~T();
        }

        T value() {
            return data;
        }

        T data;
    };

    /*
        Dummy node that hold no data to allow empty list and remove necessary to
        check for Null ptr
    */
    Sentinel* sentinel_head_;
    Sentinel* sentinel_tail_;

    /*
        Number of elements in the list
    */
    size_t size_;
public:

    SLinkedList():
        sentinel_head_(new Sentinel()),
        sentinel_tail_(new Sentinel()),
        size_(0)
    {
        sentinel_head_->next = sentinel_tail_;
        sentinel_head_->previous = sentinel_tail_;

        sentinel_tail_->previous = sentinel_head_;
        sentinel_tail_->next = sentinel_head_;
    }

    ~SLinkedList()
    {
        // Traverse the list to delete the pointers
        NodeBase* first = sentinel_head_->next;
        while (first != nullptr && first != sentinel_tail_) {
            NodeBase *move = first;
            first = first->next;
            delete move;
        }

        delete sentinel_head_;
        delete sentinel_tail_;
    }

    /*
        First node of the list.
    */
    NodeBase* head() {
        return sentinel_head_->next;
    }

    /*
        Last node of the list.
    */
    NodeBase* tail() {
        return sentinel_tail_->previous;
    }

    /*
        Get size of the list
    */
    size_t size() const
    {
        return size_;
    }

    /*
        Create a new node at the end of the list.
    */
    void push_back(T value)
    {
        NodeBase* new_node = new Node(value);

        if (new_node) {
            new_node->previous = tail();
            tail()->next = new_node;
            sentinel_tail_->previous = new_node;
            size_++;
        }
    }

    /*
        Create new node at the beginning of the list.
    */
    void push_front(T value)
    {
        NodeBase* new_node = new Node(value);

        if (new_node) {
            new_node->next = head();
            head()->previous = new_node;
            sentinel_head_->next = new_node;
            size_++;
        }
    }

    /*
        Remove node from the left.
    -*/
    void pop_front()
    {
        // Check that there is at least one element to pop_front
        if (size_ > 0) {

            auto the_head = sentinel_head_->next;

            sentinel_head_->next = sentinel_head_->next->next;
            sentinel_head_->next->previous = sentinel_head_;

            delete the_head;
            the_head = nullptr;

            size_--;
        }
    }

    /*
        Remove node from the right
    -*/
    void pop_back()
    {
        // Check that there is at least one element to pop_front
        if (size_ > 0) {
            // get the last element.
            auto the_tail = sentinel_tail_->previous;
            sentinel_tail_->previous = sentinel_tail_->previous->previous;
            sentinel_tail_->previous->next = sentinel_tail_;

            delete the_tail;
            the_tail = nullptr;

            size_--;
        }
    }

};
#endif
