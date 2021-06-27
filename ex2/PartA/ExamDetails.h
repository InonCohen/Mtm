#ifndef EX2_EXAMDETAILS_H
#define EX2_EXAMDETAILS_H
#include <cstdio>
#include <string>
#include <cstdlib>


namespace mtm{

    class ExamDetails{
        int course_number;
        int month;
        int day;
        double time;
        int duration;
        std::string zoom_link;
    public:
        class InvalidDateException: public std::exception{
        public:
            const char* what() const noexcept {
                return "invalid date";
            }
        };
        class InvalidTimeException: public std::exception{
        public:
            const char* what() const noexcept {
                return "invalid time";
            }
        };
        class InvalidArgsException: public std::exception{
        public:
            const char* what() const noexcept {
                return "invalid argument";
            }
        };
        ExamDetails(int course_number, int month, int day, double time, int duration, std::string zoom_link="");
        ~ExamDetails();
        ExamDetails(const ExamDetails& other);
        ExamDetails& operator=(const ExamDetails& other);
        std::string getLink() const;
        void setLink(const std::string new_link);
        int operator-(const ExamDetails& other) const;
        bool operator<(const ExamDetails& other) const;
        static ExamDetails makeMatamExam();
        friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

    };
    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);


}


#endif //EX2_EXAMDETAILS_H