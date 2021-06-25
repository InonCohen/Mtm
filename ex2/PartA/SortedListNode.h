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
        SortedListNode<T> *next;

    public:
        explicit SortedListNode(T value, SortedListNode *next = NULL);
        explicit SortedListNode(const SortedListNode<T> &node);
        SortedListNode& operator=(const SortedListNode<T>& other);
        ~SortedListNode();
        static void deleteRecursively(SortedListNode<T>* node);
        SortedListNode* getNext() const;
        void setNext(SortedListNode *node);
        const T& getValue() const;
        void setValue(T &val);
        SortedListNode<T>& deepCopyAhead() const;
        bool operator==(SortedListNode<T> &to_compare);
    };

    template <class T>
    SortedListNode<T>::SortedListNode(T value, SortedListNode *next) : value(value), next(next){}

    template <class T>
    SortedListNode<T>::SortedListNode(const SortedListNode<T> &node) : value(node.value), next(node.next){}

    template <class T>
    SortedListNode<T>& SortedListNode<T>::operator=(const SortedListNode<T>& other){
        if(this == &other){
            return *this;
        }
        value = other.value;
        next = other.next;
        return *this;
    }

    template <class T>
    SortedListNode<T>::~SortedListNode<T>() {
        next = nullptr;
    }

    template <class T>
    void SortedListNode<T>::deleteRecursively(SortedListNode<T>* node){
        while(node != nullptr){
            SortedListNode<T>* temp = node->getNext();
            delete node;
            node = temp;
        }
    }

    template <class T>
    SortedListNode<T>* SortedListNode<T>::getNext() const
    {
        return next;
    }
    

    template <class T>
    void SortedListNode<T>::setNext(SortedListNode* node)
    {
        next = node;
    }

    template <class T>
    const T& SortedListNode<T>::getValue() const
    {
        return value;
    }


    template <class T>
    void SortedListNode<T>::setValue(T& val)
    {
        value = val;
    }

    template <class T>
    SortedListNode<T>& SortedListNode<T>::deepCopyAhead() const
    {
        SortedListNode<T>* to_return= new SortedListNode<T>(*this);
        T val = value;
        to_return->setValue(val);
        to_return->setNext(nullptr);
        SortedListNode<T>* ptr_of_copy = to_return;
        SortedListNode<T>* ptr_of_original = this->next;
        while (ptr_of_original){
            ptr_of_copy->setNext(new SortedListNode<T>(ptr_of_original->getValue()));
            SortedListNode<T>* next_copy = ptr_of_copy->getNext();
            val = ptr_of_original->getValue();
            next_copy->setValue(val);
            next_copy->setNext(nullptr);
            ptr_of_copy = ptr_of_copy->next;
            ptr_of_original = ptr_of_original->next;
        }
        return *to_return;
    }

    template <class T>
    bool SortedListNode<T>::operator==(SortedListNode<T> &to_compare) {
        return (!(value < to_compare.value) && !(to_compare.value < value) && next == to_compare.next);
    }



    template <class T>
    std::ostream &operator<<(std::ostream &os, const SortedListNode<T> &to_print)
    {
        os << to_print.getValue();
        return os;
    }
}

#endif //GENERICTWLIST_TWLIST_NODE_H
