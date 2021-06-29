#ifndef GENERICTWLIST_TWLIST_NODE_H
#define GENERICTWLIST_TWLIST_NODE_H

#include <cstdlib>
#include <cstdio>
#include <iostream>


namespace mtm{

    /**SortedListNode template class.
     * All Template Requirements:
     *      A copy constructor.
     *      A destructor.
     *      An assignment operator.
     *      operator< .
    */

    template <class T>
    class SortedListNode
    {
        T value;
        SortedListNode<T> *next;

    public:

        /**
           * Constructor of class SortedListNode<T>.
           *
           * @param value - of type T.
           * @param next - pointer of the next SortedListNode<T>.
           *
           * Template Requirements:
           *    Copy constructor
           *
           */
        explicit SortedListNode(T value, SortedListNode<T>* next = nullptr);

        /**
           * Copy Constructor of class SortedListNode<T>.
           *
           * @param node - a SortedListNode<T> object to be copied to caller object.
           *
           * Template Requirements:
           *    Copy constructor
           *
           */
        SortedListNode(const SortedListNode<T> &node);

        /**
           * Destructor of class SortedListNode<T>.
           *
           * Template Requirements:
           *    Destructor
           *
           */
        ~SortedListNode();

        /**
            * operator= : Assignment Operator of class SortedListNode<T>.
            *
            * @param other - a SortedList<T> object to be copied to caller object.
            *
            * Template Requirements:
            *    Assignment operator
            *
            */
        SortedListNode& operator=(const SortedListNode<T>& other);

        /**
            * getNext : Returns a pointer to the next SortedListNode.
            *
            * @return
            *       A pointer to the next SortedListNode pointer of the caller object.
            *
            */
        SortedListNode* getNext() const;

        /**
            * setNext : Sets the next node of the caller node to the received node pointer.
            *
            */
        void setNext(SortedListNode *node);

        /**
            * getValue : Returns a reference to value of the caller object.
            *
            * @return
            *       A pointer to the next SortedListNode pointer of the caller object.
            *
            */
        const T& getValue() const;

        /**
            * setValue : Sets the value of the caller node to the received value of type T val.
            *
            * Template Requirements:
            *    Assignment operator
            *
            */
        void setValue(T &val);

        /**
            * operator== : Returns whether a received SortedListNode<T> object equals the caller object .
            *
            * @param to_compare - a SortedListNode<T> object to compare with *this
            * @return
            *      true - if both objects' values are equal, and they both have same follower Node
            *      false - otherwise.
            *
            * Template Requirements:
            *    operator< .
            *
            */
        bool operator==(SortedListNode<T> &to_compare);

        /**
            * copyRecursively : Returns a copy of all nodes from the caller SortedListNode to the end of its list.
            *
            * @return
            *      A pointer to a new Node which is a copy of the caller Node.
            *
            * Template Requirements:
            *    Assignment operator.
            *    Destructor.
            *
            */
        SortedListNode<T>* copyRecursively() const;

        /**
            * deleteRecursively : Deletes the received node and all its following nodes.
            *
            * Template Requirements:
            *    Destructor.
            *
            */
        static void deleteRecursively(SortedListNode<T>* node);
    };

    template <class T>
    SortedListNode<T>::SortedListNode(T value, SortedListNode *next) : value(value), next(next){}

    template <class T>
    SortedListNode<T>::SortedListNode(const SortedListNode<T> &node) : value(node.value), next(nullptr){}

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
        if (next){
            next = nullptr;
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
    bool SortedListNode<T>::operator==(SortedListNode<T> &to_compare) {
        return (!(value < to_compare.value) && !(to_compare.value < value) && next == to_compare.next);
    }

    template <class T>
    SortedListNode<T>* SortedListNode<T>::copyRecursively() const
    {
        SortedListNode<T>* to_return = new SortedListNode<T>(*this);
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
        return to_return;
    }

    template <class T>
    void SortedListNode<T>::deleteRecursively(SortedListNode<T>* node){
        while(node != nullptr){
            SortedListNode<T>* temp = node->getNext();
            delete node;
            node = temp;
        }
    }


}

#endif //GENERICTWLIST_TWLIST_NODE_H
