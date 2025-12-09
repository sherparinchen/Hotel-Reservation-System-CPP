#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>

struct Date {
    int y,m,d;
    // compare operators
    bool operator<=(const Date& o) const;
    bool operator<(const Date& o) const;
    bool operator>=(const Date& o) const;
};

class Room {
public:
    int id;
    int capacity;
    double pricePerNight;
    Room(int id=0,int cap=1,double price=0);
    virtual std::string typeName() const = 0;
    virtual ~Room() {}
};

class SingleRoom : public Room {
public:
    SingleRoom(int id=0);
    std::string typeName() const override;
};

class DoubleRoom : public Room {
public:
    DoubleRoom(int id=0);
    std::string typeName() const override;
};

#endif
