
#include <iostream>
#include "ExamDetails.h"
    using namespace mtm;
    int main(){
        ExamDetails exam1 = ExamDetails::makeMatamExam();
        ExamDetails exam2(104032, 7, 11, 9.5, 3);
        ExamDetails exam3 = exam1;
        std::cout << "the difference between MATAM and infi 2m is " << (exam1-exam2) << " days\n\n";
        ExamDetails& closest = (exam1 < exam2) ? exam1 : exam2;
        std::cout << "your closest exam is:" << std::endl << closest << std::endl;
        return 0;
    }

