#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <cassert>
#include <stdexcept>
#include <string>
#include "SortedListNode.h"

namespace mtm {

    template<class T>
    class SortedList {
    private:
        SortedListNode<T> *head;
        int num_of_nodes = 0;

        SortedListNode<T> *getHead() const;

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
        SortedList::const_iterator begin() const {
            return const_iterator(this, 0);
        }

        /**SortedList::const_iterator end() const
        - returns const iterator pointing to "end" of sorted list.
        * requirements:
        - constructor for class const iterator
        */
        SortedList::const_iterator end() const {
            return const_iterator(this, this->length());
        }

        /**
             * const int length() const:
             * - returns number of elements in given SortedList.
             * Template Requirements: none
              */
        int length() const;


        void insert(const T &to_add);


        void remove(SortedList::const_iterator &iter);


        template<class Function>
        SortedList<T> filter(Function func) const;

        /**
         * //SortedList<T> apply(Function func) const:
         * - apply function that receives a parameter that is a function.
         * - function is applied to each element of the given sorted list.
         * - result is assigned to new sorted list.
         * Template Requirements:
         *  T assignment operator.
         *  ~T() destructor
         */
        template<class Function>
        SortedList<T> apply(Function func) const;
    };


    template<class T>
    class SortedList<T>::const_iterator {
        const SortedList *sorted_list;
        SortedListNode<T> *current_node;
        int index;

        /**iterator(const SortedList* sorted_list, int index):
    - constructor of const_iterator.
 */
        const_iterator(const SortedList *sorted_list, int index);

        friend class SortedList<T>;

        SortedListNode<T> *getNodePtr() { return current_node; };

    public:
        /**
//const_iterator(const const_iterator& const_it)=default//:
- copy constructor of const_iterator class- set to default.
*/
        const_iterator(const const_iterator &const_it) = default;

        /**
//~const_iterator()=default//:
- destructor of const_iterator class.
*/
        ~const_iterator() = default;

        /**
//T& operator*() const//:
-returns element iterator is pointing at as const.
- const_iterator remains unchanged.
*/
        const T &operator*() const;

        /**
//const_iterator& operator=(const_iterator& iterator)=default//:
-assignment operator.
- receives const_iterator reference parameter.
- set to be default, return const_iterator by reference.
*/
        const_iterator &operator=(const const_iterator &iterator) = default;

        /**
        //const_iterator& operator++()//:
        -prefix ++ operator.
        - returns const_iterator pointing to next element in sorted_list.
     */
        const_iterator &operator++();

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
        bool operator==(const const_iterator &iterator) const;
    };


    //implementation of SortedList class functions//
    template<class T>
    SortedList<T>::SortedList() : head(nullptr) {}

    template<class T>
    SortedList<T>::~SortedList() {
        // std::cout << "List size before: " << this->length() << std::endl;
        // std::cout << "emptying list" << std::endl;
        emptyList();
        delete (head);
        // std::cout << "List size after: " << this->length() << std::endl;
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList &other) : head(nullptr), num_of_nodes(0) {
        if (&other == nullptr) {
            return;
        }
        for (auto iter = other.begin(); !(iter == other.end()); iter++) {
            this->insert(*iter);
        }
    }

    template<class T>
    SortedListNode<T> *SortedList<T>::getHead() const {
        if (num_of_nodes == 0)
            return nullptr;
        return head;
    }



    template<class T>
    void SortedList<T>::emptyList() {
        SortedList<T>::const_iterator it = begin();
        while (!(it == end())) {
            remove(it);
            SortedList<T>::const_iterator temp = begin();
            it = temp;
        }
        delete(head);
        head = nullptr;
    }


    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        SortedListNode<T>* new_head = list.head->copyRecursively();
        head->deleteRecursively(head);
        head = new_head;
        num_of_nodes = list.num_of_nodes;
        return *this;
    }


    template<class T>
    int SortedList<T>::length() const {
        return this->num_of_nodes;
    }


    template<class T>
    void SortedList<T>::insert(const T &to_add) {
        auto new_node = new SortedListNode<T>(to_add, nullptr);
        if (!new_node) {
            throw std::bad_alloc();
        }
        if (num_of_nodes == 0) {
            head = new_node;
        } else if (head->getValue()>to_add){
            new_node->setNext(head);
            head=new_node;
        }
        else{
            SortedListNode<T> *antecedent = head;
            while (antecedent && antecedent->getValue() < to_add) {
                if(antecedent->getNext() == nullptr || antecedent->getNext()->getValue()>to_add) {
                    break;
                }
                antecedent = antecedent->getNext();
            }
            new_node->setNext(antecedent->getNext());
            antecedent->setNext(new_node);
        }
        num_of_nodes++;
    }


    template<class T>
    void SortedList<T>::remove(SortedList::const_iterator &iter) {
        if (&iter == nullptr || num_of_nodes == 0) {
            return;
        }
        if(iter == end()){
            return;
        }
        if (iter == begin()) {
            head = head->getNext();
        } else {
            SortedListNode<T>* previous = head;
            while(!(previous->getNext() == iter.getNodePtr())){
                previous = previous->getNext();
            }
            previous->setNext(iter.getNodePtr()->getNext());
        }
        delete (iter.getNodePtr());
        num_of_nodes--;
    }


    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::filter(Function func) const {
        SortedList<T> result;
        for (auto iter = begin(); !(iter == end()); iter++) {
            if (func(*iter)) {
                result.insert(*iter);
            }
        }
        return result;
    }


    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::apply(Function func) const {
        SortedList<T> result = SortedList<T>();
        for (auto iter = begin(); !(iter == end()); ++iter) {
            result.insert(func(*iter));
        }
        return result;
    }


    template<class T>
    std::ostream &operator<<(std::ostream &os, SortedList<T> &to_print) {
        os << to_print.printList();
        return os;
    }


/**
             // std::ostream& operator<<(std::ostream &os, const SortedList<T>& SortedList)//:
              output operator for SortedList<T>
              * Template Requirements:
              * - T copy constructor.
              * - T() destructor.
              * - operator output for T << .
              */
    template<class T>
    std::ostream &operator<<(std::ostream &os, const SortedList<T> &twList) {
        return printList(os, twList.begin(), twList.end());
    }


    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList *sorted_list, int index): sorted_list(sorted_list),
                                                                                             index(index) {
        if (index < 0 || index > sorted_list->length()) {
            throw std::out_of_range("Iterator is Illegal");
        }
        SortedListNode<T> *it = sorted_list->getHead();
        for (int i = 0; i < index; i++) {
            it = it->getNext();
        }
        current_node = it;
    }


    // operator *
    template<class T>
    const T &SortedList<T>::const_iterator::operator*() const {
        return current_node->getValue();
    }


    // operator==
    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator &iterator) const {
        assert(sorted_list == iterator.sorted_list);
        return (index == iterator.index);
    }


    // operator ++i
    template<class T>
    typename SortedList<T>::const_iterator &SortedList<T>::const_iterator::operator++() {
        ++index;
        current_node = current_node->getNext();
        return *this;
    }

    //operator i++
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int) {
        const_iterator result = *this;
        ++(*this);
        return result;
    }

    template<class T>
    void printList(const SortedList<T> &list) {
        for (auto iter = list.begin(); !(iter == list.end()); iter++) {
            std::cout << *iter << std::endl;
        }
        std::cout << std::endl;
    }
}




#endif //PARTB_PARTB_H
