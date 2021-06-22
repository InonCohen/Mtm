#ifndef TW_LIST_NO_ITER_HPP
#define TW_LIST_NO_ITER_HPP
#include <assert.h>
#include <string>
#include "SortedListNode.h"

//#define BIGGER '>'
//#define SMALLER '<'
//#define EQUAL '='
//#define NOT_EQUAL '!'
//#define BIG_EQUAL '#'
//#define SMALL_EQUAL '%'

namespace mtm{
    typedef enum
    {
        TW_LIST_OUT_OF_MEMORY = -2,
        TW_LIST_INVALID_INPUT = -3,
        TW_LIST_SUCCESS = 0,
        TW_LIST_FAILURE = -1
    } SortedListResult;

    template <class T>
    class SortedList
    {
    private:
        SortedListNode<T> *head;
        SortedListNode<T> *tail;
        int num_of_nodes = 0;
        int key;

    public:
        SortedList<T>();

        /**
     * //~SortedList()//:
     * - SortedList destructor.
     *
     * Template Requirements:
     * T destructor
      */
        ~SortedList();

        /**
             * //SortedList<T>(const SortedList<T> &SortedList)//:
             * - SortedList<T> copy constructor
             *
             * Template Requirements:
              * -~T() destructor
              */
        SortedList<T>(const SortedList<T> &other);



        /**
             * //SortedList<T> &operator=(const SortedList<T> &SortedList)//:
             * - SortedList<T> assignment operator
             *
             * Template Requirements:
              * - T() constructor with no parameters.
              *  T assignment operator.
              *  ~T() destructor
              */
        SortedList<T> &operator=(const SortedList<T> &twList);

        /**
             * //const int size() constt//:
             * - returns number of elements in given SortedList.
             * Template Requirements: none
              */
        const int size() const;

        SortedListNode<T> *getHead()
        {
            if (num_of_nodes == 0)
                return NULL;
            return head;
        };

        SortedListNode<T> *getTail()
        {
            if (num_of_nodes == 0)
                return NULL;
            return tail;
        };

        const int getKey() { return this->key; }
        void setKey(int new_key) { this->key = new_key; }

        void insert(const T &to_add);

        void remove(SortedListNode<T> *to_remove);

        SortedList<T> clone();

        SortedListNode<T> *contains(const T &element);
        SortedListNode<T> *contains(const int key);

        std::string printList();
        /** //logical operator comparison functions://
        //SortedList<bool> operator(T to_compare)//:
        - recieves paramter to compare with SortedList (T).
        - returns SortedList in which each element is the result of the logical comparison (1 if true 0 if false).
        - dimensions of SortedList are dimensions of the compared SortedList (of *this SortedList).
        - SortedList is returned by value.
        * Template Requirements:
             *  T() constructor with no parameters.
             *  T assignment operator (=).
             *  ~T(): destructor.
             * T copy constructor
             *  T operator of logical comparison (matching operator for every function):
             * (==,!=,<=,>=,<,>)
        */
        bool operator==(const SortedList<T> &twList) const;
        bool operator!=(const SortedList<T> &twList) const;
        bool operator<=(const SortedList<T> &twList) const;
        bool operator>=(const SortedList<T> &twList) const;
        bool operator<(const SortedList<T> &twList) const;
        bool operator>(const SortedList<T> &twList) const;

        void emptyList();
    };

    //implementation of SortedList class functions//
    template <class T>
    SortedList<T>::SortedList() : head(nullptr), tail(nullptr){}

    template <class T>
    SortedList<T>::~SortedList()
    {
        // std::cout << "List size before: " << this->size() << std::endl;
        // std::cout << "emptying list" << std::endl;
        SortedListNode<T>* from = head;
        while (from != nullptr && (*from).getNext() != tail)
        {
            SortedListNode<T>* curr = from->getNext();
            from->setNext(curr->getNext());
            from->getNext()->setPrev(from);
            delete curr;
            this->num_of_nodes--;
        }
        delete (tail);
        delete (head);
        // std::cout << "List size after: " << this->size() << std::endl;
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList &other) : head(nullptr), tail(nullptr), num_of_nodes(other.num_of_nodes)
    {
        SortedListNode<T> *iter = other.getHead();
        SortedList<T> new_list = new SortedList<T>();
        if(!new_list){
            throw std::bad_alloc();
        }
        while (num_of_nodes && iter != other.getTail())
        {
            new_list.insert(iter->getValue());
            iter=iter->getNext();
        }
        this = new_list;
    }

    template <class T>
    SortedListNode<T> *SortedList<T>::contains(const T &element)
    {
        SortedListNode<T> *iter = this->getHead();
        while (iter != this->getTail())
        {
            if (iter->getValue() == element)
                return iter;
            iter = iter->getNext();
        }
        return nullptr;
    }

