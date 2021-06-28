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

        /**
         * timeIsValid : Returns whether a received double makes a valid starting time of an exam.
         *
         * @param time - a new examDetails potential starting time for the exam
         * @return
         *      true - if time is between 00:00 and 23:30, and ends with .0 or .5 .
         *      false - otherwise.
         */
        static bool timeIsValid(const double time);
    public:

                /**ExamDetails Exceptions*/

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

                //End of ExamDetails Exceptions//

                /**ExamDetails Methods*/

        /**
           * Constructor of class ExamDetails.
           *
           * @param course_number - the number of the course of the new exam.
           * @param month - the month in which the new exam will take place. Must be 1 to 12.
           * @param day - the day on which the new exam will take place. Must be 1 to 30.
           * @param time - the exam starting hour. Must be 00:00 to 23:30 in lapses of 30 minutes.
           * @param duration - the exam duration, in hours.
           * @param zoom_link - the link to the zoom room in which the exam will take place.
           */
        ExamDetails(int course_number, int month, int day, double time, int duration, std::string zoom_link="");

        /**
           * Destructor of class ExamDetails.
           */
        ~ExamDetails();

        /**
           * Copy Constructor of class ExamDetails.
           *
           * @param other - an ExamDetails object to be copied.
           */
        ExamDetails(const ExamDetails& other);

        /**
           * operator= : Assignment operator of class ExamDetails.
           *
           * @param other - an ExamDetails object to be copied.
           */
        ExamDetails& operator=(const ExamDetails& other);

        /**
           * getLink : Returns the zoom link to connect to the exam.
           *
           * @return
           *    A copy of the link to the zoom meeting of the exam.
           */
        std::string getLink() const;

        /**
           * setLink : Changes the zoom link to connect to the exam.
           *
           * @param new_link - a new link to which the zoom link is to be changed.
           */
        void setLink(const std::string new_link);

        /**
           * operator- : Calculate the difference between the starting time of the caller ExamDetails
           *             and the starting time of the ExamDetails object received by the function.
           *
           * @param other - an ExamDetails object, of which time difference from the current Exam is to be calculated.
           *
           * @return
           *        the difference in days between the current ExamDetails object and the other ExamDetails object
           */
        int operator-(const ExamDetails& other) const;

        /**
           * operator< : Returns whether the caller ExamDetails object starts before the ExamDetails object
           *             received by the function.
           *
           * @param other - an ExamDetails object, to which the caller ExamDetails object is to be compared .
           *
           * @return
           *        true - if the caller ExamDetails exam starts before the other's.
           *        false - otherwise.
           */
        bool operator<(const ExamDetails& other) const;

        /**
           * makeMatamExam : Creates a new ExamDetails object with the information of Matam's exam.
           *
           * @return
           *        an ExamDetails object with course number 234124, which takes place on July 28th,
           *        at 1pm, for 3 hours. The zoom link is: https://tinyurl.com/59hzps6m.
           */
        static ExamDetails makeMatamExam();

        /**
             * operator<< : Output Operator of class ExamDetails. Returns an ostream& with an ExamDetails
             *              exam's details in the required formatting.
             *
             * @param os - Outstream to which the exam is to be sent.
             * @param exam - ExamDetails object to be output.
             *
             * @return
             *      Updated received outstream, with all required information of exam in the required formatting.
        */
        friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);

                //End of ExamDetails Methods//
    };

    //a friend operator which was declared in ExamDetails class
    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam);


}


#endif //EX2_EXAMDETAILS_H