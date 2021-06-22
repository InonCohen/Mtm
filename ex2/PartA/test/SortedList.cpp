#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include "SortedList.h"

//    // operator *
//    template <class T>
//    const T& SortedList<T>::const_iterator::operator*() const {
//        if(index < 0 || index >= sorted_list->size()) {
//            throw std::out_of_range();
//        }
//        return sorted_list->head;
//    }
//
//
//    // operator==
//    template <class T>
//    bool SortedList<T>::const_iterator::operator==(const const_iterator& iterator) const {
//        assert(sorted_list== iterator.sorted_list);
//        return (index == iterator.index);
//    }
//
//    // operator!=
//    template <class T>
//    bool SortedList<T>::const_iterator::operator!=(const const_iterator it) const {
//        return !(*this == it);
//    }
//
//    // operator ++i
//    template <class T>
//    typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++(){
//        ++index;
//        return *this;
//    }
//
//    //operator i++
//    template <class T>
//    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int){
//        const_iterator result = *this;
//        ++*this;
//        return result;
//    }

    template<class T>
    SortedList<T>::SortedList():head(nullptr), size(0), next(nullptr) {}

    template<class T>
    SortedList<T>::~SortedList() {
        if(next!= nullptr){
            ~(*next);
        }
        delete head;
    }


//    template <class T>
//    SortedList<T>::SortedList(const SortedList<T>& other): head(nullptr), size(0), next(nullptr) {
//        SortedList<T>* to_return = *this;
//        int list_full_length = other.size;
//        for(int i=0; i<size;i++){
//            size=0;
//            head = new T(other.head);
//            if(!head){
//                ~to_return;
//                throw std::bad_alloc();
//            }
//            next=new SortedList<T>();
//            if(!next){
//                ~to_return;
//                throw std::bad_alloc();
//            }
//            this = next;
//        }
//        next = nullptr;
//        this = to_return;
//        SortedList<T>::const_iterator other_iter = other.begin();
//        for(int i=0; i<size;i++){
//            *head = *other_iter++;
//            size = list_full_length-i;
//            this=next;
//        }
//        this=to_return;
//    }
//
///**
//    - returns const iterator pointing to first element of SortedList.
//    - element remains unchanged since this parameter is const.
//    * requirements:
//    - constructor for class const iterator
//    */
//    template <class T>
//   typename SortedList<T>::const_iterator SortedList<T>::begin() const{
//        return const_iterator(this,0);
//    }
//}