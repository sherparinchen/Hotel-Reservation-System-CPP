// Mehedi - FileManager and Utils 
#include "FileManager.hpp"
#include "Utils.hpp"
#include "Exceptions.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
using namespace std;

namespace FileManager {
    void ensureDataFolder() {
        std::filesystem::create_directory("data");
        // ensure default users if guests.txt missing
        if(!std::filesystem::exists("data/guests.txt")) {
            ofstream ofs("data/guests.txt");
            // default user deu/deu123 and admin/admin123 encrypted
            Guest u; u.username = "rin"; u.encryptedPassword = caesarEncrypt("rin123"); u.fullName = "Default User"; u.birthdate="1999-01-01";
            ofs<<u.serialize()<<"\n";
            Guest a; a.username = "deu"; a.encryptedPassword = caesarEncrypt("deu123"); a.fullName = "Administrator"; a.birthdate="1970-01-01";
            ofs<<a.serialize()<<"\n";
        }
    }

    vector<Guest> loadGuests() {
        ensureDataFolder();
        vector<Guest> out;
        ifstream ifs("data/guests.txt");
        string line;
        while(getline(ifs,line)) if(!line.empty()) out.push_back(Guest::deserialize(line));
        return out;
    }
    void saveGuest(const Guest& g) {
        ensureDataFolder();
        ofstream ofs("data/guests.txt", ios::app);
        ofs<<g.serialize()<<"\n";
    }

    vector<Reservation> loadReservations() {
        ensureDataFolder();
        vector<Reservation> out;
        ifstream ifs("data/reservations.txt");
        string line;
        while(getline(ifs,line)) if(!line.empty()) out.push_back(Reservation::deserialize(line));
        return out;
    }
    void saveReservation(const Reservation& r) {
        ensureDataFolder();
        ofstream ofs("data/reservations.txt", ios::app);
        ofs<<r.serialize()<<"\n";
    }
    int nextReservationId() {
        int mx=0;
        auto v = loadReservations();
        for(auto &r:v) if(r.id>mx) mx=r.id;
        return mx+1;
    }
}

Date parseDate(const string& s) {
    int y,m,d;
    if(sscanf(s.c_str(), "%d-%d-%d", &y,&m,&d)!=3) throw HotelException("Invalid date format. Use YYYY-MM-DD");
    if(m<1||m>12) throw HotelException("Month must be 1..12");
    if(d<1||d>31) throw HotelException("Day must be 1..31");
    // basic month-day checks
    int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (y%4==0 && (y%100!=0 || y%400==0));
    if(leap) mdays[2]=29;
    if(d>mdays[m]) throw HotelException("Invalid day for month");
    Date dt; dt.y=y; dt.m=m; dt.d=d;
    return dt;
}

string caesarEncrypt(const string& s) {
    string out=s;
    for(char &c: out) {
        if(isalpha((unsigned char)c)) {
            char base = isupper((unsigned char)c)?'A':'a';
            c = (char)( (c - base + 3)%26 + base );
        } else if(isdigit((unsigned char)c)) {
            c = (char)( (c - '0' + 3)%10 + '0' );
        }
    }
    return out;
}
string caesarDecrypt(const string& s) {
    string out=s;
    for(char &c: out) {
        if(isalpha((unsigned char)c)) {
            char base = isupper((unsigned char)c)?'A':'a';
            c = (char)( (c - base - 3 + 26)%26 + base );
        } else if(isdigit((unsigned char)c)) {
            c = (char)( (c - '0' - 3 + 10)%10 + '0' );
        }
    }
    return out;
}

bool overlaps(const Date& a1,const Date& a2,const Date& b1,const Date& b2) {
    // [a1,a2) and [b1,b2) overlapping
    if(a2<=b1) return false;
    if(b2<=a1) return false;
    return true;
}
