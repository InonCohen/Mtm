#ifndef GENERICTWLIST_TWLIST_NODE_H
#define GENERICTWLIST_TWLIST_NODE_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

template <class T>
class twListNode
{
    T value;
    twListNode<T> *prev;
    twListNode<T> *next;

public:
    twListNode() = default;
    explicit twListNode(T value, twListNode *prev = NULL, twListNode *next = NULL) : value(value), prev(prev), next(next){};
    explicit twListNode(const twListNode<T> &node) : value(node.value), prev(node.prev), next(node.next){};
    ~twListNode() = default;

    twListNode *getPrev()
    {
        return this->prev;
    }
    twListNode *getNext()
    {
        return this->next;
    }
    void setPrev(twListNode *node)
    {
        this->prev = node;
    }
    void setNext(twListNode *node)
    {
        this->next = node;
    }
    const T &getValue() const
    {
        return this->value;
    }
    T &getValue()
    {
        return this->value;
    }
    void setValue(T &val)
    {
        this->value = val;
    }

    twListNode<T> clone()
    {
        twListNode<T> to_return;
        to_return.setValue(this->value);
        to_return.setPrev(nullptr);
        to_return.setNext(nullptr);
        return to_return;
    }

    bool operator==(twListNode<T> &to_compare)
    {
        if (to_compare == NULL)
        {
            return false;
        }
        return (value == to_compare.value && next = to_compare.next && prev == to_compare.prev);
    }
};

template <class T>
std::ostream &operator<<(std::ostream &os, const twListNode<T> &to_print)
{
    os << to_print.getValue();
    return os;
}

#endif //GENERICTWLIST_TWLIST_NODE_H
