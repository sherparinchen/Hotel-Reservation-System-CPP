// Beda- Rooms implementation 
#include "Room.hpp"
#include <string>
using namespace std;

Room::Room(int id,int cap,double price): id(id), capacity(cap), pricePerNight(price) {}

SingleRoom::SingleRoom(int id): Room(id,1,50.0) {}
string SingleRoom::typeName() const { return "Single"; }

DoubleRoom::DoubleRoom(int id): Room(id,2,80.0) {}
string DoubleRoom::typeName() const { return "Double"; }

bool Date::operator<=(const Date& o) const {
    if(y!=o.y) return y<o.y;
    if(m!=o.m) return m<o.m;
    return d<=o.d;
}
bool Date::operator<(const Date& o) const {
    if(y!=o.y) return y<o.y;
    if(m!=o.m) return m<o.m;
    return d<o.d;
}
bool Date::operator>=(const Date& o) const {
    return !(*this < o);
}
