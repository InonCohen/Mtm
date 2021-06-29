#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include <cassert>
#include <stdexcept>
#include <string>
#include "SortedListNode.h"

namespace mtm {

    /**SortedListNode template class.
         * Create a sorted container of any type.
         *
         * Template Requirements:
         *      A copy constructor.
         *      A destructor.
         *      An assignment operator.
         *      operator< .
        */

    template<class T>
    class SortedList {
    private:
        SortedListNode<T>* head;
        int num_of_nodes;

        SortedListNode<T> *getHead() const;

    public:
        class const_iterator;


                //Declaration of SortedList template class methods//

        /**
           * Constructor of class SortedList<T>.
           */
        SortedList<T>();

        /**
           * Destructor of class SortedList<T>.
           *
           * Template Requirements (derived from SortedListNode<T> template requirements):
           *    Destructor
           */
        ~SortedList();

        /**
           * Copy Constructor of class SortedList<T>.
           *
           * @param other - a SortedList<T> object to be copied to caller object.
           *
           * Template Requirements (derived from SortedListNode<T> template requirements):
           *    Copy constructor
           */
        SortedList<T>(const SortedList<T> &other);

        /**
            * operator= : Assignment Operator of class SortedList<T>.
            *
            * @param list - a SortedList<T> object to be copied to caller object.
            *
            * Template Requirements (derived from SortedListNode<T> template requirements):
            *    Assignment operator
            *    Destructor
            */
        SortedList<T> &operator=(const SortedList<T> &list);

        /**
            * begin: Returns a const_iterator to the first node in the list.
            *
            * @return
            *   const_iterator object pointing to first element of SortedList.
            */
        SortedList::const_iterator begin() const;


        /**
            * end: Returns a const_iterator to the end of the list (nullptr).
            *
            * @return
            *   const_iterator object pointing to next of the last node of SortedList.
            */
        SortedList::const_iterator end() const;

        /**
            * length: Returns the number of nodes in the list.
            *
            * @return
            *   Non-negative integer indicating how many nodes are there in the caller SortedList object .
            */
        int length() const;

        /**
            * insert: Adds a new node to the list, while maintaining ascending order of nodes.
            *
            * @param to_add - a T element to be inserted to the list
            *
            *  * Template Requirements (derived from SortedListNode<T> template requirements):
            *    Assignment operator
            *    operator<
            */
        void insert(const T &to_add);

        /**
            * remove: Deletes a node from the caller list.
            *
            * @param iter - a const_iterator pointing to the node which is to be deleted.
            *
            *    Template Requirements (derived from SortedListNode<T> template requirements):
            *    Destructor
            */
        void remove(const const_iterator &iter);


        /**
            * filter:  Returns a new SortedList object which consists elements that meet a certain criteria.
            *
            * @param func - a Function object the gets T and returns a boolean type answer (true/false).
            *
            * @return
            *      A SortedList object that contains all the elements that returned 'true' when being ent to func.
            *
            *  Template Requirements (derived from SortedListNode<T> template requirements):
            *  T assignment operator.
            */
        template<class Function>
        SortedList<T> filter(Function func) const;

        /**
         * apply:  Returns a new SortedList object which consists elements that are the result of
         *          received function after it is applied to each element of the given sorted list.
         *
         * @param func - a Function object the gets T and returns T.
         *
         * @return
         *      A SortedList object that contains all the return values of received function after it
         *      gets all caller function elements.
         *
         *  Template Requirements (derived from SortedListNode<T> template requirements):
         *  T assignment operator.
         *  ~T() destructor
         */
        template<class Function>
        SortedList<T> apply(Function func) const;

        //End of SortedList template class methods declaration//
    };


    /**const_iterator template class.
     * Create a constant iterator of a SortedList.
     *
     * Template Requirements:
     *      A copy constructor.
     *      A destructor.
    */
    template<class T>
    class SortedList<T>::const_iterator {
        const SortedList *sorted_list;
        SortedListNode<T> *current_node;
        int index;


        friend class SortedList<T>;

        //Declaration of const_iterator template class methods//

        /**
            * Constructor of class const_iterator<T>.
            *
            * @param sorted_list - the list to which the iterator points
            * @param index - the node number in the list, starting with 0.
            *
            * @return
            *       const_iterator pointing to the 'indexth' node in the list.
            */
        const_iterator(const SortedList *sorted_list, int index);

        /**
            * getNodePtr : Returns a pointer to the SortedListNode on which the caller const_iterator points.
            *
            * @return
            *       A pointer to the SortedListNode pointer of the caller object.
            */
        SortedListNode<T> *getNodePtr() { return current_node; };

