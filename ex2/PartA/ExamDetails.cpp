#include <cmath>
#include "ExamDetails.h"

#define EPSILON (0.000001)
#define HALF_AN_HOUR (0.5)
#define DAYS_OF_THE_MONTH 30
#define MONTHS_OF_THE_YEAR 12
//#define HOURS_OF_THE_DAY 24
#define LAST_HOUR_ACCEPTED (23.5)

namespace mtm{
    static bool timeIsValid(double time){
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
}
