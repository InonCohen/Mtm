#ifndef TW_LIST_NO_ITER_HPP
#define TW_LIST_NO_ITER_HPP
#include <assert.h>
#include <stdexcept>
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
        SortedListNode<T> *getHead() const;
        SortedListNode<T> *getTail() const;
        void emptyList();
    public:
        class const_iterator;
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
        SortedList<T> &operator=(const SortedList<T> &list);

        /** SortedList::const_iterator begin() const
            - returns const iterator pointing to first element of SortedList.
            - element remains unchanged since this parameter is const.
            * requirements:
            - constructor for class const iterator
            */
        SortedList::const_iterator begin() const{
            return const_iterator(this,0);
        }

        /**SortedList::const_iterator end() const
        - returns const iterator pointing to "end" of sorted list.
        * requirements:
        - constructor for class const iterator
        */

        SortedList::const_iterator end() const{
            return const_iterator(this,this->size());
        }

        /**
             * //const int size() constt//:
             * - returns number of elements in given SortedList.
             * Template Requirements: none
              */
        const int size() const;

        const int getKey() { return this->key; }
        void setKey(int new_key) { this->key = new_key; }

        void insert(const T &to_add);

        void remove(SortedList::const_iterator& iter);

        SortedList<T> clone();

        SortedListNode<T> *contains(const T &element);
        SortedListNode<T> *contains(const int key);

        std::string printList();
    };

    template <class T>
    class SortedList<T>:: const_iterator{
        const SortedList* sorted_list;
        int index;
        /**iterator(const SortedList* sorted_list, int index):
    - constructor of const_iterator.
 */
        const_iterator(const SortedList* sorted_list, int index): sorted_list(sorted_list), index(index){};
        friend class SortedList<T>;
    public:
        /**
    //~const_iterator()=default//:
    - destructor of const_iterator class.
 */
        ~const_iterator()=default;
        /**
       //T& operator*() const//:
       -returns element iterator is pointing at as const.
       - const_iterator remains unchanged.
    */
        const T& operator*() const;
        /**
        //const_iterator(const const_iterator& const_it)=default//:
        - copy constructor of const_iterator class- set to default.
     */
        const_iterator(const const_iterator& const_it)=default;
        /**
        //const_iterator& operator=(const_iterator& iterator)=default//:
        -assignment operator.
        - recieves const_iterator reference parameter.
        - set to be default, return const_iterator by reference.
     */
        const_iterator& operator=(const_iterator& iterator)=default;
        /**
        //const_iterator& operator++()//:
        -prefix ++ operator.
        - returns const_iterator pointing to next element in sorted_list.
     */
        const_iterator& operator++();
        /**
        //const_iterator operator++(int)//:
        -postfix ++ operator
        -advances const_iterators index by 1.
        - returns original const_iterator (*this) by value
     */
        const_iterator operator++(int);
        /**
        //bool operator==(const const_iterator& iterator) const//:
        - compares two const iterators.
        - returns true if they are pointing at same element (by index)
        - otherwise returns false.
     */
        bool operator==(const const_iterator& iterator) const;
        /**
        //bool operator!=(const const_iterator& iterator) const//:
        - compares two const iterators.
        - returns false if they are pointing at same element (by index)
        - otherwise returns true.
     */
        bool operator!=(const const_iterator it) const;
    };



    //implementation of SortedList class functions//
    template <class T>
    SortedList<T>::SortedList() : head(nullptr), tail(nullptr){}

    template <class T>
    SortedList<T>::~SortedList()
    {
        // std::cout << "List size before: " << this->size() << std::endl;
        // std::cout << "emptying list" << std::endl;
        emptyList();
        delete (tail);
        delete (head);
        // std::cout << "List size after: " << this->size() << std::endl;
    }

    template <class T>
    SortedList<T>::SortedList(const SortedList &other) : head(nullptr), tail(nullptr), num_of_nodes(0)
    {
        if(&other == nullptr){
            return;
        }
        SortedList<T>* new_list = new SortedList<T>();
        if(!new_list){
            throw std::bad_alloc();
        }
        for(auto iter = other.begin() ; !(iter == other.end()) ; iter++){
                (*new_list).insert(*iter);
        }
        this->emptyList();
        *this = *new_list;

    }

    template <class T>
    SortedListNode<T>* SortedList<T>::getHead() const
    {
        if (num_of_nodes == 0)
            return nullptr;
        return head;
    }

    template <class T>
    SortedListNode<T>* SortedList<T>::getTail() const
    {
        if (num_of_nodes == 0)
            return nullptr;
        return tail;
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
    void SortedList<T>::emptyList() {
        for (auto it = this->begin(); !(it == this->end());) {
            this->remove(it);
        }
        head = nullptr;
        tail = nullptr;
    }


    template <class T>
    SortedList<T>& SortedList<T>::operator=(const SortedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        SortedList<T>* new_list = new SortedList<T>();
        if(!new_list){
            throw std::bad_alloc();
        }
        for (auto it = list.begin(); !(it == list.end()); ++it){
            (*new_list).insert(*it);
            }
        head = list.head;
        tail = list.tail;
        num_of_nodes = list.num_of_nodes;
        return *new_list;
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
    void SortedList<T>::remove(SortedList::const_iterator& iter)
    {
        if (!this)
        {
            return;
        }
        if (&iter == nullptr)
        {
            return;
        }
        if(num_of_nodes == 0){
            return;
        }
        const T& value_to_remove = *iter;
        SortedListNode<T>* to_remove = head;
        while(to_remove->getValue() < value_to_remove){
            to_remove = (*to_remove).getNext();
        }
        if(to_remove == head){
            head = head->getNext();
            if (head){
                head->setPrev(nullptr);
            }
        }
        else if(to_remove == tail){
            tail = tail->getPrev();
            if(tail){
                tail->setNext(nullptr);
            }
        }
        else{
            SortedListNode<T> *curr_prev = to_remove->getPrev();
            SortedListNode<T> *curr_next = to_remove->getNext();
            curr_prev->setNext(curr_next);
            curr_next->setPrev(curr_prev);
        }
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

//    template <class T>
//    bool SortedList<T>::operator<(const SortedList<T> &twList) const
//    {
//        return (this->key < twList.key);
//    }
//
//    template <class T>
//    bool SortedList<T>::operator>(const SortedList<T> &twList) const
//    {
//        return (this->key > twList.key);
//    }
//
//    template <class T>
//    bool SortedList<T>::operator==(const SortedList<T> &twList) const
//    {
//        return (this->key == twList.key);
//    }
//
//    template <class T>
//    bool SortedList<T>::operator!=(const SortedList<T> &twList) const
//    {
//        return (this->key != twList.key);
//    }
//
//    template <class T>
//    bool SortedList<T>::operator<=(const SortedList<T> &twList) const
//    {
//        return (this->key <= twList.key);
//    }
//
//    template <class T>
//    bool SortedList<T>::operator>=(const SortedList<T> &twList) const
//    {
//        return (this->key >= twList.key);
//    }


    // operator *
    template <class T>
    const T& SortedList<T>::const_iterator::operator*() const {
        if(index < 0 || index >= sorted_list->size()) {
            throw std::out_of_range("Iterator is Illegal");
        }
        SortedListNode<T>* current = sorted_list->getHead();
        for(int i=0;i<index;i++){
            current = (*current).getNext();
        }
        return (*current).getValue();
    }


    // operator==
    template <class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator& iterator) const {
        assert(sorted_list== iterator.sorted_list);
        return (index == iterator.index);
    }

    // operator!=
    template <class T>
    bool SortedList<T>::const_iterator::operator!=(const const_iterator it) const {
        return !(*this == it);
    }

    // operator ++i
    template <class T>
    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++(){
        ++index;
        return *this;
    }

    //operator i++
    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int){
        const_iterator result = *this;
        ++*this;
        return result;
    }
}





#endif //PARTB_PARTB_H
