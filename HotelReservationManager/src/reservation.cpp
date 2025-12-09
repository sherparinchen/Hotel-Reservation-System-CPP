// member2.cpp - Reservation and Guest (member 2)
#include "Reservation.hpp"
#include "Guest.hpp"
#include <sstream>
#include <vector>
using namespace std;

Reservation::Reservation(): id(0), roomId(0) {}

string Reservation::serialize() const {
    // id|username|roomId|fromY-fromM-fromD|toY-toM-toD
    std::ostringstream oss;
    oss<<id<<"|"<<username<<"|"<<roomId<<"|"<<from.y<<"-"<<from.m<<"-"<<from.d<<"|"<<to.y<<"-"<<to.m<<"-"<<to.d;
    return oss.str();
}

Reservation Reservation::deserialize(const string& line) {
    Reservation r;
    std::istringstream iss(line);
    string part;
    getline(iss, part, '|'); r.id = stoi(part);
    getline(iss, r.username, '|');
    getline(iss, part, '|'); r.roomId = stoi(part);
    getline(iss, part, '|');
    sscanf(part.c_str(), "%d-%d-%d", &r.from.y, &r.from.m, &r.from.d);
    getline(iss, part, '|');
    sscanf(part.c_str(), "%d-%d-%d", &r.to.y, &r.to.m, &r.to.d);
    return r;
}

Guest::Guest(): username(""), encryptedPassword(""), fullName(""), birthdate("") {}

string Guest::serialize() const {
    // username|encryptedPassword|fullName|birthdate
    std::ostringstream oss;
    oss<<username<<"|"<<encryptedPassword<<"|"<<fullName<<"|"<<birthdate;
    return oss.str();
}

Guest Guest::deserialize(const string& line) {
    Guest g;
    std::istringstream iss(line);
    getline(iss, g.username, '|');
    getline(iss, g.encryptedPassword, '|');
    getline(iss, g.fullName, '|');
    getline(iss, g.birthdate, '|');
    return g;
}
