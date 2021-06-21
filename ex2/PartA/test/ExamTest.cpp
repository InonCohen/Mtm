#include <cstdio>
#include <iostream>
#include "../ExamDetails.h"
    using namespace mtm;
    int main(){
        ExamDetails exam1 = ExamDetails::makeMatamExam();
        ExamDetails exam2(104032, 7, 11, 9.5, 3);
        ExamDetails exam3 = exam1;
        auto exam4 = new ExamDetails(104032, 7, 11, 9.5, 3, "InonC My Man");
        std::cout << "the difference between MATAM and infi 2m is " << (exam1-exam2) << " days\n\n";
        ExamDetails& closest = (exam1 < exam2) ? exam1 : exam2;
        std::cout << "your closest exam is:" << std::endl << closest << std::endl;
        std::cout << "exam4 LINK: " << exam4->getLink() << std::endl;
        delete exam4;
        std::cout << "exam4 LINK: " << exam4->getLink() << std::endl; // Why it behave that way? Should raise an error
        return 0;
    }

