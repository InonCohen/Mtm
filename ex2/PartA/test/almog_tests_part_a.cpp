#include <iostream>
#include <cstdlib>
#include "test_utilities.h"
#include <ctime>
#include <fstream>
#include <string>
#include "../ExamDetails.h"
#include "../SortedList.h"

#define NUMBER_TESTS 6
#define NUMBER_TESTS_SL 2

#define START printf("\033[1m\033[34m\033[4m"); \
              printf("\nAlmog Levy Tests\033[0m \U0001F600\n");\
              printf("\033[1m\033[34m\n");

#define END printf("\033[1m\033[34m"); \
              printf("\nGreat! \U0001F4AF");\
              printf("\033[1m\033[34m \033[0m\n\n");

#define EXAMDETAILS printf("\033[1m\033[34m"); \
              printf("\nExamDetails Tests:");\
              printf("\033[1m\033[34m\n");

#define SORTEDLIST printf("\033[1m\033[34m"); \
              printf("\nSortedList Test:");\
              printf("\033[1m\033[34m\n");

using namespace mtm;
using namespace std;

using std::cout;
using std::endl;
using std::string;
using namespace mtm;
using std::ofstream;
using std::ifstream;

string getLen(string str)
{
    return std::to_string(str.length());
}

bool isTrollLink(const ExamDetails& exam) {
    return (exam.getLink().find("tinyurl") != string::npos);
}

template<class T>
void printList(SortedList<T> list) {
    for (auto it = list.begin(); !(it == list.end()); ++it) {
        cout << *it << endl;
    }
    cout << endl;
}

template<class T>
void operator<<(ostream& os, SortedList<T>& list) {
    for (auto it = list.begin(); !(it == list.end()); ++it) {
        os << *it << endl;
    }
}

bool testConstructorParameters() {

    int counter = 0;

    try {
        ExamDetails exam_details2(104034.5, 7, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidArgsException &e) {
        counter++;
    }
    ASSERT_TEST(counter == 0);


    try {
        counter = 0;
        ExamDetails exam_details2(-104034, 7, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidArgsException &e) {
        counter++;
    }
    ASSERT_TEST(counter == 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 0, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter != 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 13, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter != 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 1, 11, 9.5, 3);
    }
    catch (...) {//TODO
        counter++;
    }
    ASSERT_TEST(counter == 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 12, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter == 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, -12, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter != 0);

    try {
        counter = 0;
        ExamDetails exam_details(104034, 12.6, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter == 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 12, 11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter == 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 12, -11, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter != 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 12, 31, 9.5, 3);
    }
    catch (ExamDetails::InvalidDateException &e) {
        counter++;
    }
    ASSERT_TEST(counter != 0);

    try {
        counter = 0;
        ExamDetails exam_details2(104034, 12, 11, 9.2, 3);
    }
    catch (ExamDetails::InvalidTimeException &e) {
        counter++;
        ASSERT_TEST(counter != 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, 9.5000, 3);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter == 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, 9, 3);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter == 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, -9, 3);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter != 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, 0, 3);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter == 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, 25, 3);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter != 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, 22, 3.0);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter == 0);

        try {
            counter = 0;
            ExamDetails exam_details2(104034, 12, 11, 25, 3.6);
        }
        catch (ExamDetails::InvalidTimeException &e) {
            counter++;
        }
        ASSERT_TEST(counter != 0);


        return true;
    }
}

