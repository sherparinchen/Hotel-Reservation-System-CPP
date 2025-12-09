// Rinchen - Main program & Manager 
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include "FileManager.hpp"
#include "Utils.hpp"
#include "Exceptions.hpp"
#include "Room.hpp"

using namespace std;

vector<Room*> makeRooms() {
    vector<Room*> rooms;
    // create 6 rooms alternating single/double
    for(int i=1;i<=6;i++){
        if(i%2==1) rooms.push_back(new SingleRoom(i));
        else rooms.push_back(new DoubleRoom(i));
    }
    return rooms;
}

Guest* findGuest(vector<Guest>& guests, const string& username) {
    for(auto &g: guests)
        if(g.username == username) return &g;
    return nullptr;
}

void userMenu() {
    cout << "\n=== Dong-eui Hotel Marriot User Menu ===\n";
    cout << "1) Make reservation\n";
    cout << "2) Cancel reservation (by id)\n";
    cout << "3) List my reservations\n";
    cout << "4) List all rooms\n";
    cout << "5) Logout\n";
    cout << "Choose: ";
}

int adminMenu() {
    cout << "\n=== Dong-eui Hotel Marriot Admin Menu ===\n";
    cout << "1) Make reservation for someone\n";
    cout << "2) List all reservations\n";
    cout << "3) Logout\n";
    cout << "Choose: ";
    int c;
    if(!(cin >> c)) { cin.clear(); string tmp; getline(cin,tmp); return -1; }
    return c;
}

int mainMenu() {
    cout << "\n=== Dong-eui Hotel Marriot Reservation Manager ===\n";
    cout << "1) Login\n";
    cout << "2) Register\n";
    cout << "0) Exit\n";
    cout << "Choose: ";
    int c;
    if(!(cin >> c)) { cin.clear(); string tmp; getline(cin,tmp); return -1; }
    return c;
}

