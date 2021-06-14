#ifndef TW_LIST_NO_ITER_HPP
#define TW_LIST_NO_ITER_HPP
#include <assert.h>
#include <string>
#include "two_way_list_node.hpp"

//#define BIGGER '>'
//#define SMALLER '<'
//#define EQUAL '='
//#define NOT_EQUAL '!'
//#define BIG_EQUAL '#'
//#define SMALL_EQUAL '%'

typedef enum twListResult_t
{
    TW_LIST_OUT_OF_MEMORY = -2,
    TW_LIST_INVALID_INPUT = -3,
    TW_LIST_SUCCESS = 0,
    TW_LIST_FAILURE = -1
} twListResult_t;

template <class T>
class twList
{
private:
    twListNode<T> *head;
    twListNode<T> *tail;
    int num_of_nodes = 0;
    int key;

public:
    twList<T>(int key);
    twList<T>();

    /**
         * //twList<T>(const twList<T> &twList)//:
         * - twList<T> copy constructor
         *
         * Template Requirements:
          * - T() constructor with no parameters.
          * - assignment operator.
          * -~T() destructor
          */
    twList<T>(const twList<T> &twList);

    /**
         * //~twList()//:
         * - twList destructor.
         *
         * Template Requirements:
         * T destructor
          */
    ~twList();

    /**
         * //twList<T> &operator=(const twList<T> &twList)//:
         * - twList<T> assignment operator
         *
         * Template Requirements:
          * - T() constructor with no parameters.
          *  T assignment operator.
          *  ~T() destructor
          */
    twList<T> &operator=(const twList<T> &twList);

    /**
         * //const int size() constt//:
         * - returns number of elements in given twList.
         * Template Requirements: none
          */
    const int size() const;

    twListNode<T> *getHead()
    {
        if (num_of_nodes == 0)
            return NULL;
        return head;
    };

    twListNode<T> *getTail()
    {
        if (num_of_nodes == 0)
            return NULL;
        return tail;
    };

    const int getKey() { return this->key; }
    void setKey(int new_key) { this->key = new_key; }

    twListResult_t addFirst(const T &to_add);

    twListResult_t addLast(const T &to_add);

    //    twListResult_t addFirst(twListNode<T> &to_add);
    //
    //    twListResult_t addLast(twListNode<T>& to_add);

    twListResult_t remove(twListNode<T> *to_remove);

    twList<T> clone();

    twListNode<T> *contains(const T &element);
    twListNode<T> *contains(const int key);

    std::string printList();
    /** //logical operator comparison functions://
    //twList<bool> operator(T to_compare)//:
    - recieves paramter to compare with twList (T).
    - returns twList in which each element is the result of the logical comparison (1 if true 0 if false).
    - dimensions of twList are dimensions of the compared twList (of *this twList).
    - twList is returned by value.
    * Template Requirements:
         *  T() constructor with no parameters.
         *  T assignment operator (=).
         *  ~T(): destructor.
         * T copy constructor
         *  T operator of logical comparison (matching operator for every function):
         * (==,!=,<=,>=,<,>)
    */
    bool operator==(const twList<T> &twList);
    bool operator!=(const twList<T> &twList);
    bool operator<=(const twList<T> &twList);
    bool operator>=(const twList<T> &twList);
    bool operator<(const twList<T> &twList);
    bool operator>(const twList<T> &twList);

    void emptyList();
};

//implementation of twList class functions//
template <class T>
twList<T>::twList() : head(nullptr), tail(nullptr)
{
    twListNode<T> *make_head = new twListNode<T>();
    twListNode<T> *make_tail = new twListNode<T>();
    head = make_head;
    tail = make_tail;
    head->setNext(tail);
    tail->setPrev(head);
}

template <class T>
twList<T>::twList(int key) : head(nullptr), tail(nullptr), key(key)
{
    twListNode<T> *make_head = new twListNode<T>();
    twListNode<T> *make_tail = new twListNode<T>();
    head = make_head;
    tail = make_tail;
    head->setNext(tail);
    tail->setPrev(head);
}

template <class T>
twList<T>::twList(const twList &tw_list) : head(tw_list.head.clone()), tail(tw_list.tail.clone()), num_of_nodes(tw_list.num_of_nodes)
{
    twListNode<T> *iter = tw_list.getHead();
    while (num_of_nodes && iter != tw_list.getTail())
    {
        iter = (*iter).getNext();
        twListNode<T> *new_node = new twListNode<T>;
        new_node = (*iter).clone();
        addLast(new_node);
    }
    this->key = tw_list.key;
}

template <class T>
twListNode<T> *twList<T>::contains(const T &element)
{
    twListNode<T> *iter = this->getHead();
    while (iter != this->getTail())
    {
        if (iter->getValue() == element)
            return iter;
        iter = iter->getNext();
    }
    return nullptr;
}