bool testGetSetLink(){

    int counter = 0;
    try {
        counter = 0;
        ExamDetails exam_details2(104034, 12, 11, 22, 3, "almogAndOri/fgfsgfsg435");
        ASSERT_TEST(exam_details2.getLink() == "almogAndOri/fgfsgfsg435");
        exam_details2.setLink("new_link/dsgfag5645");
        ASSERT_TEST(exam_details2.getLink() == "new_link/dsgfag5645");
        exam_details2.setLink("");
        ASSERT_TEST(exam_details2.getLink() == "");
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    ASSERT_TEST(counter==0);


    return true;

}

bool testMinusOperator(){

    int counter = 0;
    try {
        counter = 0;
        ExamDetails exam_details(104034, 12, 11, 22, 3);
        ExamDetails exam_details2(104036, 9, 11, 23, 3);
        ASSERT_TEST(exam_details-exam_details2 == 90);
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    try {
        counter = 0;
        ExamDetails exam_details(104034, 9, 11, 22, 3);
        ExamDetails exam_details2(104036, 12, 11, 23, 3);
        ASSERT_TEST(exam_details-exam_details2 == -90);
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    return true;
}

bool testLessThanOperator(){

    int counter = 0;
    try {
        counter = 0;
        ExamDetails exam_details(104034, 9, 11, 22, 3);
        ExamDetails exam_details2(104036, 9, 11, 23, 3);
        ASSERT_TEST((exam_details<exam_details2) == true);
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    try {
        counter = 0;
        ExamDetails exam_details(104034, 9, 11, 23, 3);
        ExamDetails exam_details2(104036, 9, 11, 21, 3);
        ASSERT_TEST((exam_details<exam_details2) == false);
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    try {
        counter = 0;
        ExamDetails exam_details(104034, 9, 11, 22, 3);
        ExamDetails exam_details2(104036, 9, 11, 22, 3);
        ASSERT_TEST((exam_details<exam_details2) == false);
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    return true;
}

static bool compareFiles(const char* file1path, const char* file2path){

    string line, line2;
    ifstream file1(file1path);
    ifstream file2(file2path);
    while(!file1.eof() && !file2.eof()){
        getline(file1,line);
        getline(file2,line2);
        if(line==line2){
            continue;
        }
        else{
            return false;
        }
    }

    return true;
}

bool testCopyConstructorAndAssignmentOperator(){

    int counter=0;
    try {
        counter = 0;
        ExamDetails exam_details(104034, 9, 11, 23, 3);
        ExamDetails exam_details2 = exam_details;
        ExamDetails exam_details3(104035, 10, 11, 23, 3);
        ASSERT_TEST((exam_details<exam_details2) == false);
        ASSERT_TEST((exam_details-exam_details2) == 0);
        ASSERT_TEST(exam_details.getLink() == exam_details2.getLink());

        ofstream file1("exam_details1.txt");
        ofstream file2("exam_details2.txt");
        ofstream file3("exam_details3.txt");
        file1 << exam_details;
        file2 << exam_details2;
        file3 << exam_details3;

        ASSERT_TEST(compareFiles("exam_details1.txt", "exam_details2.txt") == true);
        ASSERT_TEST(compareFiles("exam_details1.txt", "exam_details3.txt") == false);
        ASSERT_TEST(compareFiles("exam_details2.txt", "exam_details3.txt") == false);

        exam_details2 = exam_details3;
        ofstream file2new("exam_details2_new.txt");
        file2new << exam_details2;
        ASSERT_TEST(compareFiles("exam_details2_new.txt", "exam_details3.txt") == true);
        ASSERT_TEST(compareFiles("exam_details2_new.txt", "exam_details2.txt") == false);

    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    return true;

}

bool testMakeMatamExam(){

    int counter = 0;
    try{
        ExamDetails exam1 = ExamDetails::makeMatamExam();

        ofstream file1("matam_our_output.txt");
        file1 << exam1;

        ofstream expected_output("matam_expected_output.txt");
        expected_output << "Course Number: 234124" << endl << "Time: 28.7 at 13:00" << endl <<
                        "Duration: 3:00" << endl << "Zoom Link: https://tinyurl.com/59hzps6m" << endl;


        ASSERT_TEST(compareFiles("matam_our_output.txt", "matam_expected_output.txt") == true);
    }
    catch(ExamDetails::InvalidDateException& e) {
        counter++;
    }
    catch(ExamDetails::InvalidTimeException& e) {
        counter++;
    }
    catch(...){
        counter++;
    }
    ASSERT_TEST(counter==0);

    return true;
}

bool testCtorCCtorAssignmnetOperatorInsertSL(){

    int counter;
    try{
        counter =0;

        /** checking constructor **/
        SortedList<string> lst1 = SortedList<string>();
        lst1.insert("Charlie");
        lst1.insert("Bob");
        lst1.insert("Alice");
        lst1.insert("Donald");

        /** checking copy constructor **/
        SortedList<string> lst2 = lst1;
        ofstream file1("list1.txt");
        ofstream file2("list2.txt");
        file1 << lst1;
        file2 << lst2;
        ASSERT_TEST(compareFiles("list1.txt", "list2.txt") == true);

        /** checking assignment operator **/
        SortedList<string> lst3;
        lst3 = lst1;
        ofstream file3("list3.txt");
        file3 << lst3;
        ASSERT_TEST(compareFiles("list3.txt", "list2.txt") == true);
        ASSERT_TEST(compareFiles("list1.txt", "list3.txt") == true);

        lst3.insert("almog");
        ofstream new_file3("new_list3.txt");
        new_file3 << lst3;
        ASSERT_TEST(compareFiles("new_list3.txt", "list2.txt") == false);

        lst2.insert("almog");
        ofstream new_file2("new_list2.txt");
        new_file2 << lst2;
        ASSERT_TEST(compareFiles("new_list3.txt", "new_list2.txt") == true);

    }catch(...){
        counter++;
    }

    ASSERT_TEST(counter == 0);

    return true;
}

bool testRemoveAndLengthFunction(){

    int counter;
    try{
        counter =0;

        SortedList<string> lst1 = SortedList<string>();
        lst1.insert("Charlie");
        lst1.insert("Bob");
        lst1.insert("Alice");
        lst1.insert("Donald");

        SortedList<string> lst2 = lst1;
        ofstream file1("list1.txt");
        ofstream file2("list2.txt");
        file1 << lst1;
        file2 << lst2;

        SortedList<string> lst3;
        lst3 = lst1;
        ASSERT_TEST(lst3.length() == lst1.length());
        ASSERT_TEST(lst1.length() == lst2.length());

        lst3.remove(lst3.begin());
        ofstream file3("list3.txt");
        file3 << lst3;
        ASSERT_TEST(compareFiles("list3.txt", "list2.txt") == false);
        ASSERT_TEST(lst3.length() != lst2.length());

        lst2.remove(lst2.begin());
        ofstream new_file2("new_list2.txt");
        new_file2 << lst2;
        ASSERT_TEST(compareFiles("list3.txt", "new_list2.txt") == true);
        ASSERT_TEST(lst3.length() == lst2.length());

        lst2.remove(lst2.end());
        lst3.remove(lst3.end());
        ofstream file1e("list3e.txt");
        ofstream file2e("list2e.txt");
        file1e << lst3;
        file2e << lst2;
        ASSERT_TEST(compareFiles("list3e.txt", "list2e.txt") == true);
        ASSERT_TEST(lst3.length() == lst2.length());

    }catch(...){
        counter++;
    }

    ASSERT_TEST(counter == 0);

    return true;
}

bool (*tests[])(void) = {
        testConstructorParameters,
        testGetSetLink,
        testMinusOperator,
        testLessThanOperator,
        testCopyConstructorAndAssignmentOperator,
        testMakeMatamExam
        };

const char *testNames[] = {
        "testConstructorParameters",
        "testGetSetLink",
        "testOperator'-'",
        "testOperator'<'",
        "testCopyConstructorAndAssignmentOperator",
        "testMakeMatamExam"
        };

bool (*testsSortedList[])(void) = {
        testCtorCCtorAssignmnetOperatorInsertSL,
        testRemoveAndLengthFunction
        //TODO: test filter, apply, iterator
};

const char *testNamesSortedList[] = {
        "testCtorCCtorAssignmnetOperatorInsert",
        "testRemoveAndLengthFunction"
};

int main(int argc, char *argv[])
{
    START;
    srand(time(NULL));
    if (argc == 1)
    {
        EXAMDETAILS;
        for (int test_idx = 0; test_idx < NUMBER_TESTS; test_idx++)
        {
            RUN_TEST(tests[test_idx], testNames[test_idx]);
        }

        SORTEDLIST;
        for (int test_idx = 0; test_idx < NUMBER_TESTS_SL; test_idx++)
        {
            RUN_TEST(testsSortedList[test_idx], testNamesSortedList[test_idx]);
        }
        END;
        return 0;
    }
    if (argc != 2)
    {
        fprintf(stdout, "Usage: <test index>\n");
        return 0;
    }

    int test_idx = strtol(argv[1], NULL, 10);
    if (test_idx < 1 || test_idx > NUMBER_TESTS)
    {
        fprintf(stderr, "Invalid test index %d\n", test_idx);
        return 0;
    }

    RUN_TEST(tests[test_idx - 1], testNames[test_idx - 1]);

    return 0;
}