        /**
            * getNodePtr : Returns a const pointer to the SortedListNode on which the caller const_iterator points.
            *
            * @return
            *       A const pointer to the SortedListNode pointer of the caller object.
            */
        const SortedListNode<T> *getNodePtr() const { return current_node; };

    public:

    /**
       * Copy Constructor of class const_iterator<T>.
       *
       * @param other - a const_iterator<T> object to be copied to caller object.
       */
        const_iterator(const const_iterator &const_it) = default;

    /**
       * Destructor of class const_iterator<T>.
       *
       * Template Requirements (derived from SortedListNode<T> template requirements):
       *    Destructor
       */
        ~const_iterator() = default;

        /**
           * operator* : Dereference operator of class const_iterator<T>.
           *
           * @return
           *       A const reference of T, which is the value of the caller object.
           *
           */
        const T& operator*() const;

        /**
           * operator= : Assignment operator of class const_iterator<T>.
           *
           * @return
           *       A reference of the received const_iterator object.
           *
           */
        const_iterator& operator=(const const_iterator &iterator) = default;

        /**
           * operator++ : prefix ++ operator, which advances the caller const_iterator object
           *            to the next node in the list, and returns it.
           *
           * @return
           *       A reference of the following node of the received const_iterator object.
           */
        const_iterator& operator++();

        /**
           * operator++ : postfix ++ operator, which advances the caller const_iterator object
           *            to the next node in the list, yet returns its previous value.
           *
           * @return
           *       A reference of the node of the received const_iterator object, prior to its advancement.
           */
        const_iterator operator++(int);

        /**
          * operator== : Returns whether a received const_iterator<T> object equals the caller object .
          *
          * @param iterator - a const_iterator<T> object to compare with *this
          * @return
          *      true - if both objects' are pointing to the same node of the same list.
          *      false - otherwise.
          */
        bool operator==(const const_iterator &iterator) const;

        //End of const_iterator template class methods declaration//
    };


        //Implementation of SortedList class functions//


    template<class T>
    SortedList<T>::SortedList() : head(nullptr), num_of_nodes(0) {}

    template<class T>
    SortedList<T>::~SortedList() {
        if (head){
            SortedListNode<T>::deleteRecursively(head);
        }
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
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list) {
        if (this == &list) {
            return *this;
        }
        SortedListNode<T> *new_head = nullptr;
        if(list.num_of_nodes != 0){
            new_head = list.head->copyRecursively();
        }
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
        } else if (to_add < head->getValue()) {
            new_node->setNext(head);
            head = new_node;
        } else {
            SortedListNode<T> *antecedent = head;
            while (antecedent && antecedent->getValue() < to_add) {
                if (antecedent->getNext() == nullptr || to_add < antecedent->getNext()->getValue()) {
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
    void SortedList<T>::remove(const const_iterator& iter) {
        if (&iter == nullptr || num_of_nodes == 0) {
            return;
        }
        if (iter == end()) {
            return;
        }
        if (iter == begin()) {
            head = head->getNext();
        } else {
            SortedListNode<T> *previous = head;
            while (!(previous->getNext() == iter.getNodePtr())) {
                previous = previous->getNext();
            }
            previous->setNext(iter.getNodePtr()->getNext());
        }
        delete (iter.getNodePtr());
        num_of_nodes--;
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(this, 0);
    }

    template <class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        return const_iterator(this, this->length());
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

             //End of SortedList class functions implementation//


             //Implementation of const_iterator class functions//

    template<class T>
    SortedList<T>::const_iterator::const_iterator(const SortedList *sorted_list, int index): sorted_list(sorted_list),
                                                                                             index(index < 0 || index > sorted_list->length() ? throw std::out_of_range("Iterator is Illegal") : index) {
        if(index == sorted_list->length()){
            current_node = nullptr;
        }
        else{
            SortedListNode<T> *it = sorted_list->getHead();
            for (int i = 0; i < index; i++) {
                it = it->getNext();
            }
            current_node = it;
        }
    }

    template<class T>
    const T &SortedList<T>::const_iterator::operator*() const {
        return current_node->getValue();
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const const_iterator &iterator) const {
        if(sorted_list != iterator.sorted_list){
            return false;
        }
        return (index == iterator.index);
    }

    template<class T>
    typename SortedList<T>::const_iterator &SortedList<T>::const_iterator::operator++() {
        if(index == sorted_list->length()){
            throw std::out_of_range("Illegal access");
        }
        ++index;
        current_node = current_node->getNext();
        return *this;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int) {
        if(index == sorted_list->length()){
            throw std::out_of_range("Illegal access");
        }
        const_iterator result = *this;
        ++(*this);
        return result;
    }

            //End of const_iterator class functions implementation//

}


#endif //PARTB_PARTB_H
