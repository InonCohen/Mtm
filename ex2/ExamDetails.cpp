#include "ExamDetails.h"

namespace mtm{
    ExamDetails::ExamDetails(int course_number, int month, int day, double time, int duration, std::string zoom_link):
    course_number(course_number), month(month>=1 && month<=12 ? month : throw ExamDetails::InvalidDateException()), day(day), time(time), duration(duration), zoom_link(zoom_link)
}