template <class T>
twListNode<T> *twList<T>::contains(const int key)
{
    twListNode<T> *iter = this->getHead();
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
twList<T>::~twList()
{
    // std::cout << "List size before: " << this->size() << std::endl;
    // std::cout << "emptying list" << std::endl;
    twListNode<T> *from = head;
    while ((*from).getNext() != tail)
    {
        twListNode<T> *curr = from->getNext();
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
void twList<T>::emptyList()
{
    // std::cout << "emptying list" << std::endl;
    twListNode<T> *from = head;
    while ((*from).getNext() != tail)
    {
        twListNode<T> *curr = from->getNext();
        if (curr && curr->getValue())
            delete curr->getValue();
        from = from->getNext();
    }
}


template <class T>
twList<T> &twList<T>::operator=(const twList<T> &twList_t)
{
    if (this == &twList_t)
    {
        return *this;
    }
    twListNode<T> *from = head, to = tail;
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
        twListNode<T> *temp = new twListNode<T>;
        temp = (*from).clone();
        addLast(temp);
        from = (*from).getNext();
    }
    this->key = twList_t.key;

    return *this;
}

/*    template <class T>
    twList<bool> twList<T>::operator==(T to_compare) {
//        return compareMatrix(*this, to_compare, EQUAL);
//    }
//
//    template <class T>
//    twList<bool> twList<T>::operator!=(T to_compare) {
//        return compareMatrix(*this, to_compare, NOT_EQUAL);
//    }
//
//    template <class T>
//    twList<bool> twList<T>::operator<=(T to_compare) {
//        return compareMatrix(*this, to_compare, SMALL_EQUAL);
//    }
//
//    template <class T>
//    twList<bool> twList<T>::operator>=(T to_compare) {
//        return compareMatrix(*this, to_compare, BIG_EQUAL);
//    }
//
//    template <class T>
//    twList<bool> twList<T>::operator<(T to_compare) {
//        return compareMatrix(*this, to_compare, SMALLER);
//    }
//
//    template <class T>
//    twList<bool> twList<T>::operator>(T to_compare) {
//        return compareMatrix(*this, to_compare, BIGGER);
   }
*/
template <class T>
const int twList<T>::size() const
{
    return this->num_of_nodes;
}

/*   template <class T>
/  twListResult_t twList<T>::addFirst(twListNode<T>& to_add){
       if (!this){
           return TW_LIST_FAILURE;
       }
       twListNode<T>* curr_first=head->getNext();
       to_add.setPrev(head);
       to_add.setNext(head);
       twListNode<T>* new_first=&to_add;
       head->setNext(curr_first);
       (*curr_first).setPrev(new_first);
       num_of_nodes++;
       return TW_LIST_SUCCESS;
   }*/

template <class T>
twListResult_t twList<T>::addFirst(const T &to_add)
{
    // std::cout << "trying to add first to list " << std::endl;
    if (!this)
        return TW_LIST_FAILURE;

    twListNode<T> *curr_first = head->getNext();
    twListNode<T> *new_node = new twListNode<T>(to_add, head, curr_first);
    if (!new_node)
    {
        return TW_LIST_OUT_OF_MEMORY;
    }
    head->setNext(new_node);
    (*curr_first).setPrev(new_node);
    num_of_nodes++;
    // std::cout << num_of_nodes << std::endl;
    return TW_LIST_SUCCESS;
}

/* template <class T>
    twListResult_t twList<T>::addLast(twListNode<T>& to_add){
        if (!this){
            return TW_LIST_FAILURE;
        }
        twListNode<T>* curr_last=tail->getPrev();
        twListNode<T> list_node(to_add.getVal(), curr_last, tail);
        twListNode<T>* new_last=&list_node;
        tail->setPrev(new_last);
        (*curr_last).setNext(new_last);
        num_of_nodes++;
        return TW_LIST_SUCCESS;
}*/

template <class T>
twListResult_t twList<T>::addLast(const T &to_add)
{
    if (!this)
    {
        return TW_LIST_FAILURE;
    }
    twListNode<T> *curr_last = tail->getPrev();
    twListNode<T> *new_node = new twListNode<T>(to_add, curr_last, tail);
    if (!new_node)
    {
        return TW_LIST_OUT_OF_MEMORY;
    }
    tail->setPrev(new_node);
    (*curr_last).setNext(new_node);
    num_of_nodes++;
    return TW_LIST_SUCCESS;
}

template <class T>
twListResult_t twList<T>::remove(twListNode<T> *to_remove)
{
    if (!this)
    {
        return TW_LIST_FAILURE;
    }
    if (!to_remove)
    {
        return TW_LIST_INVALID_INPUT;
    }
    twListNode<T> *curr_prev = to_remove->getPrev();
    twListNode<T> *curr_next = to_remove->getNext();
    curr_prev->setNext(curr_next);
    curr_next->setPrev(curr_prev);
    delete to_remove;
    num_of_nodes--;
    return TW_LIST_SUCCESS;
}

template <class T>
std::ostream &operator<<(std::ostream &os, twList<T> &to_print)
{
    os << to_print.printList();
    return os;
}
template <class T>
std::string twList<T>::printList()
{
    std::string list_str;
    twListNode<T> *it = head;
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
             // std::ostream& operator<<(std::ostream &os, const twList<T>& twList)//:
              output operator for twList<T>
              * Template Requirements:
              * - T copy constructor.
              * - T() destructor.
              * - operator output for T << .
              */
template <class T>
std::ostream &operator<<(std::ostream &os, const twList<T> &twList)
{
    return printList(os, twList.begin(), twList.end());
}

template <class T>
bool twList<T>::operator<(const twList<T> &twList)
{
    return (this->key < twList.key);
}

template <class T>
bool twList<T>::operator>(const twList<T> &twList)
{
    return (this->key > twList.key);
}

template <class T>
bool twList<T>::operator==(const twList<T> &twList)
{
    return (this->key == twList.key);
}

template <class T>
bool twList<T>::operator!=(const twList<T> &twList)
{
    return (this->key != twList.key);
}

template <class T>
bool twList<T>::operator<=(const twList<T> &twList)
{
    return (this->key <= twList.key);
}

template <class T>
bool twList<T>::operator>=(const twList<T> &twList)
{
    return (this->key >= twList.key);
}

#endif //PARTB_PARTB_H
