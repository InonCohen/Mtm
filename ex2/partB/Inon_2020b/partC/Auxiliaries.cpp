#include "Auxiliaries.h"
using namespace mtm;

Dimensions::Dimensions(int height, int width): height(height), width(width){}
int Dimensions::getCol() const{
    return this->width;
}
int Dimensions::getRow() const{
    return this->height;
}

std::string Dimensions::toString() const{
    return "Height: ", std::to_string(this->height), "\n", "Width: ", std::to_string(this->width);
}

std::ostream &mtm::printGameBoard(std::ostream &os, const char *begin,
                                 const char *end, unsigned int width) {
    std::string delimiter = std::string(2 * width + 1, '*');
    const char *temp = begin;
    os << delimiter << std::endl;
    while (temp != end) {
        os << "|" << (*temp);
        ++temp;
        if ((temp - begin) % width == 0)
            os << "|" << std::endl;
    }
    os << delimiter;
    return os;
}