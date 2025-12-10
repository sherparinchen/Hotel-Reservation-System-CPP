#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
// New file
#include <vector>
#include "Reservation.hpp"
#include "Guest.hpp"

namespace FileManager {
    void ensureDataFolder();
    std::vector<Guest> loadGuests();
    void saveGuest(const Guest& g);
    std::vector<Reservation> loadReservations();
    void saveReservation(const Reservation& r);
    int nextReservationId();
}

#endif
