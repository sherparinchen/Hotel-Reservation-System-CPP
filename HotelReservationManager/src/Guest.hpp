#ifndef GUEST_HPP
#define GUEST_HPP

#include <string>

struct Guest {
    std::string username;
    std::string encryptedPassword; // Caesar shift 3
    std::string fullName;
    std::string birthdate;
    Guest();
    std::string serialize() const;
    static Guest deserialize(const std::string& line);
};

#endif
