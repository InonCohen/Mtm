#ifndef EX1_EXAMDETAILS_H
#define EX1_EXAMDETAILS_H
#include <stdio>
#include <stdlib>


namespace mtm{
    class ExamTime{
        int month;
        int day;
        double time;
    public:
        ExamTime(int month, int day, double time);
        ~ExamTime()=default;
        ExamTime& operator=(const ExamTime& other);
    };

        class ExamDetails{
            int course_number;
            ExamTime exam_time;
            int duration;
            std::string zoom_link;
        public:
            ExamDetails(int course_number, int month, int day, double time, int duration, std::string zoom_link);
            ~ExamDetails();
            ExamDetails(const ExamDetails& exam);
            ExamDetails& operator=(const ExamDetails& exam);
            std::string& getLink() const;
            void setLink(const std::string& new_link);
            int operator-(const ExamDetails& exam) const;
            bool operator<(const ExamDetails& exam) const;
            friend std::ostream& operator<<(std::ostream&, const ExamDetails& exam);
            ExamDetails makeMatamExam();
        };
        std::ostream& ExamDetails::operator<<(std::ostream& os, const ExamDetails& exam);


}


#endif //EX1_EXAMDETAILS_H
