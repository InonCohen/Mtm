/*
 * (Version 2)
 *
 * Visit: mtmtests.website
 * Tests with Robert
 *
 * Remember:    (1) Passing the below tests doesn't mean you will pass their tests.
 *              (2) Always check memory leak of your own implementation - Use the operation: valgrind ./your_excuted_project
 *                  check the above website for more about memory leak.
 */

/*
 * Make sure you already have the same files (examDetails.h and examDetails.cpp)
 * in the same folder that the file (mainR.cpp) is found.
 */
#include <iostream>
#include "examDetails.h"
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using namespace mtm;

#define LET_ME_TEST(thing, count) cout << endl << "(" << count << ") " << "Testing the " << thing << "..." << endl;
#define PASSED_THE(thing) cout << "(Excellent) Passed the " << thing << "!" << endl;
#define LET_ME_TEST_(thing, count) to_the_file << endl << "(" << count << ") " << "Testing the " << thing << "..." << endl;
#define PASSED_THE_(thing) to_the_file << "(Excellent) Passed the " << thing << "!" << endl;

/*
 * C++ TESTS COURSE MATAM (234214) - SPRING 2020
 * ---------------------------------------------
 * -------------------PART A--------------------
 * ----------------EXAM DETAILS-----------------
 * ---------------------------------------------
 */

