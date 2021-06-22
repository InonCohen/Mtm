#ifndef GENERICTWLIST_TWLIST_NODE_H
#define GENERICTWLIST_TWLIST_NODE_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

namespace mtm{
    template <class T>
    class SortedListNode
    {
        T value;
        SortedListNode<T> *prev;
        SortedListNode<T> *next;

    public:
        SortedListNode() = default;
        explicit SortedListNode(T value, SortedListNode *prev = NULL, SortedListNode *next = NULL);
        explicit SortedListNode(const SortedListNode<T> &node);
        ~SortedListNode() = default;
        SortedListNode* getPrev() const;
        SortedListNode* getNext() const;
        void setPrev(SortedListNode *node);
        void setNext(SortedListNode *node);
        const T& getValue() const;
        void setValue(T &val);
        SortedListNode<T>& clone() const;
        bool operator==(SortedListNode<T> &to_compare);
    };

    template <class T>
    SortedListNode<T>::SortedListNode(T value, SortedListNode* prev, SortedListNode *next) : value(value), prev(prev), next(next){}

    template <class T>
    SortedListNode<T>::SortedListNode(const SortedListNode<T> &node) : value(node.value), prev(node.prev), next(node.next){}

    template <class T>
    SortedListNode<T>* SortedListNode<T>::getPrev() const
    {
        return this->prev;
    }

    template <class T>
    SortedListNode<T>* SortedListNode<T>::getNext() const
    {
        return this->next;
    }

    template <class T>
    void SortedListNode<T>::setPrev(SortedListNode* node)
    {
        this->prev = node;
    }

    template <class T>
    void SortedListNode<T>::setNext(SortedListNode* node)
    {
        this->next = node;
    }

    template <class T>
    const T& SortedListNode<T>::getValue() const
    {
        return this->value;
    }


    template <class T>
    void SortedListNode<T>::setValue(T &val)
    {
        this->value = val;
    }

    template <class T>
    SortedListNode<T>& SortedListNode<T>::clone() const
    {
        SortedListNode<T> to_return;
        to_return.setValue(this->value);
        to_return.setPrev(nullptr);
        to_return.setNext(nullptr);
        return to_return;
    }

    template <class T>
    bool SortedListNode<T>::operator==(SortedListNode<T> &to_compare)
    {
        if (to_compare == NULL)
        {
            return false;
        }
        return (value == to_compare.value && next = to_compare.next && prev == to_compare.prev);
    }


    template <class T>
    std::ostream &operator<<(std::ostream &os, const SortedListNode<T> &to_print)
    {
        os << to_print.getValue();
        return os;
    }
}

#endif //GENERICTWLIST_TWLIST_NODE_H
