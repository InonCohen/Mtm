#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include "ExamDetails.h"

#define EPSILON (0.000001)
#define HALF_AN_HOUR (0.5)
#define DAYS_OF_THE_MONTH 30
#define MONTHS_OF_THE_YEAR 12
//#define HOURS_OF_THE_DAY 24
#define LAST_HOUR_ACCEPTED (23.5)
#define MTM_COURSE_NUM (234124)
#define MTM_EXAM_MONTH 7
#define MTM_EXAM_DAY 28
#define MTM_EXAM_HOUR 13
#define MTM_EXAM_DURATION 3
#define MTM_EXAM_ZOOM_LINK "https://tinyurl.com/59hzps6m"

namespace mtm{
    static bool timeIsValid(const double time){
        if(time<0-EPSILON || time>LAST_HOUR_ACCEPTED+EPSILON){
            return false;
        }
        double fraction, integer=0;
        fraction = modf(time, &integer);
        if(abs(fraction)<EPSILON || abs(fraction-HALF_AN_HOUR)<EPSILON){
            return true;
        }
        return false;
    }

    ExamDetails::ExamDetails(int course_number, int month, int day, double time, int duration, std::string zoom_link):
            course_number(course_number),
            month(month>=1 && month<=MONTHS_OF_THE_YEAR ? month : throw ExamDetails::InvalidDateException()),
            day(day>=1 && day<=DAYS_OF_THE_MONTH ? day : throw ExamDetails::InvalidDateException()),
            time(timeIsValid(time)?time:throw ExamDetails::InvalidTimeException()),
            duration(duration>=0? duration:throw ExamDetails::InvalidTimeException()),
            zoom_link(zoom_link){}
    ExamDetails::~ExamDetails() = default;
    ExamDetails::ExamDetails(const ExamDetails& other)=default;
    ExamDetails& ExamDetails::operator=(const ExamDetails& other)=default;
    std::string ExamDetails::getLink() const{
        if(!this){
            throw ExamDetails::InvalidArgsException();
        }
        return zoom_link;
    }
    void ExamDetails::setLink(const std::string new_link){
        if(!this){
            throw ExamDetails::InvalidArgsException();
        }
        zoom_link=new_link;
    }
    int ExamDetails::operator-(const ExamDetails& other) const{
        if(!this || !&other){
            throw ExamDetails::InvalidArgsException();
        }
        int month_diff=month-other.month;
        int day_diff=day-other.day;
        return month_diff*30+day_diff;
    }

    bool ExamDetails::operator<(const ExamDetails& other) const{
        if(!this || !&other){
            throw InvalidArgsException();
        }
        return (*this - other < 0) ? true : false;
    }
    ExamDetails ExamDetails::makeMatamExam(){
        ExamDetails to_return(MTM_COURSE_NUM, MTM_EXAM_MONTH, MTM_EXAM_DAY,
                              MTM_EXAM_HOUR, MTM_EXAM_DURATION, MTM_EXAM_ZOOM_LINK);
        return to_return;
    }

    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam){
        if(!&os || !&exam){
            throw ExamDetails::InvalidArgsException();
        }
        os << "Course Number: " << exam.course_number << std::endl;
        os << "Time: " << exam.day << "." << exam.month << " at ";
        double fraction, integer=0;
        fraction = modf(exam.time, &integer);
        os << integer << ":" << ((fabs(fraction-HALF_AN_HOUR)<EPSILON)? "30" : "00") << std::endl;
        os << "Duration: " << exam.duration << ":00" << std::endl;
        os << "Zoom Link: " << exam.zoom_link << std::endl;
        return os;
    }


}