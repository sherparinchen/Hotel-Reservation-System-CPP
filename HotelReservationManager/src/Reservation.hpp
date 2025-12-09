#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include "Room.hpp"

struct Reservation {
    int id;
    std::string username;
    int roomId;
    Date from;
    Date to;
    Reservation();
    std::string serialize() const;
    static Reservation deserialize(const std::string& line);
};

#endif