int main() {
    try {
        FileManager::ensureDataFolder();
        auto rooms = makeRooms();

        while(true) {
            int choice = mainMenu();

            if(choice == 0) break;

            if(choice == 2) {
                // Register
                Guest ng;
                cout << "Choose username: ";
                cin >> ng.username;

                auto guests = FileManager::loadGuests();
                if(findGuest(guests, ng.username)) {
                    cout << "User already exists.\n";
                    continue;
                }

                string pass;
                cout << "Choose password: ";
                cin >> pass;
                ng.encryptedPassword = caesarEncrypt(pass);

                cin.ignore();
                cout << "Full name: ";
                getline(cin, ng.fullName);
                cout << "Birthdate (YYYY-MM-DD): ";
                getline(cin, ng.birthdate);

                FileManager::saveGuest(ng);
                cout << "Registered successfully. Please login now.\n";
                continue;
            }

            if(choice != 1) {
                cout << "Invalid choice.\n";
                continue;
            }

            // LOGIN
            cout << "Username: ";
            string user;
            cin >> user;
            cout << "Password: ";
            string pass;
            cin >> pass;

            auto guests = FileManager::loadGuests();
            Guest* g = findGuest(guests, user);

            if(!g) {
                cout << "User not found. Please register first.\n";
                continue;
            }

            if(g->encryptedPassword != caesarEncrypt(pass)) {
                cout << "Wrong password.\n";
                continue;
            }

            bool isAdmin = (user == "admin");

            cout << "\nWelcome, " << g->fullName << " (" << g->username << ")\n";

            if(isAdmin) {
                while(true) {
                    int cmd = adminMenu();
                    if(cmd == 3) break;

                    if(cmd == 1) {
                        try {
                            cout << "Username to reserve for: ";
                            string whom; cin >> whom;

                            cout << "Room id: ";
                            int rid; cin >> rid;

                            cout << "From (YYYY-MM-DD): ";
                            string fs; cin >> fs;
                            cout << "To   (YYYY-MM-DD): ";
                            string ts; cin >> ts;

                            Date d1 = parseDate(fs);
                            Date d2 = parseDate(ts);

                            if(!(d1 < d2)) throw HotelException("From must be before To");

                            auto resv = FileManager::loadReservations();
                            for(auto &r : resv)
                                if(r.roomId == rid && overlaps(r.from, r.to, d1, d2))
                                    throw HotelException("Overlapping reservation");

                            Reservation newr;
                            newr.id = FileManager::nextReservationId();
                            newr.username = whom;
                            newr.roomId = rid;
                            newr.from = d1;
                            newr.to = d2;
                            FileManager::saveReservation(newr);

                            cout << "Reservation saved. ID=" << newr.id << "\n";
                        }
                        catch(HotelException &he) {
                            cout << "Error: " << he.what() << "\n";
                        }
                    }
                    else if(cmd == 2) {
                        auto all = FileManager::loadReservations();
                        cout << "All reservations:\n";
                        for(auto &r : all)
                            cout << r.serialize() << "\n";
                    }
                    else cout << "Invalid option\n";
                }
            }
            else {
                while(true) {
                    userMenu();
                    int cmd;
                    if(!(cin >> cmd)) { cin.clear(); string tmp; getline(cin,tmp); cmd = -1; }

                    if(cmd == 5) break; // Logout

                    if(cmd == 1) {
                        try {
                            cout << "Room id: ";
                            int rid; cin >> rid;

                            cout << "From (YYYY-MM-DD): ";
                            string fs; cin >> fs;
                            cout << "To   (YYYY-MM-DD): ";
                            string ts; cin >> ts;

                            Date d1 = parseDate(fs);
                            Date d2 = parseDate(ts);
                            if(!(d1 < d2)) throw HotelException("From must be before To");

                            auto resv = FileManager::loadReservations();
                            for(auto &r : resv)
                                if(r.roomId == rid && overlaps(r.from, r.to, d1, d2))
                                    throw HotelException("Overlapping reservation");

                            Reservation newr;
                            newr.id = FileManager::nextReservationId();
                            newr.username = g->username;
                            newr.roomId = rid;
                            newr.from = d1;
                            newr.to = d2;
                            FileManager::saveReservation(newr);
                            cout << "Reservation saved. ID=" << newr.id << "\n";
                        }
                        catch(HotelException& he) {
                            cout << "Error: " << he.what() << "\n";
                        }
                    }
                    else if(cmd == 2) {
                        cout << "Reservation ID to cancel: ";
                        int id; cin >> id;

                        auto all = FileManager::loadReservations();
                        vector<Reservation> keep;
                        bool removed = false;

                        for(auto &r : all) {
                            if(r.id == id && r.username == g->username)
                                removed = true;
                            else
                                keep.push_back(r);
                        }

                        if(!removed) {
                            cout << "Reservation not found or not yours.\n";
                        } else {
                            ofstream ofs("data/reservations.txt");
                            for(auto &r : keep) ofs << r.serialize() << "\n";
                            cout << "Cancelled.\n";
                        }
                    }
                    else if(cmd == 3) {
                        auto all = FileManager::loadReservations();
                        cout << "Your reservations:\n";
                        for(auto &r : all)
                            if(r.username == g->username)
                                cout << r.serialize() << "\n";
                    }
                    else if(cmd == 4) {
                        cout << "Rooms:\n";
                        for(auto &rm : rooms)
                            cout << rm->id << " : "
                            << rm->typeName()
                            << " cap=" << rm->capacity
                            << " price=" << rm->pricePerNight << "\n";
                    }
                    else cout << "Invalid option\n";
                }
            }
        }

        cout << "Goodbye!\n";

        // Cleanup rooms
        for(auto p : rooms) delete p;
    }
    catch(exception &e) {
        cout << "Fatal error: " << e.what() << "\n";
    }

    return 0;
}
