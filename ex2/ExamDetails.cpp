#include "ExamDetails.h"

namespace mtm{
    ExamDetails::ExamDetails(int course_number, int month, int day, double time, int duration, std::string zoom_link):
    course_number(course_number), exam_time(new ExamTime(month, day, duration)), duration(duration), zoom_link(zoom_link)
}
