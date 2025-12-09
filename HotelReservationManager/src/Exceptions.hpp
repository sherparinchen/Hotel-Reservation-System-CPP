#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

class HotelException : public std::runtime_error {
public:
    HotelException(const std::string& msg): std::runtime_error(msg) {}
};

#endif