    template <class T>
    SortedListNode<T> *SortedList<T>::contains(const int key)
    {
        SortedListNode<T> *iter = this->getHead();
        while (iter != this->getTail())
        {
            if (iter->getValue())
                if (iter->getValue()->getKey() == key)
                    return iter;
            iter = iter->getNext();
        }
        return nullptr;
    }



    template <class T>
    void SortedList<T>::emptyList()
    {
        // std::cout << "emptying list" << std::endl;
        SortedListNode<T> *from = head;
        while ((*from).getNext() != tail)
        {
            SortedListNode<T> *curr = from->getNext();
            if (curr && curr->getValue())
                delete curr->getValue();
            from = from->getNext();
        }
    }


    template <class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &twList_t)
    {
        if (this == &twList_t)
        {
            return *this;
        }
        SortedListNode<T> *from = head, to = tail;
        while (from != to - 1)
        {
            from = (*from).getNext();
            delete (*from).getPrev();
        }
        delete from;
        head = twList_t.head.clone();
        tail = twList_t.tail.clone();
        from = twList_t.head;
        from = (*from).getNext();
        to = twList_t.tail;
        while (from != to)
        {
            SortedListNode<T> *temp = new SortedListNode<T>;
            temp = (*from).clone();
            addLast(temp);
            from = (*from).getNext();
        }
        this->key = twList_t.key;

        return *this;
    }

    template <class T>
    const int SortedList<T>::size() const
    {
        return this->num_of_nodes;
    }




    template <class T>
    void SortedList<T>::insert(const T &to_add)
    {
        SortedListNode<T> *new_node = new SortedListNode<T>(to_add, nullptr, nullptr);
        if(!new_node){
            throw std::bad_alloc();
        }
        if(num_of_nodes == 0){
            head = new_node;
            tail = new_node;
        }
        else if (head == tail){
            if(head->getValue()<to_add){
                new_node->setPrev(head);
                tail=new_node;
                head->setNext(tail);
            }
            else{
                new_node->setNext(tail);
                head=new_node;
                tail->setPrev(head);
            }
        }
        else{
            SortedListNode<T> *antecedent = tail;
            while(antecedent&&antecedent->getValue() >= to_add){
                antecedent=antecedent->getPrev();
            }
            SortedListNode<T> *follower = antecedent? antecedent->getNext(): head;
            if(antecedent != nullptr){
                new_node->setPrev(antecedent);
                antecedent->setNext(new_node);
            }
            if(follower != nullptr){
                new_node->setNext(follower);
                follower->setPrev(new_node);
            }
            if(antecedent == tail){
                tail=new_node;
            }
            if(follower == head){
                head = new_node;
            }
        }
        num_of_nodes++;
    }


    template <class T>
    void SortedList<T>::remove(SortedListNode<T> *to_remove)
    {
        if (!this)
        {
            return;
        }
        if (!to_remove)
        {
            return;
        }
        SortedListNode<T> *curr_prev = to_remove->getPrev();
        SortedListNode<T> *curr_next = to_remove->getNext();
        curr_prev->setNext(curr_next);
        curr_next->setPrev(curr_prev);
        delete to_remove;
        num_of_nodes--;
    }

    template <class T>
    std::ostream &operator<<(std::ostream &os, SortedList<T> &to_print)
    {
        os << to_print.printList();
        return os;
    }
    template <class T>
    std::string SortedList<T>::printList()
    {
        std::string list_str;
        SortedListNode<T> *it = head;
        for (int i = 0; i < num_of_nodes; i++)
        {
            it = (*it).getNext();
            list_str += std::to_string((*it).getValue());
            if (i != num_of_nodes - 1)
            {
                list_str += " - ";
            }
        }
        return list_str;
    }

/**
             // std::ostream& operator<<(std::ostream &os, const SortedList<T>& SortedList)//:
              output operator for SortedList<T>
              * Template Requirements:
              * - T copy constructor.
              * - T() destructor.
              * - operator output for T << .
              */
    template <class T>
    std::ostream &operator<<(std::ostream &os, const SortedList<T> &twList)
    {
        return printList(os, twList.begin(), twList.end());
    }

    template <class T>
    bool SortedList<T>::operator<(const SortedList<T> &twList) const
    {
        return (this->key < twList.key);
    }

    template <class T>
    bool SortedList<T>::operator>(const SortedList<T> &twList) const
    {
        return (this->key > twList.key);
    }

    template <class T>
    bool SortedList<T>::operator==(const SortedList<T> &twList) const
    {
        return (this->key == twList.key);
    }

    template <class T>
    bool SortedList<T>::operator!=(const SortedList<T> &twList) const
    {
        return (this->key != twList.key);
    }

    template <class T>
    bool SortedList<T>::operator<=(const SortedList<T> &twList) const
    {
        return (this->key <= twList.key);
    }

    template <class T>
    bool SortedList<T>::operator>=(const SortedList<T> &twList) const
    {
        return (this->key >= twList.key);
    }
}





#endif //PARTB_PARTB_H