int main()
{
    std::ofstream to_the_file;
    to_the_file.open("Your_output.txt");
    int test_counter = 0;
    test_counter++;
    LET_ME_TEST("ExamDetails Constructor (Version 1)",test_counter)
    LET_ME_TEST_("ExamDetails Constructor (Version 1)",test_counter)
    ExamDetails exam1(104195, 1, 1, 0, 1, "infy1.com");
    ExamDetails exam2(104031, 12, 30, 23.5, 10000, "infy1m.com");
    ExamDetails exam3(104281, 9, 9, 9, 3, "infy2.com");
    ExamDetails exam4(104032, 10, 10, 10, 3, "infy2m.com");
    ExamDetails exam5(100000, 1, 1, 0, 1);
    PASSED_THE("ExamDetails Constructor (Version 1)")
    PASSED_THE_("ExamDetails Constructor (Version 1)")

    test_counter++;
    LET_ME_TEST("ExamDetails Copy Constructor (Version 1)", test_counter)
    LET_ME_TEST_("ExamDetails Copy Constructor (Version 1)", test_counter)
    ExamDetails copied_exam1 = exam1;
    ExamDetails copied_exam2 = exam2;
    ExamDetails copied_exam3 = exam3;
    ExamDetails copied_exam4 = exam4;
    ExamDetails copied_exam5 = exam5;
    PASSED_THE("ExamDetails Copy Constructor (Version 1)")
    PASSED_THE_("ExamDetails Copy Constructor (Version 1)")

    test_counter++;
    LET_ME_TEST("ExamDetails makeMatamExam Method", test_counter)
    LET_ME_TEST_("ExamDetails makeMatamExam Method", test_counter)
    ExamDetails::makeMatamExam();
    PASSED_THE("ExamDetails makeMatamExam Method")
    PASSED_THE_("ExamDetails makeMatamExam Method")

    test_counter++;
    LET_ME_TEST("ExamDetails Copy Constructor (Version 2)", test_counter)
    LET_ME_TEST_("ExamDetails Copy Constructor (Version 2)", test_counter)
    ExamDetails copied_matam = ExamDetails::makeMatamExam();
    PASSED_THE("ExamDetails Copy Constructor (Version 2)")
    PASSED_THE_("ExamDetails Copy Constructor (Version 2)")

    test_counter++;
    LET_ME_TEST("ExamDetails Copy Assignment Operator (Version 1) - Normal Assignment", test_counter)
    LET_ME_TEST_("ExamDetails Copy Assignment Operator (Version 1) - Normal Assignment", test_counter)
    copied_exam1 = exam2;
    copied_exam2 = exam1;
    copied_exam3 = exam4;
    copied_exam4 = exam3;
    copied_exam5 = exam5;
    PASSED_THE("ExamDetails Copy Assignment Operator (Version 1) - Normal Assignment")
    PASSED_THE_("ExamDetails Copy Assignment Operator (Version 1) - Normal Assignment")

    test_counter++;
    LET_ME_TEST("ExamDetails Copy Assignment Operator (Version 2.1) - Self Assignment", test_counter)
    LET_ME_TEST_("ExamDetails Copy Assignment Operator (Version 2.1) - Self Assignment", test_counter)
    exam1 = exam1;
    exam2 = exam2;
    exam3 = exam3;
    exam4 = exam4;
    exam5 = exam5;
    copied_exam1 = copied_exam1;
    copied_exam2 = copied_exam2;
    copied_exam3 = copied_exam3;
    copied_exam4 = copied_exam4;
    copied_exam5 = copied_exam5;
    PASSED_THE("ExamDetails Copy Assignment Operator (Version 2.1) - Self Assignment")
    PASSED_THE_("ExamDetails Copy Assignment Operator (Version 2.1) - Self Assignment")

    ExamDetails& referenece_to_exam1 = exam1;
    ExamDetails& referenece_to_exam2 = exam2;
    ExamDetails& referenece_to_exam3 = exam3;
    const ExamDetails& const_referenece_to_exam1 = exam1;
    const ExamDetails& const_referenece_to_exam2 = exam2;
    const ExamDetails& const_referenece_to_exam3 = exam3;

    test_counter++;
    LET_ME_TEST("ExamDetails Copy Assignment Operator (Version 2.2) - Self Assignment - Reference", test_counter)
    LET_ME_TEST_("ExamDetails Copy Assignment Operator (Version 2.2) - Self Assignment - Reference", test_counter)
    exam1 = referenece_to_exam1;
    referenece_to_exam1 = exam1;
    exam2 = referenece_to_exam2;
    referenece_to_exam2 = exam2;
    exam3 = referenece_to_exam3;
    referenece_to_exam3 = exam3;
    exam1 = const_referenece_to_exam1;
    exam2 = const_referenece_to_exam2;
    exam3 = const_referenece_to_exam3;
    PASSED_THE("ExamDetails Copy Assignment Operator (Version 2.2) - Self Assignment - Reference")
    PASSED_THE_("ExamDetails Copy Assignment Operator (Version 2.2) - Self Assignment - Reference")

    test_counter++;
    LET_ME_TEST("ExamDetails getLink Method (Version 1)", test_counter)
    LET_ME_TEST_("ExamDetails getLink Method (Version 1)", test_counter)
    exam1.getLink();
    exam2.getLink();
    exam3.getLink();
    exam4.getLink();
    exam5.getLink();
    copied_exam1.getLink();
    copied_exam2.getLink();
    copied_exam3.getLink();
    copied_exam4.getLink();
    copied_exam5.getLink();
    referenece_to_exam1.getLink();
    referenece_to_exam2.getLink();
    referenece_to_exam3.getLink();
    PASSED_THE("ExamDetails getLink Method (Version 1)")
    PASSED_THE_("ExamDetails getLink Method (Version 1)")

    test_counter++;
    LET_ME_TEST("ExamDetails getLink Method (Version 2.1) - Printing the link", test_counter)
    LET_ME_TEST_("ExamDetails getLink Method (Version 2.1) - Printing the link", test_counter)
    cout << "Original Infy 1 website: " << exam1.getLink() << endl;
    cout << "Original Infy 1m website: " << exam2.getLink() << endl;
    cout << "Original Infy 2 website: " << exam3.getLink() << endl;
    cout << "Original Infy 2m website: " << exam4.getLink() << endl;
    cout << "Original String website: " << exam5.getLink() << endl;
    cout << "Copied Infy 1 website: " << copied_exam2.getLink() << endl;
    cout << "Copied Infy 1m website: " << copied_exam1.getLink() << endl;
    cout << "Copied Infy 2 website: " << copied_exam4.getLink() << endl;
    cout << "Copied Infy 2m website: " << copied_exam3.getLink() << endl;
    cout << "Copied Empty String: " << copied_exam5.getLink() << endl;
    to_the_file << "Original Infy 1 website: " << exam1.getLink() << endl;
    to_the_file << "Original Infy 1m website: " << exam2.getLink() << endl;
    to_the_file << "Original Infy 2 website: " << exam3.getLink() << endl;
    to_the_file << "Original Infy 2m website: " << exam4.getLink() << endl;
    to_the_file << "Original String website: " << exam5.getLink() << endl;
    to_the_file << "Copied Infy 1 website: " << copied_exam2.getLink() << endl;
    to_the_file << "Copied Infy 1m website: " << copied_exam1.getLink() << endl;
    to_the_file << "Copied Infy 2 website: " << copied_exam4.getLink() << endl;
    to_the_file << "Copied Infy 2m website: " << copied_exam3.getLink() << endl;
    to_the_file << "Copied Empty String: " << copied_exam5.getLink() << endl;
    PASSED_THE("ExamDetails getLink Method (Version 2.1) - Printing the link")
    PASSED_THE_("ExamDetails getLink Method (Version 2.1) - Printing the link")

    test_counter++;
    LET_ME_TEST("ExamDetails setLink Method", test_counter)
    LET_ME_TEST_("ExamDetails setLink Method", test_counter)
    copied_exam1.setLink("infy1m.co.il/copied");
    copied_exam2.setLink("infy1.co.il/copied");
    copied_exam3.setLink("infy2m.co.il/copied");
    copied_exam4.setLink("infy2.co.il/copied");
    copied_exam5.setLink("Not Empty Anymore");
    referenece_to_exam1.setLink("infy1.co.il/original");
    referenece_to_exam2.setLink("infy1m.co.il/original");
    referenece_to_exam3.setLink("infy2.co.il/original");
    exam4.setLink("infy2m.co.il/original");
    exam5.setLink("original");
    PASSED_THE("ExamDetails setLink Method")
    PASSED_THE_("ExamDetails setLink Method")

    test_counter++;
    LET_ME_TEST("ExamDetails getLink Method (Version 2.2) - Printing the updated link", test_counter)
    LET_ME_TEST_("ExamDetails getLink Method (Version 2.2) - Printing the updated link", test_counter)
    cout << "Updated Original Infy 1 website: " << exam1.getLink() << endl;
    cout << "Updated Original Infy 1m website: " << exam2.getLink() << endl;
    cout << "Updated Original Infy 2 website: " << exam3.getLink() << endl;
    cout << "Updated Original Infy 2m website: " << exam4.getLink() << endl;
    cout << "Updated Original String website: " << exam5.getLink() << endl;
    cout << "Updated Copied Infy 1 website: " << copied_exam2.getLink() << endl;
    cout << "Updated Copied Infy 1m website: " << copied_exam1.getLink() << endl;
    cout << "Updated Copied Infy 2 website: " << copied_exam4.getLink() << endl;
    cout << "Updated Copied Infy 2m website: " << copied_exam3.getLink() << endl;
    cout << "Updated Copied Empty String: " << copied_exam5.getLink() << endl;
    to_the_file << "Updated Original Infy 1 website: " << exam1.getLink() << endl;
    to_the_file << "Updated Original Infy 1m website: " << exam2.getLink() << endl;
    to_the_file << "Updated Original Infy 2 website: " << exam3.getLink() << endl;
    to_the_file << "Updated Original Infy 2m website: " << exam4.getLink() << endl;
    to_the_file << "Updated Original String website: " << exam5.getLink() << endl;
    to_the_file << "Updated Copied Infy 1 website: " << copied_exam2.getLink() << endl;
    to_the_file << "Updated Copied Infy 1m website: " << copied_exam1.getLink() << endl;
    to_the_file << "Updated Copied Infy 2 website: " << copied_exam4.getLink() << endl;
    to_the_file << "Updated Copied Infy 2m website: " << copied_exam3.getLink() << endl;
    to_the_file << "Updated Copied Empty String: " << copied_exam5.getLink() << endl;
    PASSED_THE("ExamDetails getLink Method (Version 2.2) - Printing the updated link")
    PASSED_THE_("ExamDetails getLink Method (Version 2.2) - Printing the updated link")

    test_counter++;
    LET_ME_TEST("ExamDetails Subtract Operator (-)", test_counter)
    LET_ME_TEST_("ExamDetails Subtract Operator (-)", test_counter)
    cout << "((Infy 1 date) - (Infy 1 date)) = " << exam1-exam1 << " days" << endl;
    cout << "((Infy 1 date) - (Infy 1m date)) = " << exam1-exam2 << " days" << endl;
    cout << "((Infy 1m date) - (Infy 1 date)) = " << exam2-exam1 << " days" << endl;
    cout << "((Infy 2 date) - (Infy 2m date)) = " << exam3-exam4 << " days" << endl;
    cout << "((Infy 2m date) - (Infy 2 date)) = " << exam4-exam3 << " days" << endl;
    cout << "((Empty String) - (Infy 1)) = " << exam5-exam1 << " days" << endl;
    cout << "((Copied Infy 1 date) - (Copied Infy 1m date)) = " << copied_exam2-copied_exam1 << " days" << endl;
    cout << "((Copied Infy 1m date) - (Copied Infy 1 date)) = " << copied_exam1-copied_exam2 << " days" << endl;
    cout << "((Copied Infy 2 date) - (Copied Infy 2m date)) = " << copied_exam4-copied_exam3 << " days" << endl;
    cout << "((Copied Infy 2m date) - (Copied Infy 2 date)) = " << copied_exam3-copied_exam4 << " days" << endl;
    cout << "((Copied Empty String) - (Copied Infy 1)) = " << copied_exam5-copied_exam2 << " days" << endl;
    to_the_file << "((Infy 1 date) - (Infy 1 date)) = " << exam1-exam1 << " days" << endl;
    to_the_file << "((Infy 1 date) - (Infy 1m date)) = " << exam1-exam2 << " days" << endl;
    to_the_file << "((Infy 1m date) - (Infy 1 date)) = " << exam2-exam1 << " days" << endl;
    to_the_file << "((Infy 2 date) - (Infy 2m date)) = " << exam3-exam4 << " days" << endl;
    to_the_file << "((Infy 2m date) - (Infy 2 date)) = " << exam4-exam3 << " days" << endl;
    to_the_file << "((Empty String) - (Infy 1)) = " << exam5-exam1 << " days" << endl;
    to_the_file << "((Copied Infy 1 date) - (Copied Infy 1m date)) = " << copied_exam2-copied_exam1 << " days" << endl;
    to_the_file << "((Copied Infy 1m date) - (Copied Infy 1 date)) = " << copied_exam1-copied_exam2 << " days" << endl;
    to_the_file << "((Copied Infy 2 date) - (Copied Infy 2m date)) = " << copied_exam4-copied_exam3 << " days" << endl;
    to_the_file << "((Copied Infy 2m date) - (Copied Infy 2 date)) = " << copied_exam3-copied_exam4 << " days" << endl;
    to_the_file << "((Copied Empty String) - (Copied Infy 1)) = " << copied_exam5-copied_exam2 << " days" << endl;
    PASSED_THE("ExamDetails Subtract Operator (-)")
    PASSED_THE_("ExamDetails Subtract Operator (-)")

    test_counter++;
    LET_ME_TEST("ExamDetails Statement Operator (<) (Version 1)", test_counter)
    LET_ME_TEST_("ExamDetails Statement Operator (<) (Version 1)", test_counter)
    cout << "Is Infy 1 before Infy 1: " << ((exam1<exam1) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Infy 1 before Infy 1m: " << ((exam1<exam2) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Infy 1m before Infy 1: " << ((exam2<exam1) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Infy 2 before Infy 2m: " << ((exam3<exam4) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Infy 2m before Infy 2: " << ((exam4<exam3) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Empty String before Infy 1: " << ((exam5<exam1) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Copied Infy 1 before Copied Infy 1m: " << ((copied_exam2<copied_exam1) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Copied Infy 1m before Copied Infy 1: " << ((copied_exam1<copied_exam2) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Copied Infy 1 before Copied Infy 2m: " << ((copied_exam4<copied_exam3) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Copied Infy 1m before Copied Infy 2: " << ((copied_exam3<copied_exam4) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Copied Empty String before Copied Infy 1: " << ((copied_exam5<copied_exam2) ? "TRUE!" : "FALSE!") << endl;
    cout << "Is Reference to Infy1 before Infy 1: " << ((referenece_to_exam1<exam1) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Infy 1 before Infy 1: " << ((exam1<exam1) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Infy 1 before Infy 1m: " << ((exam1<exam2) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Infy 1m before Infy 1: " << ((exam2<exam1) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Infy 2 before Infy 2m: " << ((exam3<exam4) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Infy 2m before Infy 2: " << ((exam4<exam3) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Empty String before Infy 1: " << ((exam5<exam1) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Copied Infy 1 before Copied Infy 1m: " << ((copied_exam2<copied_exam1) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Copied Infy 1m before Copied Infy 1: " << ((copied_exam1<copied_exam2) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Copied Infy 1 before Copied Infy 2m: " << ((copied_exam4<copied_exam3) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Copied Infy 1m before Copied Infy 2: " << ((copied_exam3<copied_exam4) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Copied Empty String before Copied Infy 1: " << ((copied_exam5<copied_exam2) ? "TRUE!" : "FALSE!") << endl;
    to_the_file << "Is Reference to Infy1 before Infy 1: " << ((referenece_to_exam1<exam1) ? "TRUE!" : "FALSE!") << endl;
    PASSED_THE("ExamDetails Statement Operator (<) (Version 1)")
    PASSED_THE_("ExamDetails Statement Operator (<) (Version 1)")

    test_counter++;
    LET_ME_TEST("ExamDetails Printing Method (Version 1)", test_counter)
    LET_ME_TEST_("ExamDetails Printing Method (Version 1)", test_counter)
    cout << exam1 << endl;
    cout << exam2 << endl;
    cout << exam3 << endl;
    cout << exam4 << endl;
    cout << exam5 << endl;
    cout << copied_exam2 << endl;
    cout << copied_exam1 << endl;
    cout << copied_exam4 << endl;
    cout << copied_exam3 << endl;
    cout << copied_exam5 << endl;
    cout << referenece_to_exam1 << endl;
    cout << referenece_to_exam2 << endl;
    cout << referenece_to_exam3;
    to_the_file << exam1 << endl;
    to_the_file << exam2 << endl;
    to_the_file << exam3 << endl;
    to_the_file << exam4 << endl;
    to_the_file << exam5 << endl;
    to_the_file << copied_exam2 << endl;
    to_the_file << copied_exam1 << endl;
    to_the_file << copied_exam4 << endl;
    to_the_file << copied_exam3 << endl;
    to_the_file << copied_exam5 << endl;
    to_the_file << referenece_to_exam1 << endl;
    to_the_file << referenece_to_exam2 << endl;
    to_the_file << referenece_to_exam3;
    PASSED_THE("ExamDetails Printing Method (Version 1)")
    PASSED_THE_("ExamDetails Printing Method (Version 1)")

    test_counter++;
    LET_ME_TEST("ExamDetails Exception - InvalidDateException() (Version 1)", test_counter)
    LET_ME_TEST_("ExamDetails Exception - InvalidDateException() (Version 1)", test_counter)
    try {
        ExamDetails invalid_date1(1, 0, 1, 1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Invalid date - (month=0)" << endl;
        to_the_file << "Invalid date - (month=0)" << endl;
    }
    try {
        ExamDetails invalid_date2(1, 1, 0, 1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Invalid date - (day=0)" << endl;
        to_the_file << "Invalid date - (day=0)" << endl;
    }
    try {
        ExamDetails invalid_date3(1, 13, 1, 1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Invalid date - (month>12)" << endl;
        to_the_file << "Invalid date - (month>12)" << endl;
    }
    try {
        ExamDetails invalid_date4(1, 1, 31, 1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Invalid date - (day>30)" << endl;
        to_the_file << "Invalid date - (day>30)" << endl;
    }
    try {
        ExamDetails invalid_date5(1, -1, 1, 1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Invalid date - (month<0)" << endl;
        to_the_file << "Invalid date - (month<0)" << endl;
    }
    try {
        ExamDetails invalid_date6(1, 1, -1, 1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Invalid date - (day<0)" << endl;
        to_the_file << "Invalid date - (day<0)" << endl;
    }
    PASSED_THE("ExamDetails Exception - InvalidDateException() (Version 1)")
    PASSED_THE_("ExamDetails Exception - InvalidDateException() (Version 1)")

    test_counter++;
    LET_ME_TEST("ExamDetails Exception - InvalidTimeException()", test_counter)
    LET_ME_TEST_("ExamDetails Exception - InvalidTimeException()", test_counter)
    try {
        ExamDetails invalid_hour1(1, 1, 1, -1, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidTimeException& e) {
        cout << "Invalid hour - (hour<0)" << endl;
        to_the_file << "Invalid hour - (hour<0)" << endl;
    }
    try {
        ExamDetails invalid_hour2(1, 1, 1, 24, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidTimeException& e) {
        cout << "Invalid hour - (hour>23.5))" << endl;
        to_the_file << "Invalid hour - (hour>23.5))" << endl;
    }
    PASSED_THE("ExamDetails Exception - InvalidTimeException()")
    PASSED_THE_("ExamDetails Exception - InvalidTimeException()")

    test_counter++;
    LET_ME_TEST("ExamDetails Exception - Exceptions Order", test_counter)
    LET_ME_TEST_("ExamDetails Exception - Exceptions Order", test_counter)
    try {
        ExamDetails exceptions_order2(1, 0, 1, 24, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Priority to DateException - Month number is invalid" << endl;
        to_the_file << "Priority to DateException - Month number is invalid" << endl;
    }
    try {
        ExamDetails exceptions_order3(1, 1, 31, 24, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidDateException& e) {
        cout << "Priority to DateException - Day number is invalid" << endl;
        to_the_file << "Priority to DateException - Day number is invalid" << endl;
    }
    try {
        ExamDetails exceptions_order4(1, 1, 1, 24, 1, "https://tinyurl.com/ym8wf46t");
    }
    catch (ExamDetails::InvalidTimeException& e) {
        cout << "Priority to TimeException - Hour number is invalid" << endl;
        to_the_file << "Priority to TimeException - Hour number is invalid" << endl;
    }
    PASSED_THE("ExamDetails Exception - Exceptions Order")
    PASSED_THE_("ExamDetails Exception - Exceptions Order")
    to_the_file.close();

    cout << endl << "Now compare the output in the file 'Your_output.txt' with 'My_output.txt'";
    return 0;
}
