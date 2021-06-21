#ifndef EX1_SORTEDLIST_H
#define EX1_SORTEDLIST_H


    template <class T>
    class SortedList{
        T* head;
        int size;
        SortedList<T>* next;
    public:
//        class const_iterator;
        SortedList();
        ~SortedList();
//        SortedList(const SortedList& other);
//        SortedList::const_iterator begin() const;
//        SortedList::const_iterator end() const;
    };

//    //implementation of const_iterator class//
//    template <class T>
//    class SortedList<T>:: const_iterator{
//        const SortedList* sorted_list;
//        int index;
//        /**
//    //iterator(const SortedList* int_SortedList, int index)//:
//    - constructor of const_iterator.
// */
//        const_iterator(const SortedList* sorted_list, int index): sorted_list(sorted_list), index(index){};
//        friend class SortedList<T>;
//    public:
//        /**
//    //~const_iterator()=default//:
//    - destructor of const_iterator class.
// */
//        ~const_iterator()=default;
//        /**
//       //T& operator*() const//:
//       -returns element iterator is pointing at as const.
//       - const_iterator remains unchanged.
//    */
//        const T& operator*() const;
//        /**
//        //const_iterator(const const_iterator& const_it)=default//:
//        - copy constructor of const_iterator class- set to default.
//     */
//        const_iterator(const const_iterator& const_it)=default;
//        /**
//        //const_iterator& operator=(const_iterator& iterator)=default//:
//        -assignment operator.
//        - receives const_iterator reference parameter.
//        - set to be default, return const_iterator by reference.
//     */
//        const_iterator& operator=(const_iterator& iterator)=default;
//        /**
//        //const_iterator& operator++()//:
//        -prefix ++ operator.
//        - returns const_iterator pointing to next element in SortedList.
//     */
//        const_iterator& operator++();
//        /**
//        //const_iterator operator++(int)//:
//        -postfix ++ operator
//        -advances const_iterators index by 1.
//        - returns original const_iterator (*this) by value
//     */
//        const_iterator operator++(int);
//        /**
//        //bool operator==(const const_iterator& iterator) const//:
//        - compares two const iterators.
//        - returns true if they are pointing at same element (by index)
//        - otherwise returns false.
//     */
//        bool operator==(const const_iterator& iterator) const;
//        /**
//        //bool operator!=(const const_iterator& iterator) const//:
//        - compares two const iterators.
//        - returns false if they are pointing at same element (by index)
//        - otherwise returns true.
//     */
//        bool operator!=(const const_iterator it) const;
//    };






#endif //EX1_SORTEDLIST_H
