#ifndef LISTNODE_H
#define LISTNODE_H

#include <iostream>

template <typename T>
class ListNode
{
public:
    T value;
    ListNode<T>* next = nullptr;

    ListNode(T value) : value(std::move(value)) {}

    //Output for debugging
    void dump(std::ostream& out) const
    {
        out << value;
    }
};

template <typename T>
std::ostream& operator<< (std::ostream& out, const ListNode<T>& node)
{
    node.dump(out);
    return out;
}

#endif // LISTNODE_H
