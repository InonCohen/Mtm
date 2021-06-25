#include <string>
#include "SortedList.h"
using namespace mtm;
using namespace std;

std::string getLen (std::string str){
    int str_len= str.size();
    return to_string(str_len);
}

int main(){
    SortedList<string> lst1 = SortedList<string>();
    lst1.insert("Charlie");
    lst1.insert("Bob");
    lst1.insert("Alice");
    lst1.insert("Donald");
    printList(lst1);
    SortedList<string> lst2 = lst1;
    lst2 = lst2.apply(getLen);
    printList(lst2);
    SortedList<string>::const_iterator it = lst2.begin();
    cout << *it << endl << endl;
    ++it;
    lst2.remove(it);
    printList(lst2);
    return 0;
}
