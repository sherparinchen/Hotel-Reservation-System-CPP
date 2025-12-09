#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "Reservation.hpp"
#include "Guest.hpp"

Date parseDate(const std::string& s); // throws HotelException
std::string caesarEncrypt(const std::string& s);
std::string caesarDecrypt(const std::string& s);
bool overlaps(const Date& a1,const Date& a2,const Date& b1,const Date& b2);

#endif
